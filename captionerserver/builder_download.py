from transformers import AutoModelForCausalLM, AutoProcessor
import torch

model_id = "microsoft/Florence-2-large"
print(f"Pre-downloading {model_id}...")

# Download model and processor to default cache directory (~/.cache/huggingface)
AutoModelForCausalLM.from_pretrained(model_id, trust_remote_code=True)
AutoProcessor.from_pretrained(model_id, trust_remote_code=True)

print("Download complete.")