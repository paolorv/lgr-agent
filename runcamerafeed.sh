#source /opt/venv/csagent/bin/activate
#/usr/bin/python3 -m pip install PyQt5 --break-system-packages && /usr/bin/python3 -m pip install PySide2 --break-system-packages && /usr/bin/python3 -m pip install catkin_pkg --break-system-packages
#ros2 run rqt_image_view rqt_image_view /camera/image_raw

source /opt/venv/csagent/bin/activate
pip install PyQt5 && pip install PySide2 && pip install catkin_pkg
ros2 run rqt_image_view rqt_image_view /camera/image_raw

# OTHERWISE: use rviz2