# 1. Use the specific NVIDIA L4T PyTorch base image for JetPack 5.1.2 (R35.4.1)
FROM dustynv/l4t-pytorch:r35.4.1

# Prevent python from writing pyc files or buffering stdout
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

WORKDIR /app

# 2. Install System Dependencies (git is needed for Hugging Face ops)
RUN apt-get update && apt-get install -y \
    git \
    && rm -rf /var/lib/apt/lists/*

# 3. Install Python Dependencies
# NOTE: torch, torchvision, and torchaudio are intentionally OMITTED here 
# because they are already compiled for Jetson's GPU inside the base image.
#RUN pip3 install --no-cache-dir \
#    flask \
#    transformers==4.45.2 \
#    timm \
#    einops \
#    pillow \
#    sentencepiece


# 3. Install Python Dependencies on JETSON
RUN pip3 install --no-cache-dir \
    flask \
    transformers==4.45.2 \
    accelerate \
    timm \
    einops \
    pillow \
    sentencepiece

# 4. Model Pre-Caching (Crucial for Docker)
# This prevents downloading the Florence-2 weights every time the container starts.
COPY builder_download.py .
RUN python3 builder_download.py && rm builder_download.py

# 5. Copy Server Code
COPY captioner_server.py .

# 6. Expose the port
EXPOSE 8001

# 7. Run the server
CMD ["python3", "captioner_server.py"]