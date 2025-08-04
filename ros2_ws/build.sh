source /opt/ros/humble/setup.bash
cd ~/LEDFACE_ws/ros2_ws
colcon build --cmake-args -DCMAKE_EXPORT_COMPILE_COMMANDS=ON --symlink-install
source install/setup.bash
