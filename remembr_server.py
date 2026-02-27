@app.route("/query", methods=["POST"])
def query():
    data = request.get_json()
    query_text = data.get("query", "")
    if not query_text:
        return jsonify({"error": "No query provided"}), 400
    try:
        # 1. Let the agent generate the conversational text
        response = ltm_agent.query(query_text)
        
        # 2. Query the memory directly to get the closest MemoryItem
        # (Replace .search or .retrieve with whatever method your MilvusMemory uses)
        retrieved_memories = memory.search(query_text, top_k=1) 
        
        pos_list = None
        if retrieved_memories:
            raw_pos = retrieved_memories[0].position
            
            # 3. Handle the NumPy array conversion for jsonify
            if hasattr(raw_pos, "tolist"):
                pos_list = raw_pos.tolist()
            elif isinstance(raw_pos, (list, tuple)):
                pos_list = list(raw_pos)

        return jsonify({
            "text": response.text,
            "position": pos_list
        })
        
    except Exception as e:
        return jsonify({"error": str(e)}), 500