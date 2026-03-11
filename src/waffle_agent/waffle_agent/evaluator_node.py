import os
import json
import re
import math
import rclpy
from rclpy.node import Node
import numpy as np
import threading

from langchain.agents import initialize_agent, AgentType
from langchain_openai import ChatOpenAI
from waffle_agent.llm import get_llm

# IMPORT YOUR TOOLS HERE
from waffle_agent.tools.waffle import (
    init_waffle_tools, 
    query_graph_memory_semantical, 
    query_graph_memory_positional,
    query_graph_memory_by_time,
    query_long_term_memory # This is your ReMEmbR vector DB tool
)

import time
from langchain.callbacks.base import BaseCallbackHandler

class LLMTrackingCallbackHandler(BaseCallbackHandler):
    def __init__(self, logger):
        self.logger = logger
        self.graph_times = []
        self.ltm_times = []
        self.tool_starts = {}

    def on_agent_action(self, action, **kwargs):
        # This intercepts the Thought and Action before it finishes
        self.logger.info(f"\n[LLM THOUGHT] {action.log.strip()}")

    def on_tool_start(self, serialized, input_str, **kwargs):
        # Start stopwatch for this specific tool call
        run_id = kwargs.get('run_id')
        self.tool_starts[run_id] = time.time()

    def on_tool_end(self, output, **kwargs):
        run_id = kwargs.get('run_id')
        if run_id in self.tool_starts:
            elapsed = time.time() - self.tool_starts[run_id]
            tool_name = kwargs.get('name', '')
            
            # Sort the timing into the correct bucket
            if 'graph' in tool_name:
                self.graph_times.append(elapsed)
            elif 'long_term' in tool_name:
                self.ltm_times.append(elapsed)
            
            self.logger.info(f"[TOOL METRIC] '{tool_name}' completed in {elapsed:.3f}s")

class RosaNaVQAEvaluator(Node):
    def __init__(self):
        super().__init__('rosa_navqa_evaluator')
        
        self.declare_parameter('sequence_id', 6)
        self.declare_parameter('memory_mode', 'both') # 'graph', 'remembr', 'both'
        
        self.seq_id = self.get_parameter('sequence_id').value
        self.mode = self.get_parameter('memory_mode').value
        
        init_waffle_tools(self)
        
        # Dynamically assign tools based on evaluation mode
        self.tools = []
        if self.mode in ['graph', 'both']:
            self.tools.extend([query_graph_memory_semantical, query_graph_memory_positional, query_graph_memory_by_time])
        if self.mode in ['remembr', 'both']:
            self.tools.append(query_long_term_memory)
            
        self.get_logger().info(f"Eval Mode: {self.mode}. Tools loaded: {[t.name for t in self.tools]}")

        self.llm = get_llm(streaming=False) ### Initialize GPT-4o
        
        self.system_prompt = """
        You are an autonomous robot evaluating your memory of a past sequence. 
        You MUST use your provided memory tools to answer the question.
        You have a limit of 7 iterations, therefore provide an answer before reaching 7 iterations with the informations you have up to that point.
        
        CRITICAL INSTRUCTION FOR YOUR FINAL ANSWER:
        When you are finished using tools and are ready to answer the user, your Final Answer MUST be a pure JSON block containing exactly these keys. 
        If a field is not asked for, set it to null. Do NOT include any conversational text outside the JSON block.
        ```json
        {
            "binary": "yes" or "no" or null,
            "position": [x_float, y_float] or null,
            "time": time_float_in_seconds or null,
            "text": "Your descriptive text answer or null"
        }
        ```
        """
        
        self.agent = initialize_agent(
            self.tools, 
            self.llm, 
            agent=AgentType.CHAT_ZERO_SHOT_REACT_DESCRIPTION, 
            agent_kwargs={"system_message": self.system_prompt},
            max_iterations=9,
            verbose=False,
            handle_parsing_errors=True # <--- THIS IS THE CRITICAL FIX
        )

        # Run in thread so Langchain doesn't block ROS service callbacks
        self.eval_thread = threading.Thread(target=self.run_eval)
        self.eval_thread.start()

    # def run_eval(self):
    #     # Use absolute path to ensure file is found
    #     base_dir = "/app/NaVQA_eval/remembr/remembr" # Update if your path is different
    #     qa_file = f"{base_dir}/data/questions/{self.seq_id}/human_qa.json"
        
    #     if not os.path.exists(qa_file):
    #         self.get_logger().error(f"CRITICAL: Cannot find QA file at {qa_file}")
    #         return
            
    #     with open(qa_file, 'r') as f:
    #         qa_data = json.load(f)['data']

    #     results = []
    #     metrics = {"spatial_hits": 0, "spatial_total": 0, "time_hits": 0, "time_total": 0}

    #     for qa in qa_data:
    #         q_type = qa['type']
    #         gt = qa['answers']
            
    #         self.get_logger().info(f"\n[Q] {qa.get('question', 'No question found')}")
            
    #         # --- UPDATED ROBUST AGENT EXECUTION AND PARSING ---
    #         raw_resp = ""
    #         try:
    #             # 1. Fix LangChain deprecation warning (use invoke instead of run)
    #             raw_resp = self.agent.invoke({"input": qa['question']})['output']
                
    #             # 2. More forgiving JSON extraction
    #             json_match = re.search(r"```(?:json)?(.*?)```", raw_resp, re.DOTALL | re.IGNORECASE)
    #             if json_match:
    #                 json_str = json_match.group(1).strip()
    #             else:
    #                 # Fallback: manually find the first { and last }
    #                 start_idx = raw_resp.find('{')
    #                 end_idx = raw_resp.rfind('}')
    #                 if start_idx != -1 and end_idx != -1:
    #                     json_str = raw_resp[start_idx:end_idx+1]
    #                 else:
    #                     raise ValueError("No JSON-like structure found in response.")
                        
    #             pred = json.loads(json_str)

    #         except Exception as e:
    #             self.get_logger().error(f"Agent/Formatting Error: {e}\nRaw Output was: {raw_resp}")
    #             pred = {"binary": None, "position": None, "time": None, "text": str(raw_resp)}

    #         # --- EVALUATION LOGIC ---
    #         # 1. Evaluate Spatial (Threshold = 2.0m)
    #         if 'position' in q_type and isinstance(pred.get('position'), list) and len(pred['position']) >= 2:
    #             err = np.linalg.norm(np.array(pred['position'][:2]) - np.array(gt['position'][:2]))
    #             correct = bool(err <= 2.0)
    #             metrics['spatial_total'] += 1
    #             metrics['spatial_hits'] += int(correct)
    #             self.get_logger().info(f"Spatial Err: {err:.2f}m | Correct: {correct}")

    #         # 2. Evaluate Temporal (Threshold = 15.0s)
    #         if 'time' in q_type and pred.get('time') is not None:
    #             try:
    #                 err = abs(float(pred['time']) - float(gt['time']))
    #                 correct = bool(err <= 15.0)
    #                 metrics['time_total'] += 1
    #                 metrics['time_hits'] += int(correct)
    #                 self.get_logger().info(f"Time Err: {err:.2f}s | Correct: {correct}")
    #             except Exception as e:
    #                 self.get_logger().error(f"Time parsing error: {e}")

    #         # --- SAFE UUID EXTRACTION ---
    #         # Pandas sometimes alters headers. Safely get UUID, uuid, or default to a random string
    #         safe_uuid = qa.get('UUID', qa.get('uuid', f"unknown_q_{len(results)}"))

    #         results.append({"uuid": safe_uuid, "question": qa['question'], "pred": pred, "gt": gt})

    #     # --- LOG FINAL RESULTS ---
    #     self.get_logger().info("\n=== RESULTS ===")
    #     if metrics['spatial_total'] > 0:
    #         self.get_logger().info(f"Spatial: {metrics['spatial_hits']}/{metrics['spatial_total']}")
    #     if metrics['time_total'] > 0:
    #         self.get_logger().info(f"Time: {metrics['time_hits']}/{metrics['time_total']}")

    #     os.makedirs(f"{base_dir}/out", exist_ok=True)
    #     with open(f"{base_dir}/out/eval_seq{self.seq_id}_{self.mode}.json", 'w') as f:
    #         json.dump(results, f, indent=4)


    # def run_eval(self):
    #     base_dir = "/app/NaVQA_eval/remembr/remembr" # Update if your path is different
    #     qa_file = f"{base_dir}/data/questions/{self.seq_id}/human_qa.json"
        
    #     if not os.path.exists(qa_file):
    #         self.get_logger().error(f"CRITICAL: Cannot find QA file at {qa_file}")
    #         return
            
    #     with open(qa_file, 'r') as f:
    #         qa_data = json.load(f)['data']

    #     results = []
    #     metrics = {"spatial_hits": 0, "spatial_total": 0, "time_hits": 0, "time_total": 0}

    #     # Create a dedicated JSON formatter LLM
    #     json_llm = ChatOpenAI(
    #         temperature=0.0, 
    #         model="gpt-4o", 
    #         model_kwargs={"response_format": {"type": "json_object"}}
    #     )

    #     for qa in qa_data:
    #         q_type = qa['type']
    #         gt = qa['answers']
    #         question_text = qa.get('question', 'No question found')
            
    #         self.get_logger().info(f"\n[Q] {question_text}")
            
    #         raw_resp = ""
    #         try:
    #             # 1. Let the agent think normally and return raw text
    #             raw_resp = self.agent.invoke({"input": question_text})['output']
                
    #             # 2. Force it into JSON using OpenAI's guaranteed JSON mode
    #             formatter_prompt = f"""
    #             You are a data parser. Read the robot's answer and extract the facts into a strict JSON format.
                
    #             Original Question: {question_text}
    #             Robot's Answer: {raw_resp}
                
    #             You must output a JSON object with EXACTLY these keys:
    #             {{
    #                 "binary": "yes" or "no" or null,
    #                 "position": [x_coordinate, y_coordinate] or null,
    #                 "time": float_time_in_seconds or null,
    #                 "text": "The descriptive answer or null"
    #             }}
    #             If a specific piece of data is not present in the robot's answer, use null.
    #             """
                
    #             formatted_json_str = json_llm.invoke(formatter_prompt).content
    #             pred = json.loads(formatted_json_str)

    #         except Exception as e:
    #             self.get_logger().error(f"Agent/Formatting Error: {e}\nRaw Output was: {raw_resp}")
    #             pred = {"binary": None, "position": None, "time": None, "text": str(raw_resp)}

    #         # --- EVALUATION LOGIC ---
    #         if 'position' in q_type and isinstance(pred.get('position'), list) and len(pred['position']) >= 2:
    #             err = np.linalg.norm(np.array(pred['position'][:2]) - np.array(gt['position'][:2]))
    #             correct = bool(err <= 2.0)
    #             metrics['spatial_total'] += 1
    #             metrics['spatial_hits'] += int(correct)
    #             self.get_logger().info(f"Spatial Err: {err:.2f}m | Correct: {correct}")

    #         if 'time' in q_type and pred.get('time') is not None:
    #             try:
    #                 err = abs(float(pred['time']) - float(gt['time']))
    #                 correct = bool(err <= 15.0)
    #                 metrics['time_total'] += 1
    #                 metrics['time_hits'] += int(correct)
    #                 self.get_logger().info(f"Time Err: {err:.2f}s | Correct: {correct}")
    #             except Exception as e:
    #                 self.get_logger().error(f"Time parsing error: {e}")

    #         safe_uuid = qa.get('UUID', qa.get('uuid', f"unknown_q_{len(results)}"))
    #         results.append({"uuid": safe_uuid, "question": question_text, "pred": pred, "gt": gt})

    #     self.get_logger().info("\n=== RESULTS ===")
    #     if metrics['spatial_total'] > 0:
    #         self.get_logger().info(f"Spatial: {metrics['spatial_hits']}/{metrics['spatial_total']}")
    #     if metrics['time_total'] > 0:
    #         self.get_logger().info(f"Time: {metrics['time_hits']}/{metrics['time_total']}")

    #     os.makedirs(f"{base_dir}/out", exist_ok=True)
    #     with open(f"{base_dir}/out/eval_seq{self.seq_id}_{self.mode}.json", 'w') as f:
    #         json.dump(results, f, indent=4)

    def run_eval(self):
        base_dir = "/app/NaVQA_eval/remembr/remembr"
        qa_file = f"{base_dir}/data/questions/{self.seq_id}/human_qa.json"
        
        if not os.path.exists(qa_file):
            self.get_logger().error(f"CRITICAL: Cannot find QA file at {qa_file}")
            return
            
        with open(qa_file, 'r') as f:
            qa_data = json.load(f)['data']

        results = []
        metrics = {"spatial_hits": 0, "spatial_total": 0, "time_hits": 0, "time_total": 0}

        # 1. Initialize our custom tracking handler
        tracker = LLMTrackingCallbackHandler(self.get_logger())

        json_llm = ChatOpenAI(
            temperature=0.0, 
            model="gpt-4o", 
            model_kwargs={"response_format": {"type": "json_object"}}
        )

        overall_question_times = []

        for qa in qa_data:
            q_type = qa['type']
            gt = qa['answers']
            question_text = qa.get('question', 'No question found')
            
            self.get_logger().info(f"\n=========================================\n[Q] {question_text}")
            
            raw_resp = ""
            start_q_time = time.time() # Start question timer
            
            try:
                # 1. Get raw text from agent
                raw_resp = self.agent.invoke(
                    {"input": question_text}, 
                    config={"callbacks": [tracker]}
                )['output']
                
                # ---> ADDED: Log the final conclusion of the LLM before formatting
                self.get_logger().info(f"[LLM FINAL ANSWER] {raw_resp.strip()}")
                
                # 2. Format to JSON
                formatter_prompt = f"""
                You are a data parser. Read the robot's answer and extract the facts into strict JSON.
                Original Question: {question_text}
                Robot's Answer: {raw_resp}
                {{
                    "binary": "yes" or "no" or null,
                    "position": [x, y] or null,
                    "time": float_time_in_seconds or null,
                    "text": "The descriptive answer or null"
                }}
                """
                
                formatted_json_str = json_llm.invoke(formatter_prompt).content
                pred = json.loads(formatted_json_str)

            except Exception as e:
                self.get_logger().error(f"Agent/Formatting Error: {e}\nRaw Output was: {raw_resp}")
                pred = {"binary": None, "position": None, "time": None, "text": str(raw_resp)}

            # End question timer
            q_elapsed = time.time() - start_q_time
            overall_question_times.append(q_elapsed)
            self.get_logger().info(f"[METRIC] Total Agent Reply Time: {q_elapsed:.2f}s")

            # --- UPDATED EVALUATION LOGIC (No more silent skipping) ---
            
            # 1. Evaluate Spatial
            if 'position' in q_type or 'position' in gt:
                metrics['spatial_total'] += 1
                try:
                    # If LLM actually provided a valid [x, y] list
                    if isinstance(pred.get('position'), list) and len(pred['position']) >= 2:
                        err = np.linalg.norm(np.array(pred['position'][:2]) - np.array(gt['position'][:2]))
                        correct = bool(err <= 20.0)
                    else:
                        err = float('inf') # Penalize heavily if it returned null or text
                        correct = False
                        
                    metrics['spatial_hits'] += int(correct)
                    self.get_logger().info(f"--> Spatial Err: {err:.2f}m | Correct: {correct}")
                except Exception as e:
                    self.get_logger().error(f"Spatial math error: {e}")

            # 2. Evaluate Temporal
            if 'time' in q_type or 'time' in gt:
                metrics['time_total'] += 1
                try:
                    # If LLM provided a valid time float
                    if pred.get('time') is not None:
                        err = abs(float(pred['time']) - float(gt['time']))
                        correct = bool(err <= 120.0)
                    else:
                        err = float('inf') # Penalize heavily if it returned null
                        correct = False
                        
                    metrics['time_hits'] += int(correct)
                    self.get_logger().info(f"--> Time Err: {err:.2f}s | Correct: {correct}")
                except Exception as e:
                    self.get_logger().error(f"Time math error: {e}")

            safe_uuid = qa.get('UUID', qa.get('uuid', f"unknown_q_{len(results)}"))
            results.append({"uuid": safe_uuid, "question": question_text, "pred": pred, "gt": gt})

        # --- FINAL PERFORMANCE MARKERS ---
        self.get_logger().info("\n\n=== PERFORMANCE MARKERS ===")
        
        avg_graph = sum(tracker.graph_times) / len(tracker.graph_times) if tracker.graph_times else 0.0
        avg_ltm = sum(tracker.ltm_times) / len(tracker.ltm_times) if tracker.ltm_times else 0.0
        avg_q = sum(overall_question_times) / len(overall_question_times) if overall_question_times else 0.0
        
        self.get_logger().info(f"-> Average Graph Retrieval Time: {avg_graph:.3f} seconds (over {len(tracker.graph_times)} calls)")
        self.get_logger().info(f"-> Average VectorDB (LTM) Retrieval Time: {avg_ltm:.3f} seconds (over {len(tracker.ltm_times)} calls)")
        self.get_logger().info(f"-> Average Overall Reply Time per Question: {avg_q:.2f} seconds")

        self.get_logger().info("\n=== ACCURACY RESULTS ===")
        if metrics['spatial_total'] > 0:
            self.get_logger().info(f"Spatial: {metrics['spatial_hits']}/{metrics['spatial_total']}")
        if metrics['time_total'] > 0:
            self.get_logger().info(f"Time: {metrics['time_hits']}/{metrics['time_total']}")

        os.makedirs(f"{base_dir}/out", exist_ok=True)
        with open(f"{base_dir}/out/eval_seq{self.seq_id}_{self.mode}.json", 'w') as f:
            json.dump(results, f, indent=4)


def main(args=None):
    rclpy.init(args=args)
    node = RosaNaVQAEvaluator()
    try: rclpy.spin(node)
    except KeyboardInterrupt: pass
    finally: node.destroy_node(); rclpy.shutdown()

if __name__ == '__main__':
    main()