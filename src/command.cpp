// 
#include "canlib.h"
#include "elmocontrol/command.h"
#include "elmocontrol/motor.h"
#include "std_msgs/String.h"
#include <sstream>
#include <sys/time.h>
#include <unistd.h>
#include <ros/ros.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
	
int motormode;

namespace elmocontrol
{

canHandle h;

unsigned command::GetTickCount()
{
        struct timeval tv;
        if(gettimeofday(&tv, NULL) != 0)
                return 0;
        return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
};

void command::MotorInit()
{
	//Elmo driver initialize
        CAN_DATA canData;
        UINT32 can_id;
        
	canData.dU32[0] = 0;

	int i=0;
	{
		can_id = 0;
		canData.dByte[0] = 0x82;				//
		canData.dByte[1] = 3;
		CanSendMessage(can_id, canData, 8);
		sleep(0.02);	// for delay

	}


	{
		//can_id =0x0300| (3);
		canData.dByte[0] = 0x01;				//Ÿêµµ ±×·³. ±×³É ÃÊ±âÈ­ ŽÜ°èÀÓ.
		canData.dByte[1] = 3;
		CanSendMessage(can_id, canData, 8);
		sleep(0.02);	// for delay


	}


	{
		can_id = 0x0300 | (3);	
		stop(canData);
		CanSendMessage(can_id, canData, 8);
                motormode=5;
		if (motormode == 5)
		{
			selectMode(5, canData); //w(false);
		}
		else if (motormode == 1)
		{
			selectMode(1, canData); //w(true);
		}

		CanSendMessage(can_id, canData, 8);

		sleep(0.01);// for delay
		SF(100, canData);
		CanSendMessage(can_id, canData, 8);
		SP(40000, canData);
		CanSendMessage(can_id, canData, 8);
		AC(50000, canData);
		CanSendMessage(can_id, canData, 8);
		DC(50000, canData);
		CanSendMessage(can_id, canData, 8);
		sleep(0.01);// for delay

	}

	{
		can_id = 0x0300 | (3);
		start(canData);
		CanSendMessage(can_id, canData, 8);
		sleep(0.01);	// for delay
	}
};

//

void command::MotorOn()
{       CAN_DATA canData;
        UINT32 can_id;
        can_id = 0x0300|(3);

	canData.dU32[0] = 0;
        int i=0;
	{
		//can_id = 0x0300 | (72 + i);
	start(canData);
	CanSendMessage(can_id, canData, 8);
	  sleep(0.01);	// for delay
	}
  //printf("%s", "Motor On");
};

//
void command::MotorOff()
{
	CAN_DATA canData;
	UINT32 can_id;

	canData.dU32[0] = 0;
	for (int i = 0; i<7; i++)
	{
		can_id = 0x0300 | (3);
		stop(canData);
		CanSendMessage(can_id, canData, 8);
		Wait();	// for delay
	}
};

//

void command::Wait()
{
	GetTickCount();
};

//
void command::CanSendMessage(UINT32 id, CAN_DATA &canData, UINT32 len)    
       
       
{       canStatus stat; 
	char msg[8] = { 0, };
        
	for (int i = 0; i<len; i++)
		msg[i] = canData.dByte[i];
        stat=canWrite(h, id, msg, len, 0);
        if (stat != canOK) {
    char buf[50];
    buf[0] = '\0';
    canGetErrorText(stat, buf, sizeof(buf));
    fprintf(stderr,"canOpenChannel failed (%s)\n", buf);
    exit(1);
  }
  
};



}
