### Check Video Driver status:
nvidia-smi
glxinfo | grep "OpenGL renderer"
echo $DISPLAY
echo "###########################################################################"

# Create a script to launch Gazebo with correct env
cat > /usr/local/bin/gz-nvidia << 'EOF'
#!/bin/bash
export __NV_PRIME_RENDER_OFFLOAD=1
export __GLX_VENDOR_LIBRARY_NAME=nvidia
exec gz "$@"
EOF
chmod +x /usr/local/bin/gz-nvidia

# Now run Gazebo
gz-nvidia sim empty.sdf