import os
import torch
import gc
import io
from flask import Flask, request, jsonify
from transformers import AutoProcessor, AutoModelForCausalLM
from PIL import Image

app = Flask(__name__)

# --- GLOBAL CONFIG ---
model_id = "microsoft/Florence-2-base-ft"
device = "cuda" if torch.cuda.is_available() else "cpu"
torch_dtype = torch.float16 if torch.cuda.is_available() else torch.float32

print(f"Initializing Florence-2 Service on {device}...")

# LOAD MODEL
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

@torch.inference_mode()
def run_inference(image, task_prompt):
    """Process frame with selected task from input_ids"""
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
    
    # --- CRITICAL TENSOR CLEANUP ---
    del inputs
    del generated_ids
    if torch.cuda.is_available():
        torch.cuda.empty_cache()
        
    return parsed_answer


# def process_request(request_obj, default_task):
#     """Helper to handle image loading, inference, and memory clearing for all endpoints."""
#     if 'file' not in request_obj.files:
#         return jsonify({"error": "No file part provided"}), 400
    
#     file = request_obj.files['file']
#     task = request_obj.form.get("task", default_task)
    
#     if file.filename == '':
#         return jsonify({"error": "No file selected"}), 400

#     try:
#         # Load image safely
#         raw_bytes = file.read()
#         image = Image.open(io.BytesIO(raw_bytes))
        
#         # Run inference
#         result = run_inference(image, task)
        
#         # --- CRITICAL RAM CLEANUP ---
#         image.close()
#         del raw_bytes
#         gc.collect()
        
#         return jsonify({
#             "task": task,
#             "result": result[task]
#         })
#     except Exception as e:
#         return jsonify({"error": str(e)}), 500

def process_request(request_obj, default_task):
    if 'file' not in request_obj.files:
        return jsonify({"error": "No file part provided"}), 400

    file = request_obj.files['file']
    task = request_obj.form.get("task", default_task)

    if file.filename == '':
        return jsonify({"error": "No file selected"}), 400

    try:
        raw_bytes = file.read()
        file.close()                          # release file handle immediately
        image = Image.open(io.BytesIO(raw_bytes))
        
        result = run_inference(image, task)
        
        result_value = result[task]           # extract before freeing
        del result

        image.close()
        del image                             # PIL buffer cleanup
        del raw_bytes
        gc.collect()
        
        return jsonify({"task": task, "result": result_value})
    except Exception as e:
        gc.collect()                          # also collect on error paths
        return jsonify({"error": str(e)}), 500


@app.route("/caption", methods=["POST"])
def caption():
    return process_request(request, "<MORE_DETAILED_CAPTION>")

@app.route("/labels", methods=["POST"])
def labels():
    # Regular Object Detection (Usually 5-15 objects)
    return process_request(request, "<OD>")

@app.route("/dlabels", methods=["POST"])
def dlabels():
    # Dense Region Captioning (Usually 30-100 descriptive boxes)
    return process_request(request, "<DENSE_REGION_CAPTION>")

@app.route("/health", methods=["GET"])
def health():
    return jsonify({"status": "ok", "gpu": torch.cuda.get_device_name(0)}), 200

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8001, threaded=False)
