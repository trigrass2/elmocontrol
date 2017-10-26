cmake_minimum_required(VERSION 2.8.3)
project(elmocontrol)

find_package(catkin REQUIRED COMPONENTS roscpp canopen_402 canopen_master)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system thread)

#roslint_cpp()

set(EXTRAINC_DIRS /home/anhtuan/linuxcan/include)
set(EXTRALIB_DIRS /home/anhtuan/linuxcan/canlib/libcanlib.so)

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
 ${Boost_INCLUDE_DIRS}
 ${EXTRAINC_DIRS}
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES elmocontrol
  CATKIN_DEPENDS roscpp canopen_402 canopen_master
  ##DEPENDS system_lib
)	

## Declare a C++ library
add_library(elmocontrol src/elmocontrol_node.cpp src/command.cpp src/motor.cpp)
add_executable(elmocontrol_node src/elmocontrol_node.cpp src/command.cpp src/motor.cpp)
add_dependencies(elmocontrol_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(elmocontrol ${catkin_LIBRARIES} ${EXTRALIB_DIRS})

target_link_libraries(elmocontrol_node
   ${catkin_LIBRARIES}
   ${PROJECT_NAME}
   ${EXTRALIB_DIRS}
 )
## Specify libraries to link a library or executable target against

##


#

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
 install(TARGETS elmocontrol elmocontrol_node
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

## Mark cpp header files for installation
 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
 )

## Mark other files for installation (e.g. launch and bag files, etc.)
 install(FILES
   elmocontrol.xml
#   # myfile2
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
 )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_elmocontrol.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
