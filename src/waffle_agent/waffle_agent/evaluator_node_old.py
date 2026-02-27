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
        
        CRITICAL: Your final output MUST be a JSON block containing exactly these keys. 
        If a field is not asked for, set it to null.
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
            self.tools, self.llm, 
            agent=AgentType.CHAT_ZERO_SHOT_REACT_DESCRIPTION, 
            agent_kwargs={"system_message": self.system_prompt},
            max_iterations=5, verbose=False
        )

        # Run in thread so Langchain doesn't block ROS service callbacks
        self.eval_thread = threading.Thread(target=self.run_eval)
        self.eval_thread.start()

    def run_eval(self):
        # Force the absolute path based on your container's mount structure
        base_dir = "/app/NaVQA_eval/remembr/remembr"
        qa_file = f"{base_dir}/data/questions/{self.seq_id}/human_qa.json"
        
        if not os.path.exists(qa_file):
            self.get_logger().error(f"CRITICAL: Cannot find QA file at {qa_file}")
            return
            
        with open(qa_file, 'r') as f:
            qa_data = json.load(f)['data']

        results = []
        metrics = {"spatial_hits": 0, "spatial_total": 0, "time_hits": 0, "time_total": 0}

        for qa in qa_data:
            q_type = qa['type']
            gt = qa['answers']
            
            self.get_logger().info(f"\n[Q] {qa['question']}")
            
            try:
                raw_resp = self.agent.run(qa['question'])
                json_str = re.search(r"```json(.*?)```", raw_resp, re.DOTALL | re.IGNORECASE).group(1)
                pred = json.loads(json_str)
            except Exception as e:
                self.get_logger().error(f"Agent Formatting Error: {e}")
                pred = {"position": None, "time": None, "text": raw_resp}

            # 1. Evaluate Spatial (Threshold = 2.0m)
            if 'position' in q_type and pred.get('position'):
                err = np.linalg.norm(np.array(pred['position'][:2]) - np.array(gt['position'][:2]))
                correct = bool(err <= 2.0)
                metrics['spatial_total'] += 1
                metrics['spatial_hits'] += int(correct)
                self.get_logger().info(f"Spatial Err: {err:.2f}m | Correct: {correct}")

            # 2. Evaluate Temporal (Threshold = 15.0s)
            if 'time' in q_type and pred.get('time'):
                err = abs(pred['time'] - gt['time'])
                correct = bool(err <= 15.0)
                metrics['time_total'] += 1
                metrics['time_hits'] += int(correct)
                self.get_logger().info(f"Time Err: {err:.2f}s | Correct: {correct}")

            results.append({"uuid": qa['UUID'], "question": qa['question'], "pred": pred, "gt": gt})

        self.get_logger().info("\n=== RESULTS ===")
        if metrics['spatial_total'] > 0:
            self.get_logger().info(f"Spatial: {metrics['spatial_hits']}/{metrics['spatial_total']}")
        if metrics['time_total'] > 0:
            self.get_logger().info(f"Time: {metrics['time_hits']}/{metrics['time_total']}")

        os.makedirs("./out", exist_ok=True)
        with open(f"./out/eval_seq{self.seq_id}_{self.mode}.json", 'w') as f:
            json.dump(results, f, indent=4)

def main(args=None):
    rclpy.init(args=args)
    node = RosaNaVQAEvaluator()
    try: rclpy.spin(node)
    except KeyboardInterrupt: pass
    finally: node.destroy_node(); rclpy.shutdown()

if __name__ == '__main__':
    main()