import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/satoimo/ros2_LEDFACE_ws/firmware/dev_ws/install/ament_copyright'
