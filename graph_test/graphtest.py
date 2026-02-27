import networkx as nx
import numpy as np
import matplotlib.pyplot as plt  # <--- THIS WAS MISSING
from sentence_transformers import SentenceTransformer

# Embedding model
model = SentenceTransformer('sentence-transformers/all-MiniLM-L6-v2')

# Graph
robot_memory = nx.Graph()

def add_memory_node(graph, label, position):
    embedding = model.encode(label)
    node_id = len(graph.nodes)
    graph.add_node(node_id, 
                   label=label, 
                   pos=position, 
                   embedding=embedding)
    return node_id

# Example: Adding memory entries
n1 = add_memory_node(robot_memory, "charging station", (1.0, 1.0, 0.0))
n2 = add_memory_node(robot_memory, "office desk", (5.2, 1.5, 0.0))
n3 = add_memory_node(robot_memory, "blue coffee mug", (5.5, 1.2, 0.8))
n4 = add_memory_node(robot_memory, "red coffee mug", (2.0, 3.0, 0.8))
n5 = add_memory_node(robot_memory, "green coffee mug", (1.0, 2.0, 0.0))

# Spatial Relationships (Edges)
# robot_memory.add_edge(n2, n3, relationship="on_top_of")

def find_by_semantics(graph, query_text, top_k=1):
    query_vec = model.encode(query_text)
    scores = []
    
    for node, data in graph.nodes(data=True):
        # Calculate cosine similarity: (A · B) / (||A|| * ||B||)
        sim = np.dot(query_vec, data['embedding']) / (np.linalg.norm(query_vec) * np.linalg.norm(data['embedding']))
        scores.append((node, sim))
    
    # Sort by highest similarity
    return sorted(scores, key=lambda x: x[1], reverse=True)[:top_k]

best_match = find_by_semantics(robot_memory, "something where to sit")
print(f"Closest match: {robot_memory.nodes[best_match[0][0]]['label']}")



def find_by_spatial_proximity(graph, position, top_k=1):
    scores = []
    
    for node, data in graph.nodes(data=True):
        node_pos = np.array(data['pos'])
        dist = np.linalg.norm(np.array(position) - node_pos)
        scores.append((node, dist))
    
    # Sort by closest distance
    return sorted(scores, key=lambda x: x[1])[:top_k]


### --- VISUALIZATION SECTION ---

# Use a layout engine so nodes aren't on top of each other
layout = nx.spring_layout(robot_memory)

# Draw the nodes
nx.draw(robot_memory, layout, with_labels=False, node_color='lightblue', node_size=2000)

# Draw the labels (the text names)
labels = nx.get_node_attributes(robot_memory, 'label')
nx.draw_networkx_labels(robot_memory, layout, labels, font_size=10)

# Show the plot
#print("Opening graph window...")
#plt.show()
print("Saving graph to robot_memory.png...")
plt.savefig("robot_memory.png")
print("Done!")



