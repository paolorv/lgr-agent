source /opt/venv/csagent/bin/activate
pip install PyQt5 && pip install PySide2 && pip install catkin_pkg
ros2 run rqt_image_view rqt_image_view /camera/rgb/image_raw