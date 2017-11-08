// Copyright 

#include "elmocontrol/command.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "elmocontrol/exception.h"
#include <sstream>
#include "canlib.h"
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

elmocontrol::command *control;
UINT32 can_id;
canHandle h;

#define ALARM_INTERVAL_IN_S   (2)
#define READ_WAIT_INFINITE    (unsigned long)(-1)

static unsigned int msgCounter = 0;
static unsigned int std1 = 0, ext = 0, rtr = 0, err = 0, over = 0;

static void check(char* id, canStatus stat)
{
  if (stat != canOK) {
    char buf[50];
    buf[0] = '\0';
    canGetErrorText(stat, buf, sizeof(buf));
    fprintf(stderr,"canOpenChannel failed (%s)\n", buf);
  }
}

static void sighand(int sig)
{
  static unsigned int last;

  switch (sig) {
  case SIGINT:
    break;
  case SIGALRM:
    if (msgCounter - last) {
      printf("msg/s = %d, total=%d, std1=%u, ext=%u, err=%u, over=%u\n",
             (msgCounter - last) / ALARM_INTERVAL_IN_S, msgCounter, std1, ext, err, over);
    }
    last = msgCounter;
    alarm(ALARM_INTERVAL_IN_S);
    break;
  }
}

static void printUsageAndExit(char *prgName)
{
  printf("Usage: '%s <channel>'\n", prgName);
  exit(1);
}


using namespace elmocontrol;

int main(int argc, char**argv)
{ 
  ros::init(argc, argv, "elmocontrol");
  ros::NodeHandle private_node("~");
  
  CAN_DATA canData;
  std_msgs::String msg;
  std::stringstream ss;	
  
  
  canStatus stat;
  int channel=0;


  canInitializeLibrary();
  h=canOpenChannel(channel, canWANT_EXCLUSIVE);
  if (h < 0) {
    printf("canOpenChannel %d", channel);
    char buf[50];
    buf[0] = '\0';
    canGetErrorText(stat, buf, sizeof(buf));
    fprintf(stderr,"canOpenChannel failed (%s)\n", buf);
    exit(1);
    return -1;
  }
  
  stat = canSetBusParams(h, canBITRATE_1M, 0, 0, 0, 0, 0);
  check("canSetBusParams", stat);

  if (stat != canOK) {
	  alarm(ALARM_INTERVAL_IN_S);
	  stat = canBusOff(h);
	  check("canBusOff", stat);
	  stat = canClose(h);
	  check("canClose", stat);
  }
  
canSetBusOutputControl(h,canDRIVER_NORMAL);
stat = canBusOn(h);
  check("canBusOn", stat);
  if (stat != canOK) {
	  alarm(ALARM_INTERVAL_IN_S);
	  stat = canBusOff(h);
	  check("canBusOff", stat);
	  stat = canClose(h);
	  check("canClose", stat);
  }

  alarm(ALARM_INTERVAL_IN_S);
 
try
 {

   can_id=(0x0300)|0;
   control->MotorInit();
   control->MotorOn();
   
   PA(20,canData);
   control->CanSendMessage(can_id,canData,8);  

   begin(canData);
   control->CanSendMessage(can_id,canData,4);

   PA(0,canData);
   control->CanSendMessage(can_id,canData,8);  

   begin(canData);
   control->CanSendMessage(can_id,canData,4);

 while (ros::ok())
   { 
   
    long id;
    UINT8 msg[8];
    unsigned int dlc;
    unsigned int flag;
    unsigned long time;

    stat = canReadWait(h, &id, &msg, &dlc, &flag, &time, READ_WAIT_INFINITE);

    if (stat == canOK) {
      if (flag & canMSG_ERROR_FRAME) {
        err++;
      } else {
        if (flag & canMSG_STD)        std1++;
        if (flag & canMSG_EXT)        ext++;
        if (flag & canMSG_RTR)        rtr++;
        if (flag & canMSGERR_OVERRUN) over++;
      }
      msgCounter++;
    }
    else {
      if (errno == 0) {
        check("\ncanReadWait", stat);
      }
      else {
        perror("\ncanReadWait error");
      }
    }
   
   sighand(SIGALRM);
   //can_id=id;

   printf("id = %ld",id);
   //can_id=(0x0300)|3;
   //control->MotorInit();
   //control->MotorOn();

   start(canData);
   control->CanSendMessage(can_id, canData, 8);

   JV(30,canData);
   control->CanSendMessage(can_id,canData,8);  

   begin(canData);
   control->CanSendMessage(can_id,canData,4);
   

   ros::spinOnce();
   ros::Rate loop_rate(1);
   loop_rate.sleep();

    }
  }
  catch (elmocontrol::DeviceError &e)
  {
    ROS_ERROR_STREAM("Elmo connection failed: " << e.what());
    return 1;
  }

  return 0;
}
