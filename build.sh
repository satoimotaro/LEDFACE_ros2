source /opt/ros/humble/setup.bash
cd ~/ros2_LEDFACE_ws/
colcon build --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --symlink-install
source install/setup.bash
