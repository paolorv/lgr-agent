FROM python:3.10-slim

# Prevent python from writing pyc files or buffering stdout
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

WORKDIR /app

# 1. Install System Dependencies (git is needed for some huggingface ops)
RUN apt-get update && apt-get install -y \
    git \
    && rm -rf /var/lib/apt/lists/*

# 2. Install Python Dependencies
# CHECK CUDA VERSION AND ADJUST TORCH: THEY NEED TO MATCH IN PRE-COMPILATION
#RUN pip install --no-cache-dir \
#    torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu121

# IF RUNNING ON CUDA 13.0 USE THIS INSTEAD:
RUN pip install --pre torch torchvision torchaudio --index-url https://download.pytorch.org/whl/nightly/cu130


RUN pip install --no-cache-dir \
    flask \
    transformers==4.45.2 \
    timm \
    einops \
    pillow \
    sentencepiece

# 3. Model Pre-Caching (Crucial for Docker)
# This prevents downloading 1.5GB every time the container starts.
COPY builder_download.py .
RUN python builder_download.py && rm builder_download.py

# 4. Copy Server Code
COPY captioner_server.py .

# 5. Expose the port
EXPOSE 8001

RUN export MALLOC_ARENA_MAX=2

# 6. Run the server
CMD ["python", "captioner_server.py"]
