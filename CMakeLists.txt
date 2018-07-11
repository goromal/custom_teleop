cmake_minimum_required(VERSION 2.8.3)
project(custom_teleop)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

find_package(catkin_simple REQUIRED)

catkin_simple()

###############################
### keyboard_teleop library ###
###############################

cs_add_library(keyboard_teleop
  src/lib/keyboard_teleop.cpp
)

##############################
#### example teleop nodes ####
##############################

# cs_add_executable(arrow_teleop_twist
#   src/arrow_teleop_twist.cpp
# )
# target_link_libraries(arrow_teleop ${catkin_LIBRARIES})

###############################
########## endmatter ##########
###############################

cs_install()

cs_export()
