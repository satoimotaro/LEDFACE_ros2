cmake_minimum_required(VERSION 3.8)
project(image_dot_filter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(image_transport REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
  include  
  ${OpenCV_INCLUDE_DIRS}
)

add_library(dot_filter src/dot_filter.cpp)

target_include_directories(dot_filter PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

add_executable(image_dot_filter src/image_dot_filter.cpp)
ament_target_dependencies(dot_filter rclcpp sensor_msgs cv_bridge image_transport)
ament_target_dependencies(image_dot_filter rclcpp sensor_msgs cv_bridge image_transport)
target_link_libraries(image_dot_filter dot_filter ${OpenCV_LIBRARIES})

install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}/
)
install(TARGETS
  dot_filter
  image_dot_filter
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
