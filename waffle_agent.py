#!/usr/bin/env python3
import asyncio
import os
import sys
import threading
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

@tool
def cool_turtle_tool():
    """A cool turtle tool that doesn't really do anything."""
    return "This is a cool turtle tool! It doesn't do anything, but it's cool."

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
            description="Make the turtle blast off!",
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
            "Give me a ROS tutorial using the turtlesim.",
            "Show me how to move the turtle forward.",
            "Draw a 5-point star using the turtle.",
            "Teleport to (3, 3) and draw a small hexagon.",
            "Give me a list of nodes, topics, services, params, and log files.",
            "Change the background color to light blue and the pen color to red.",
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
        greeting = Text("\nWAFFLE AGENT AWAITING COMMAND:\n")
        greeting.stylize("frame bold blue")
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
        # Added a print here to force flush buffer in case of lag
        print("", end="", flush=True)
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
            # print("DEBUG: Starting stream response...") 
            await self.stream_response(query)
        else:
            # print("DEBUG: Starting standard response...") 
            self.print_response(query)
            
    def print_response(self, query: str):
        """Submit the query to the agent and print the response."""
        
        # 1. Get the response from LLM
        # print("DEBUG: Invoking LLM chain (this might take time)...") 
        try:
            response = self.invoke(query)
            # print("DEBUG: Response received!")
        except Exception as e:
            print(f"ERROR from LLM: {e}")
            return

        # 2. Display it using Rich (This was missing in your new file!)
        console = Console()
        with Live(console=console, auto_refresh=True, vertical_overflow="visible") as live:
            content_panel = Panel(Markdown(response), title="Final Response", border_style="green")
            live.update(content_panel, refresh=True)

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

def main(args=None):
    rclpy.init(args=args)
    dotenv.load_dotenv(dotenv.find_dotenv())

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