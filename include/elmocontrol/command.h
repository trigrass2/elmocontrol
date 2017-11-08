// 

#ifndef ELMOCONTROL_COMMAND_H_
#define ELMOCONTROL_COMMAND_H_

#include "elmocontrol/motor.h"
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
         //command::canData1 *canclassmem;
         //ros::NodeHandle private_node_;
 	 //boost::shared_ptr<ros::Rate> rate_;
};
}
#endif  
