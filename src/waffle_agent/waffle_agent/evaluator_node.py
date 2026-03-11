import os
import json
import time
import csv
import rclpy
from rclpy.node import Node
import numpy as np
import dotenv

# LangChain Imports
from langchain_openai import ChatOpenAI
from langchain.agents import initialize_agent, AgentType
from langchain.callbacks.base import BaseCallbackHandler
#from langchain.schema import SystemMessage

# Explicitly import your tools
from waffle_agent.tools.waffle import (
    init_waffle_tools,
    query_graph_memory_semantical, 
    query_graph_memory_positional,
    query_graph_memory_by_time,
    query_long_term_memory 
)

class LLMTrackingCallbackHandler(BaseCallbackHandler):
    """Tracks the agent's thought process and monitors VectorDB fallback usage."""
    def __init__(self, logger):
        self.logger = logger
        self.used_ltm_in_current_q = False

    def on_agent_action(self, action, **kwargs):
        self.logger.info(f"\n[LLM THOUGHT] {action.log.strip()}")

    def on_tool_start(self, serialized, input_str, **kwargs):
        # Safely extract the tool name, checking kwargs first, then serialized dict
        tool_name = kwargs.get('name')
        if tool_name is None:
            tool_name = serialized.get('name', '')
            
        # Convert to string to guarantee .lower() won't crash on a NoneType
        tool_name = str(tool_name).lower()
        
        # If the tool is your Vector DB/ReMEmbR tool, flag the fallback!
        if 'long_term' in tool_name or 'remembr' in tool_name or 'vector' in tool_name:
            self.used_ltm_in_current_q = True

    # ---> ADD THIS FUNCTION <---
    def on_tool_end(self, output, **kwargs):
        # This prints the EXACT string the tool passes back to the LLM
        self.logger.info(f"\n[TOOL OUTPUT] {output}")

class RosaNaVQAEvaluator(Node):
    def __init__(self):
        super().__init__('rosa_navqa_evaluator')
        
        # --- Parameters ---
        self.declare_parameter('sequence_id', 0)
        self.declare_parameter('memory_mode', 'both') # 'graph', 'remembr', or 'both'
        self.declare_parameter('vlm_name', 'Florence2-large')
        
        self.seq_id = str(self.get_parameter('sequence_id').value)

        # ---> CRITICAL FIX: Clean the string so "graph," becomes "graph"
        # raw_mode = str(self.get_parameter('memory_mode').value)
        # self.mode = raw_mode.replace(',', '').strip().lower()


        self.mode = self.get_parameter('memory_mode').value
        self.vlm_name = self.get_parameter('vlm_name').value

        init_waffle_tools(self)

        # --- Explicitly Handle Tool Modalities ---
        self.tools = []
        if self.mode in ['graph', 'both']:
            self.tools.extend([query_graph_memory_semantical, query_graph_memory_positional, query_graph_memory_by_time])
        if self.mode in ['remembr', 'both']:
            self.tools.append(query_long_term_memory)
            
        self.get_logger().info(f"Initializing Evaluator | Seq: {self.seq_id} | Mode: {self.mode} | VLM: {self.vlm_name}")
        self.get_logger().info(f"Explicit Tools loaded: {[t.name for t in self.tools]}")

        # --- MERGED LLM SETUP (from llm.py) ---
        dotenv.load_dotenv(dotenv.find_dotenv())
        api_key = os.getenv("OPENAI_API_KEY")
        if not api_key:
            self.get_logger().error("Environment variable OPENAI_API_KEY is not set.")
            raise ValueError("OPENAI_API_KEY is missing.")

        self.llm = ChatOpenAI(
            model_name="gpt-4o",
            temperature=0.0,
            max_tokens=None,
            timeout=None,
            max_retries=8, # Matched to max_iterations to prevent crash on API failure
            openai_api_key=api_key,
            streaming=False
        )
        
        # --- Define the strict System Prompt ---
        # self.system_prompt = """
        # You are EmbodiedLGR, an autonomous robotic agent evaluating your memory of a past sequence.
        # You must use your provided memory tools to answer the user's spatial and temporal questions.
        
        # CRITICAL TOOL USAGE INSTRUCTION:
        # If you decide to use the query_long_term_memory tool (if it's defined), you MUST pass the user's FULL, EXACT original question as the tool input. 
        # Do not summarize or alter the question when querying that specific tool.

        # CRITICAL: Whenever you're not absolutely sure about your answer from graph retrieval, ALWAYS resort to query_long_term_memory tool if defined.
        # """

        # GOOD ONE
        # self.system_prompt = """
        # You are EmbodiedLGR, an autonomous robotic agent evaluating your memory of a past memory sequence you observed.
        # You must use ONLY your provided memory retrieval tools to answer the user's spatial and temporal questions.
        
        # CRITICAL INSTRUCTIONS:
        # 1. YOU MUST ALWAYS USE AT LEAST ONE MEMORY TOOL TO GATHER MEMORY INFORMATION BEFORE REPLYING.
        # 2. YOU CAN NOT REQUEST ADDITIONAL INFORMATION. YOU CAN ONLY PROVIDE THE FINAL ANSWER IN JSON FORMAT.
        # 3. ONLY use the tools explicitly provided to you below. DO NOT hallucinate or invent tools like 'search', 'calculate_time_difference', or 'geolocation_lookup'. Invocating any other tool will result in a catastrophic failure.
        # 4. To 'WHEN' questions, you ALWAYS reply with time in the format '2023-01-16 16:02:47'. To 'WHERE' questions, you ALWAYS reply with '[x,y,z]' positions.
        # 5. If you decide to use the query_long_term_memory tool, you MUST pass the user's FULL, EXACT original question as the tool input.
        # 6. Whenever you're not absolutely sure about your answer from graph retrieval, you can resort to the query_long_term_memory tool.
        # 7. If you cannot determine the answer, you MUST still use the standard 'Final Answer' action providing your best guess on what you have retrieved. Do not output plain conversational text.
        # 8. Questions provided to you are always valid and non-contradictory. If you cannot answer the question, you must STILL use the strict JSON format with the action "Final Answer". NEVER output plain conversational text.


        # === REQUIRED FORMATTING ===
        # Your responses must ALWAYS be a single JSON block containing an "action" and "action_input". 
        # Here are the ONLY allowed formats:

        # To search the graph memory by an object's name or semantics:
        # ```json
        # {{
        #     "action": "query_graph_memory_semantical",
        #     "action_input": "red fire hydrant"
        # }}
        # ```

        # To search the graph memory by a specific [x, y, z] position:
        # ```json
        # {{
        #     "action": "query_graph_memory_positional",
        #     "action_input": "[-0.36, 0.05, -0.01]"
        # }}
        # ```

        # To search the graph memory by a specific timestamp:
        # ```json
        # {{
        #     "action": "query_graph_memory_by_time",
        #     "action_input": "2023-01-16 16:02:47"
        # }}
        # ```

        # To use the Long Term Memory (ReMEmbR / VectorDB) tool (YOU MUST PASS THE FULL EXACT QUESTION YOU RECEIVED):
        # ```json
        # {{
        #     "action": "query_long_term_memory",
        #     "action_input": "Where did you see a red fire hydrant?"
        # }}
        # ```

        # When you have the final answer, OR if you cannot answer the question based on the memory:
        # ```json
        # {{
        #     "action": "Final Answer",
        #     "action_input": "Your final descriptive answer here. (e.g., 'You saw the red fire hydrant at [-0.36, 0.05, -0.01]' OR 'I cannot determine the answer based on the provided memory.')"
        # }}
        # ```
        # ===========================
        # """


        # self.system_prompt = """
        # You are EmbodiedLGR, an autonomous robotic agent evaluating your memory of a past sequence you observed.
        # You must use ONLY your provided memory retrieval tools to answer the user's spatial and temporal questions.
        
        # CRITICAL INSTRUCTIONS:
        # 1. YOU MUST ALWAYS USE AT LEAST ONE MEMORY TOOL TO GATHER MEMORY INFORMATION BEFORE REPLYING.
        # 2. YOU CAN NOT REQUEST ADDITIONAL INFORMATION. YOU CAN ONLY PROVIDE THE FINAL ANSWER.
        # 3. ONLY use the tools explicitly provided to you below. DO NOT hallucinate or invent tools like 'search' or 'calculate_time_difference'.
        # 4. To 'WHEN' questions, you ALWAYS reply with time in the format '2023-01-16 16:02:47'. To 'WHERE' questions, you ALWAYS reply with '[x,y,z]' positions.
        # 5. If you decide to use the query_long_term_memory tool, you MUST pass the user's FULL, EXACT original query as the tool input, ALWAYS PASSING also YOUR CURRENT POSITION, WHEN YOU STARTED MOVING, AND THE CURRENT TIME from the QUERY JUST RECEIVED to the query_long_term_memory tool.
        # 5.1. For the query_long_term_memory tool, indeed, if the request is 'You started moving at 2023-01-16 15:56:30. The current time is 2023-01-16 15:58:39 and you are located at [-104.63, 127.53, -3.17]. What color jacket was the person who opened the door for you wearing?` You need to pass the full period 'You started moving at 2023-01-16 15:56:30. The current time is 2023-01-16 15:58:39 and you are located at [-104.63, 127.53, -3.17]. What color jacket was the person who opened the door for you wearing?` so exactly the same full query.
        # 5.2. Always trust what's returned by the query_long_term_memory tool.
        # 6. Whenever you're not absolutely sure about your answer from graph retrieval, you can resort to the query_long_term_memory tool IF available on the tool list.
        # 7. If you cannot determine the answer, you MUST still use the standard 'Final Answer' action providing your best guess.
        # """



        self.system_prompt = """
        You are EmbodiedLGR, an autonomous robotic agent evaluating your memory of a past sequence you observed.
        You must use ONLY your provided memory retrieval tools to answer the user's spatial and temporal questions.
        
        CRITICAL INSTRUCTIONS:
        1. YOU MUST ALWAYS USE AT LEAST ONE MEMORY TOOL TO GATHER MEMORY INFORMATION BEFORE REPLYING.
        2. YOU CAN NOT REQUEST ADDITIONAL INFORMATION. YOU CAN ONLY PROVIDE THE FINAL ANSWER.
        3. ONLY use the tools explicitly provided to you below. DO NOT hallucinate or invent tools like 'search' or 'calculate_time_difference'.
        4. To 'WHEN' questions, you ALWAYS reply with time in the format '2023-01-16 16:02:47'. To 'WHERE' questions, you ALWAYS reply with '[x,y,z]' positions.
        5. If you decide to use the query_long_term_memory tool, you MUST pass the user's FULL, EXACT original query as the tool input, ALWAYS PASSING also YOUR CURRENT POSITION, WHEN YOU STARTED MOVING, AND THE CURRENT TIME from the QUERY JUST RECEIVED to the query_long_term_memory tool.
        5.1. For the query_long_term_memory tool, indeed, if the request is 'You started moving at 2023-01-16 15:56:30. The current time is 2023-01-16 15:58:39 and you are located at [-104.63, 127.53, -3.17]. What color jacket was the person who opened the door for you wearing?` You need to pass the full period 'You started moving at 2023-01-16 15:56:30. The current time is 2023-01-16 15:58:39 and you are located at [-104.63, 127.53, -3.17]. What color jacket was the person who opened the door for you wearing?` so exactly the same full query.
        5.2. Always trust any POSITIVE answer returned by the query_long_term_memory tool. If you call it, any POSITON, TIME or DETAIL returned NEEDS to be your final answer.
        6. Whenever you're not absolutely sure about your answer from graph retrieval, you can resort to the query_long_term_memory tool IF available on the tool list.
        7. If you cannot determine the answer, you MUST still use the standard 'Final Answer' action providing your best guess.
        """


        ### VERY GOOD PROMPT
        # self.system_prompt = """
        # You are EmbodiedLGR, an autonomous robotic agent evaluating your memory of a past memory sequence you observed.
        # You must use ONLY your provided memory retrieval tools to answer the user's spatial and temporal questions.
        
        # CRITICAL INSTRUCTIONS:
        # 1. YOU MUST ALWAYS USE AT LEAST ONE MEMORY TOOL TO GATHER MEMORY INFORMATION BEFORE REPLYING.
        # 2. YOU CAN NOT REQUEST ADDITIONAL INFORMATION. YOU CAN ONLY PROVIDE THE FINAL ANSWER IN JSON FORMAT.
        # 3. You can query the memory graph with the tools query_graph_memory_semantical, query_graph_memory_positional OR query_graph_memory_by_time.
        # 4. ONLY use the tools explicitly provided to you below. DO NOT hallucinate or invent tools like 'search', 'calculate_time_difference', or 'geolocation_lookup'. Invocating any other tool will result in a catastrophic failure.
        # 5. To 'WHEN' questions, you ALWAYS reply with time in the format '2023-01-16 16:02:47'. To 'WHERE' questions, you ALWAYS reply with '[x,y,z]' positions.
        # 6. If you decide to use the query_long_term_memory tool, you MUST pass the user's FULL, EXACT original question as the tool input.
        # 7. Whenever you're not absolutely sure about your answer from graph retrieval, you can resort to the query_long_term_memory tool.
        # 8. If you cannot determine the answer, you MUST still use the standard 'Final Answer' action providing your best guess on what you have retrieved. Do not output plain conversational text.
        # 9. Questions provided to you are always valid and non-contradictory. If you cannot answer the question, you must STILL use the strict JSON format with the action "Final Answer". NEVER output plain conversational text.

        # === REQUIRED FORMATTING ===
        # Your responses must ALWAYS be a single JSON block containing an "action" and "action_input". 
        # Here are the ONLY allowed formats:

        # To search the graph memory by an object's name or semantics:
        # ```json
        # {{
        #     "action": "query_graph_memory_semantical",
        #     "action_input": "red fire hydrant"
        # }}
        # ```

        # To search the graph memory by a specific [x, y, z] position:
        # ```json
        # {{
        #     "action": "query_graph_memory_positional",
        #     "action_input": "[-0.36, 0.05, -0.01]"
        # }}
        # ```

        # To search the graph memory by a specific timestamp:
        # ```json
        # {{
        #     "action": "query_graph_memory_by_time",
        #     "action_input": "2023-01-16 16:02:47"
        # }}
        # ```

        # To use the Long Term Memory (ReMEmbR / VectorDB) tool (YOU MUST PASS THE FULL EXACT QUESTION YOU RECEIVED):
        # ```json
        # {{
        #     "action": "query_long_term_memory",
        #     "action_input": "Where did you see a red fire hydrant?"
        # }}
        # ```

        # When you have the final answer, OR if you cannot answer the question based on the memory:
        # ```json
        # {{
        #     "action": "Final Answer",
        #     "action_input": "Your final descriptive answer here. (e.g., 'You saw the red fire hydrant at [-0.36, 0.05, -0.01]' OR 'I cannot determine the answer based on the provided memory.')"
        # }}
        # ```
        # ===========================
        # """


        # self.system_prompt = """
        # You are EmbodiedLGR, an autonomous robotic agent evaluating your memory of a past sequence.
        # You must use your provided memory tools to answer the user's spatial and temporal questions.
        
        # CRITICAL INSTRUCTIONS:
        # 1. YOU MUST ALWAYS USE AT LEAST ONE MEMORY TOOL TO GATHER MEMORY INFORMATION BEFORE REPLYING.
        # 2. YOU CAN NOT REQUEST ADDITIONAL INFORMATION. YOU CAN ONLY PROVIDE THE FINAL ANSWER IN JSON FORMAT.
        # 3. ONLY use the tools explicitly provided to you. DO NOT hallucinate or invent tools like 'search', 'calculate_time_difference', or 'geolocation_lookup'.
        # 4. To 'WHEN' questions, you ALWAYS reply with time in the format '2023-01-16 16:02:47'. To 'WHERE' questions, you ALWAYS reply with '[x,y,z]` positions.
        # 5. If you decide to use the query_long_term_memory tool, you MUST pass the user's FULL, EXACT original question as the tool input.
        # 6. Whenever you're not absolutely sure about your answer from graph retrieval, ALWAYS resort to the query_long_term_memory tool if defined.
        # 7. If you cannot determine the answer, you MUST still use the standard 'Final Answer' action providing your best guess on what you have retrieved. Do not output plain conversational text.
        # 8. Questions provided to you are always valid and non-contraddictory, If you cannot answer the question, you must STILL use the strict JSON format with the action "Final Answer". NEVER output plain conversational text. 

        # Always follow these rules strictly.

        # === REQUIRED FORMATTING ===
        # Your responses must ALWAYS be a single JSON block containing an "action" and "action_input". 
        # Here are the ONLY allowed formats:

        # To search the graph memory by an object's name or semantics:
        # ```json
        # {
        #     "action": "query_graph_memory_semantical",
        #     "action_input": "red fire hydrant"
        # }
        # ```

        # To search the graph memory by a specific [x, y, z] position:
        # ```json
        # {
        #     "action": "query_graph_memory_positional",
        #     "action_input": "[-0.36, 0.05, -0.01]"
        # }
        # ```

        # To search the graph memory by a specific timestamp:
        # ```json
        # {
        #     "action": "query_graph_memory_by_time",
        #     "action_input": "2023-01-16 16:02:47"
        # }
        # ```

        # To use the Long Term Memory (ReMEmbR / VectorDB) tool (YOU MUST PASS THE FULL EXACT QUESTION YOU RECEIVED):
        # ```json
        # {
        #     "action": "query_long_term_memory",
        #     "action_input": "Where did you see a red fire hydrant?"
        # }
        # ```

        # When you have the final answer, OR if you cannot answer the question based on the memory:
        # ```json
        # {
        #     "action": "Final Answer",
        #     "action_input": "Your final descriptive answer here. (e.g., 'You saw the red fire hydrant at [-0.36, 0.05, -0.01]' OR 'I cannot determine the answer based on the provided memory.')"
        # }
        # ```
        # ===========================
        # """
        
        # --- Initialize the Agent ---
        # We MUST keep this. It glues the tools, prompt, and LLM together.
        # self.agent = initialize_agent(
        #     self.tools, 
        #     self.llm, 
        #     agent=AgentType.CHAT_ZERO_SHOT_REACT_DESCRIPTION, 
        #     verbose=False,
        #     max_iterations=8,
        #     handle_parsing_errors=True,
        #     #agent_kwargs={"system_message": self.system_prompt}
        #     agent_kwargs={
        #         "system_message": SystemMessage(content=self.system_prompt) # <--- Wrapped in SystemMessage
        #     }
        # )
        
        # --- Initialize the Agent ---
        self.agent = initialize_agent(
            self.tools, 
            self.llm, 
            agent=AgentType.CHAT_ZERO_SHOT_REACT_DESCRIPTION,
            verbose=False,
            max_iterations=8,
            # Custom parsing error message forces it back on track if it hallucinates!
            handle_parsing_errors="CRITICAL ERROR: Invalid format or hallucinated tool. You must output a valid JSON block, and you MUST ONLY use the tools explicitly provided in the 'tools' list. Do NOT invent tools like 'search' or 'geolocation'. If you cannot answer, use the 'Final Answer' action.",
            agent_kwargs={
                "system_message_prefix": self.system_prompt  # <--- CRITICAL FIX: The correct variable name and no wrapper!
            }
        )

        # Start Evaluation
        self.run_eval()

    def run_eval(self):
        # 1. Load the QA Dataset
        qa_file = f"/app/NaVQA_eval/remembr/remembr/data/questions/{self.seq_id}/human_qa.json"
        if not os.path.exists(qa_file):
            self.get_logger().error(f"QA file not found at {qa_file}")
            return
            
        with open(qa_file, 'r') as f:
            qa_data = json.load(f).get('data', [])

        results = []
        metrics = {"spatial_hits": 0, "spatial_total": 0, "time_hits": 0, "time_total": 0}
        
        tracker = LLMTrackingCallbackHandler(self.get_logger())
        self.fallback_count = 0 
        overall_question_times = []

        # 2. Main Question Loop
        for qa in qa_data:
            tracker.used_ltm_in_current_q = False 
            
            q_type = qa.get('type', [])
            gt = qa.get('answers', {})
            question_text = qa.get('question', 'No question found')
            
            self.get_logger().info(f"\n=========================================\n[Q] {question_text}")
            start_q_time = time.time()
            
            try:
                # Agent retrieves information
                raw_resp = self.agent.invoke(
                    {"input": question_text}, 
                    config={"callbacks": [tracker]}
                )['output']
                
                self.get_logger().info(f"[LLM RAW ANSWER] {raw_resp.strip()}")
                
                # Second LLM call purely for strict JSON extraction (No ReAct loop to break)
                formatter_prompt = f"""
                You are a data parser. Read the robot's raw answer and extract the facts into strict JSON.
                Original Question: {question_text}
                Robot's Answer: {raw_resp}
                {{
                    "binary": "yes" or "no" or null,
                    "position": [x_float, y_float] or null,
                    "time": time_float_in_seconds or null,
                    "text": "The descriptive answer or null"
                }}
                """
                formatted_json_str = self.llm.invoke(formatter_prompt).content
                formatted_json_str = formatted_json_str.replace('```json', '').replace('```', '').strip()
                pred = json.loads(formatted_json_str)

            except Exception as e:
                self.get_logger().error(f"Agent/Formatting Error: {e}")
                pred = {"binary": None, "position": None, "time": None, "text": "Error/Timeout"}

            if tracker.used_ltm_in_current_q:
                self.fallback_count += 1
                self.get_logger().info("-> Fallback to VectorDB detected for this question.")

            q_elapsed = time.time() - start_q_time
            overall_question_times.append(q_elapsed)
            self.get_logger().info(f"[METRIC] Total Agent Reply Time: {q_elapsed:.2f}s")

            # --- EVALUATION LOGIC ---
            if 'position' in q_type or 'position' in gt:
                metrics['spatial_total'] += 1
                try:
                    if isinstance(pred.get('position'), list) and len(pred['position']) >= 2:
                        err = np.linalg.norm(np.array(pred['position'][:2]) - np.array(gt['position'][:2]))
                        correct = bool(err <= 25.0) 
                    else:
                        err = float('inf') 
                        correct = False
                        
                    metrics['spatial_hits'] += int(correct)
                    self.get_logger().info(f"--> Spatial Err: {err:.2f}m | Correct: {correct}")
                except Exception as e:
                    self.get_logger().error(f"Spatial math error: {e}")

            if 'time' in q_type or 'time' in gt:
                metrics['time_total'] += 1
                try:
                    if pred.get('time') is not None:
                        err = abs(float(pred['time']) - float(gt['time']))
                        correct = bool(err <= 180.0)
                    else:
                        err = float('inf') 
                        correct = False
                        
                    metrics['time_hits'] += int(correct)
                    self.get_logger().info(f"--> Time Err: {err:.2f}s | Correct: {correct}")
                except Exception as e:
                    self.get_logger().error(f"Time math error: {e}")

            safe_uuid = qa.get('UUID', qa.get('uuid', f"unknown_q_{len(results)}"))
            results.append({"uuid": safe_uuid, "question": question_text, "pred": pred, "gt": gt})

        # 3. Calculate Final Sequence Metrics
        total_questions = len(qa_data)
        spatial_acc = (metrics['spatial_hits'] / metrics['spatial_total']) * 100.0 if metrics['spatial_total'] > 0 else 0.0
        temporal_acc = (metrics['time_hits'] / metrics['time_total']) * 100.0 if metrics['time_total'] > 0 else 0.0
        avg_latency = sum(overall_question_times) / len(overall_question_times) if overall_question_times else 0.0
        fallback_perc = (self.fallback_count / total_questions) * 100.0 if total_questions > 0 else 0.0

        self.get_logger().info(f"\n=========================================")
        self.get_logger().info(f"EVALUATION COMPLETE FOR SEQ {self.seq_id}")
        self.get_logger().info(f"Spatial Accuracy: {spatial_acc:.1f}%")
        self.get_logger().info(f"Temporal Accuracy: {temporal_acc:.1f}%")
        self.get_logger().info(f"Avg Latency: {avg_latency:.2f}s")
        self.get_logger().info(f"Fallback Percentage: {fallback_perc:.1f}% ({self.fallback_count}/{total_questions})")
        self.get_logger().info(f"=========================================\n")

        # 4. Export to Master CSV
        csv_file = "/app/NaVQA_eval/remembr/remembr/CSVRESULTS/master_evaluation_results.csv"
        os.makedirs(os.path.dirname(csv_file), exist_ok=True)
        file_exists = os.path.isfile(csv_file)
        
        with open(csv_file, mode='a', newline='') as f:
            writer = csv.writer(f)
            if not file_exists:
                writer.writerow(["Sequence", "VLM", "Configuration", "Positional Accuracy", "Temporal Accuracy", "Retrieval Latency", "Fallback Percentage"])
            
            writer.writerow([self.seq_id, self.vlm_name, self.mode, round(spatial_acc, 2), round(temporal_acc, 2), round(avg_latency, 2), round(fallback_perc, 2)])
            
        dump_file = f"/app/NaVQA_eval/remembr/remembr/out/eval_seq{self.seq_id}_{self.mode}_{self.vlm_name}.json"
        with open(dump_file, 'w') as f:
            json.dump(results, f, indent=4)

def main(args=None):
    rclpy.init(args=args)
    node = RosaNaVQAEvaluator()
    #rclpy.spin(node) 
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
