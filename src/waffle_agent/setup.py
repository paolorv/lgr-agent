from setuptools import setup
import os
from glob import glob

package_name = 'waffle_agent'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name, f'{package_name}.tools'],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Paolo Riva',
    maintainer_email='paolo13.riva@mail.polimi.it',
    description='LLM Agent for Waffle Robot',
    license='Apache-2.0',
    # CHANGED: tests_require is deprecated. Use extras_require for tests.
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            # Ensure these paths exist: waffle_agent/waffle_agent.py -> main()
            'agent = waffle_agent.waffle_agent:main',
            'captioner_node = waffle_agent.captioner_node:main', 
            'memory_builder_node = waffle_agent.memory_builder_node:main',
            'objectdetection_node = waffle_agent.objectdetection_node:main',
            'graphmemory_manager = waffle_agent.graphmemory_manager:main',
            'coda_player = waffle_agent.coda_player:main',
            'evaluator_node = waffle_agent.evaluator_node:main',
            'json_memory_populator = waffle_agent.json_memory_populator:main',
        ],
    },
)