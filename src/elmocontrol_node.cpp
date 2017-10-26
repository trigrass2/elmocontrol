// Copyright 

#include "elmocontrol/command.h"
#include "elmocontrol/exception.h"
#include "elmocontrol/motor.h"
#include "ros/ros.h"

elmocontrol::command *control;
CAN_DATA canData;

int main(int argc, char**argv)
{
  ros::init(argc, argv, "elmocontrol");
  ros::NodeHandle n;
  //cv_camera::Driver driver(private_node, private_node);

  try
  {
    control->MotorInit();
    while (ros::ok())
    {
      control->MotorOn();
      PA(1137.8, canData);
      ros::spinOnce();
    }
  }
  catch (elmocontrol::DeviceError &e)
  {
    ROS_ERROR_STREAM("Elmo connection failed: " << e.what());
    return 1;
  }

  return 0;
}
