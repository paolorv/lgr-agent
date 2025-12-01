import os
import torch
from flask import Flask, request, jsonify
from transformers import AutoProcessor, AutoModelForCausalLM
from PIL import Image
import io

app = Flask(__name__)

# --- GLOBAL CONFIG ---
model_id = "microsoft/Florence-2-base"
device = "cuda" if torch.cuda.is_available() else "cpu"
torch_dtype = torch.float16 if torch.cuda.is_available() else torch.float32

print(f"Initializing Florence-2 Service on {device}...")

# 1. LOAD MODEL (Global variable, loaded once at startup)
# We use 'eager' attention to prevent the 4.46+ transformers crash
model = AutoModelForCausalLM.from_pretrained(
    model_id, 
    torch_dtype=torch_dtype, 
    trust_remote_code=True,
    attn_implementation="eager"
).to(device)

processor = AutoProcessor.from_pretrained(
    model_id, 
    trust_remote_code=True
)

print("Florence-2 Service Ready!")

def run_inference(image, task_prompt):
    """Helper to run the model on a PIL Image"""
    # Ensure RGB
    if image.mode != "RGB":
        image = image.convert("RGB")

    inputs = processor(text=task_prompt, images=image, return_tensors="pt").to(device, torch_dtype)

    generated_ids = model.generate(
        input_ids=inputs["input_ids"],
        pixel_values=inputs["pixel_values"],
        max_new_tokens=1024,
        do_sample=False,
        num_beams=3,
    )

    generated_text = processor.batch_decode(generated_ids, skip_special_tokens=False)[0]
    parsed_answer = processor.post_process_generation(
        generated_text, 
        task=task_prompt, 
        image_size=(image.width, image.height)
    )
    return parsed_answer

@app.route("/caption", methods=["POST"])
def caption():
    """
    Endpoint to receive an image and return a caption.
    Expects 'file' in multipart/form-data.
    Optional: 'task' form field (default: <MORE_DETAILED_CAPTION>)
    """
    if 'file' not in request.files:
        return jsonify({"error": "No file part provided"}), 400
    
    file = request.files['file']
    task = request.form.get("task", "<MORE_DETAILED_CAPTION>")
    
    if file.filename == '':
        return jsonify({"error": "No file selected"}), 400

    try:
        # Load image from bytes
        image = Image.open(io.BytesIO(file.read()))
        
        # Run inference
        result = run_inference(image, task)
        
        # Return JSON
        return jsonify({
            "task": task,
            "result": result[task] # Extract just the text/data
        })

    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route("/health", methods=["GET"])
def health():
    return jsonify({"status": "ok", "gpu": torch.cuda.get_device_name(0)}), 200

if __name__ == "__main__":
    # Host 0.0.0.0 is required for Docker containers to be accessible
    app.run(host="0.0.0.0", port=8001)