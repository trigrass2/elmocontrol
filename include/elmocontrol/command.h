// 

#ifndef ELMOCONTROL_COMMAND_H_
#define ELMOCONTROL_COMMAND_H_

//#include "ros/ros.h"
#include "elmocontrol/can_def.h"
#include "canlib.h"

namespace elmocontrol
{
class command
{
 public: 
        unsigned GetTickCount();
  	void MotorInit();
	void MotorOn();
	void MotorOff();
	void Wait();
	void CanSendMessage(UINT32 id, CAN_DATA &canData, UINT32 len);
 //private:
         //ros::NodeHandle private_node_;
 	 //boost::shared_ptr<ros::Rate> rate_;
};
}
#endif  
