cmake_minimum_required(VERSION 3.8)
project(group6_rwa4)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


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

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)  

# add path to the include directory
include_directories(include/group6_rwa4)

#other code
add_executable(bot_sequence src/main.cpp src/bot_sequence.cpp)
ament_target_dependencies(bot_sequence rclcpp geometry_msgs nav_msgs tf2 tf2_ros)


install(TARGETS bot_sequence DESTINATION lib/${PROJECT_NAME})   #This means inside directory named group6_rwa4, 
                                                                # executable file named bot_sequence will be generated.

ament_package()
