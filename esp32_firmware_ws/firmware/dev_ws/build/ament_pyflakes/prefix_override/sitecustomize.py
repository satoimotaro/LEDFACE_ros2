import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/satoimo/LEDFACE_ws/esp32_firmware_ws/firmware/dev_ws/install/ament_pyflakes'
