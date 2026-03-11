#!/usr/bin/env python3
import asyncio
import os
import sys
import threading
import logging
from datetime import datetime

import dotenv
import pyinputplus as pyip
import rclpy
from rclpy.executors import MultiThreadedExecutor

# --- FIXED IMPORTS FOR LANGCHAIN 0.3 ---
from langchain_core.tools import tool, Tool
# ---------------------------------------

from rich.console import Console, Group
from rich.live import Live
from rich.markdown import Markdown
from rich.panel import Panel
from rich.text import Text
from rosa import ROSA

# --- CORRECTED IMPORTS FOR ROS 2 PACKAGING ---
import waffle_agent.tools.waffle as waffle_tools
from waffle_agent.help import get_help
from waffle_agent.llm import get_llm
from waffle_agent.prompts import get_prompts
# ---------------------------------------------
logger = None  # Global logger variable (Logging is enabled only for streaming=False)


@tool
def cool_turtle_tool():
    """Tool example."""
    return "This is just a tool example"

class TurtleAgent(ROSA):
    def __init__(self, ros_node, streaming: bool = False, verbose: bool = True):
        self.__blacklist = ["master", "docker"]
        self.__prompts = get_prompts()
        self.__llm = get_llm(streaming=streaming)
        self.__streaming = streaming
        self.ros_node = ros_node

        # Initialize waffle tools with the node
        waffle_tools.init_waffle_tools(self.ros_node)

        blast_off = Tool(
            name="blast_off",
            func=self.blast_off,
            description="Make the robot blast off!",
        )

        super().__init__(
            ros_version=2,
            llm=self.__llm,
            tools=[cool_turtle_tool, blast_off],
            tool_packages=[waffle_tools],
            blacklist=self.__blacklist,
            prompts=self.__prompts,
            verbose=verbose,
            accumulate_chat_history=True,
            streaming=streaming,
        )

        self.examples = [
            "Show me around the environment.",
            "Request the robot where's the closest building.",
            "Draw a 5-point star from your current position.",
        ]

        self.command_handler = {
            "help": lambda: self.submit(get_help(self.examples)),
            "examples": lambda: self.submit(self.choose_example()),
            "clear": lambda: self.clear(),
        }

    def blast_off(self, input: str):
        return f"""
        Ok, we're blasting off at the speed of light!
        <ROSA_INSTRUCTIONS>
            You should now use your tools to make the turtle move around the screen at high speeds.
        </ROSA_INSTRUCTIONS>
        """

    @property
    def greeting(self):
        greeting = Text("\n EMBODIED-LGR-AGENT AWAITING REQUEST:\n")
        greeting.stylize("frame bold green")
        greeting.append(f"Try {', '.join(self.command_handler.keys())} or exit.", style="italic")
        return greeting

    def choose_example(self):
        return pyip.inputMenu(
            self.examples,
            prompt="\nEnter your choice and press enter: \n",
            numbered=True,
            blank=False,
            timeout=60,
            default="1",
        )

    async def clear(self):
        self.clear_chat()
        self.last_events = []
        self.command_handler.pop("info", None)
        os.system("clear")

    def get_input(self, prompt: str):
       
        print("", end="", flush=True)  # Print here to force flush buffer in case of lag
        return pyip.inputStr(prompt, default="help")

    async def run(self):
        await self.clear()
        console = Console()
        while True:
            console.print(self.greeting)
            user_input = self.get_input("> ")

            if user_input == "exit":
                break
            elif user_input in self.command_handler:
                await self.command_handler[user_input]()
            else:
                await self.submit(user_input)

    async def submit(self, query: str):
        # print(f"DEBUG: Received query: {query}") 
        if self.__streaming: 
            await self.stream_response(query)
        else: 
            self.print_response(query)
            
    def print_response(self, query: str):
        """Submit the query to the agent and print the response."""
        logger = logging.getLogger(__name__)
        logger.info(f"ROSA User Query: {query}")

        try:
            response = self.invoke(query)
            logger.info(f"ROSA LLM response: {response}")
        except Exception as e:
            print(f"ERROR from LLM: {e}")
            logger.error(f"ROSA LLM error: {e}")
            return

        # Display returned response using Rich
        console = Console()
        with Live(console=console, auto_refresh=True, vertical_overflow="visible") as live:
            content_panel = Panel(Markdown(response), title="EmbodiedLGR-Agent Response", border_style="bold green")
            live.update(content_panel, refresh=True)


    #### Async components for streaming response (used if streaming=True) ####
    async def stream_response(self, query: str):
        console = Console()
        content = ""
        self.last_events = []
        panel = Panel("", title="Streaming Response", border_style="green")

        with Live(panel, console=console, auto_refresh=False) as live:
            async for event in self.astream(query):
                event["timestamp"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
                if event["type"] == "token":
                    content += event["content"]
                    panel.renderable = Markdown(content)
                    live.refresh()
                elif event["type"] in ["tool_start", "tool_end", "error"]:
                    self.last_events.append(event)
                elif event["type"] == "final":
                    content = event["content"]
                    footer = "\n\nType 'info' for details on how I got my answer." if self.last_events else ""
                    panel.renderable = Markdown(content + footer)
                    panel.title = "Final Response"
                    live.refresh()

        if self.last_events:
            self.command_handler["info"] = self.show_event_details
        else:
            self.command_handler.pop("info", None)

    async def show_event_details(self):
        console = Console()
        if not self.last_events:
            console.print("[yellow]No events to display.[/yellow]")
            return
        console.print(Markdown("# Tool Usage and Events"))
        for event in self.last_events:
            # (Simple debug print if needed, or full implementation)
            pass



### Logging with Timestamps
#def setup_logging():
#    # Create a logs directory if it doesn't exist
#    log_folder = 'logs'
#    os.makedirs(log_folder, exist_ok=True) #

    # Set timestamp
#    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
#    log_filename = f"interaction_{timestamp}.log"
#    full_log_path = os.path.join(log_folder, log_filename)

#    logging.basicConfig(
#        filename=full_log_path,
#        filemode='a',      # Append mode
#        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
#        level=logging.INFO
#    )
    
#    print(f"Logging initialized. Saving to: {full_log_path}")

### Incremental Log File Naming
def setup_logging():
    # Create a logs directory if it doesn't exist
    log_folder = 'logs'
    os.makedirs(log_folder, exist_ok=True) 

    # Find the next available incremental log file
    log_counter = 1
    while True:
        log_filename = f"ROSAinteraction_{log_counter}.log"
        full_log_path = os.path.join(log_folder, log_filename)
        
        # If file doesn't exist, we found our number. Break the loop.
        if not os.path.exists(full_log_path):
            break
            
        # Otherwise, check the next number
        log_counter += 1

    # Configure logging
    logging.basicConfig(
        filename=full_log_path,
        filemode='a',      # Append mode
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        level=logging.INFO
    )
    
    print(f"Logging initialized. Saving to: {full_log_path}")
    
    # Return the path so we can send it to the Flask server later
    return full_log_path


def main(args=None):
    # Setup ROS 2 and load environment variables
    rclpy.init(args=args)
    dotenv.load_dotenv(dotenv.find_dotenv())

    # Setup logging
    setup_logging()
    logger = logging.getLogger(__name__)
    logger.info("BEGINNING OF INTERACTION - LOGGING STARTED")

    ### Start ROS 2 Node and CuriosityAgent ###
    node = rclpy.create_node("waffle_agent")
    node.declare_parameter("streaming", False)
    streaming = node.get_parameter("streaming").value
    
    turtle_agent = TurtleAgent(ros_node=node, verbose=False, streaming=streaming)

    executor = MultiThreadedExecutor()
    executor.add_node(node)
    spin_thread = threading.Thread(target=executor.spin, daemon=True)
    spin_thread.start()

    try:
        asyncio.run(turtle_agent.run())
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()
        spin_thread.join(timeout=1.0)

if __name__ == "__main__":
    main()