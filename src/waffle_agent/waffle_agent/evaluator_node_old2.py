import os
import json
import time
import csv
import rclpy
from rclpy.node import Node
import numpy as np

# LangChain Imports
from langchain.chat_models import ChatOpenAI
from langchain.agents import initialize_agent, AgentType
from langchain.callbacks.base import BaseCallbackHandler

# Import your tools from your waffle package
# (Ensure this import matches wherever your tools are defined in your workspace)
from waffle_agent.waffle import get_tools

class LLMTrackingCallbackHandler(BaseCallbackHandler):
    """Tracks the agent's thought process and monitors VectorDB fallback usage."""
    def __init__(self, logger):
        self.logger = logger
        self.used_ltm_in_current_q = False

    def on_agent_action(self, action, **kwargs):
        self.logger.info(f"\n[LLM THOUGHT] {action.log.strip()}")

    def on_tool_start(self, serialized, input_str, **kwargs):
        tool_name = kwargs.get('name', '').lower()
        # If the tool is your Vector DB/ReMEmbR tool, flag the fallback!
        if 'long_term' in tool_name or 'remembr' in tool_name or 'vector' in tool_name:
            self.used_ltm_in_current_q = True 

class RosaNaVQAEvaluator(Node):
    def __init__(self):
        super().__init__('rosa_navqa_evaluator')
        
        # --- Parameters ---
        self.declare_parameter('sequence_id', 0)
        self.declare_parameter('memory_mode', 'both') # 'graph', 'remembr', or 'both'
        self.declare_parameter('vlm_name', 'Florence2-large')
        
        self.seq_id = str(self.get_parameter('sequence_id').value)
        self.mode = self.get_parameter('memory_mode').value
        self.vlm_name = self.get_parameter('vlm_name').value

        self.get_logger().info(f"Initializing Evaluator | Seq: {self.seq_id} | Mode: {self.mode} | VLM: {self.vlm_name}")

        # --- LLM & Agent Setup ---
        self.llm = ChatOpenAI(temperature=0.0, model_name="gpt-4o")
        
        # Load the appropriate tools based on the mode
        self.tools = get_tools(self.mode) 
        self.get_logger().info(f"Tools loaded: {[t.name for t in self.tools]}")
        
        self.agent = initialize_agent(
            self.tools, 
            self.llm, 
            agent=AgentType.ZERO_SHOT_REACT_DESCRIPTION, 
            verbose=False,
            max_iterations=8
        )
        
        # Start Evaluation
        self.run_eval()

    def run_eval(self):
        # 1. Load the QA Dataset
        qa_file = f"/NAVQA_eval/remembr/remembr/data/questions/{self.seq_id}/human_qa.json"
        if not os.path.exists(qa_file):
            self.get_logger().error(f"QA file not found at {qa_file}")
            return
            
        with open(qa_file, 'r') as f:
            qa_data = json.load(f).get('data', [])

        results = []
        metrics = {"spatial_hits": 0, "spatial_total": 0, "time_hits": 0, "time_total": 0}
        
        # 2. Initialize tracking variables
        tracker = LLMTrackingCallbackHandler(self.get_logger())
        self.fallback_count = 0 
        overall_question_times = []

        # 3. Main Question Loop
        for qa in qa_data:
            tracker.used_ltm_in_current_q = False # Reset fallback boolean for this question
            
            q_type = qa.get('type', [])
            gt = qa.get('answers', {})
            question_text = qa.get('question', 'No question found')
            
            self.get_logger().info(f"\n=========================================\n[Q] {question_text}")
            start_q_time = time.time()
            
            try:
                # Run the Agent
                raw_resp = self.agent.invoke(
                    {"input": question_text}, 
                    config={"callbacks": [tracker]}
                )['output']
                
                self.get_logger().info(f"[LLM FINAL ANSWER] {raw_resp.strip()}")
                
                # Format to JSON
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
                formatted_json_str = self.llm.invoke(formatter_prompt).content
                formatted_json_str = formatted_json_str.replace('```json', '').replace('```', '').strip()
                pred = json.loads(formatted_json_str)

            except Exception as e:
                self.get_logger().error(f"Agent/Formatting Error: {e}")
                pred = {"binary": None, "position": None, "time": None, "text": "Error/Timeout"}

            # Track if fallback occurred
            if tracker.used_ltm_in_current_q:
                self.fallback_count += 1
                self.get_logger().info("-> Fallback to VectorDB detected for this question.")

            q_elapsed = time.time() - start_q_time
            overall_question_times.append(q_elapsed)
            self.get_logger().info(f"[METRIC] Total Agent Reply Time: {q_elapsed:.2f}s")

            # --- EVALUATION LOGIC ---
            
            # Spatial Evaluation (Threshold: 15.0m based on SpaceLocQA)
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

            # Temporal Evaluation (Threshold: 120.0s based on NaVQA)
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


        # 4. Calculate Final Sequence Metrics
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

        # 5. Export to Master CSV
        csv_file = "/NAVQA_eval/remembr/out/master_evaluation_results.csv"
        os.makedirs(os.path.dirname(csv_file), exist_ok=True)
        file_exists = os.path.isfile(csv_file)
        
        with open(csv_file, mode='a', newline='') as f:
            writer = csv.writer(f)
            if not file_exists:
                # Create headers if file is new
                writer.writerow(["Sequence", "VLM", "Configuration", "Positional Accuracy", "Temporal Accuracy", "Retrieval Latency", "Fallback Percentage"])
            
            writer.writerow([self.seq_id, self.vlm_name, self.mode, round(spatial_acc, 2), round(temporal_acc, 2), round(avg_latency, 2), round(fallback_perc, 2)])
            
        self.get_logger().info(f"Results successfully appended to {csv_file}")
        
        # Save full JSON dump of predictions just in case
        dump_file = f"/NAVQA_eval/remembr/out/eval_seq{self.seq_id}_{self.mode}_{self.vlm_name}.json"
        with open(dump_file, 'w') as f:
            json.dump(results, f, indent=4)

def main(args=None):
    rclpy.init(args=args)
    node = RosaNaVQAEvaluator()
    rclpy.spin(node) # Only strictly necessary if tools require ROS callbacks during execution
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()