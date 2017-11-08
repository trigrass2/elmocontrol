/*
* motor.h
*
*  Created on: 2011. 12. 6.
*      Author: k13201
*/

#ifndef ELMOCONTROL_MOTOR_H_
#define ELMOCONTROL_MOTOR_H_


//#include "stdafx.h"
#include "elmocontrol/can_def.h"
#include "canlib.h"
#include <canopen_master/canopen.h>


void start(CAN_DATA &out);
void stop(CAN_DATA &out);

void selectMode(int mode, CAN_DATA &out);

void TC(float torque, CAN_DATA &out);

void PA(int pos, CAN_DATA &out); // absolute position
void SF(int pos, CAN_DATA &out); // smooth factor
void SP(int pos, CAN_DATA &out); // speed for ptp mode
void AC(int pos, CAN_DATA &out); // acceleration
void DC(int pos, CAN_DATA &out); // deceleration
void JV(int vel, CAN_DATA &out); // jogging velocity
void begin(CAN_DATA &out);       // 
void PX(CAN_DATA &out);          // main position
void ST(CAN_DATA &out);          // stop motion
void VX(CAN_DATA &out);          // Velocity of main feedback

#endif /* MOTOR_H_ */

