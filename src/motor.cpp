
#include "elmocontrol/motor.h"


void start(CAN_DATA &out)
{
	//printf("motor[%d]: start...\n", _id);
	//rt_task_sleep(50000000);
	unsigned char msg[] = { 0x4d, 0x4f, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void stop(CAN_DATA &out)
{
	//printf("motor[%d]: stop...\n", _id);
	//rt_task_sleep(50000000);
	unsigned char msg[] = { 0x4d, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void selectMode(int mode, CAN_DATA &out)
{

	//stop();
	//rt_task_sleep(50000000);
	unsigned char msg[] = { 0x55, 0x4d, 0x00, 0x00, mode, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	//rt_task_sleep(50000000);
	//start();
	//printf("mode[%d] is selected...\n", _mode);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void TC(float torque, CAN_DATA &out)
{
	unsigned int temp;
	//memcpy(&temp, &torque, sizeof(int));
	unsigned char p[4] = { 0, };

	
	p[0] = temp & 0xFF;
	p[1] = (temp >> 8) & 0xFF;
	p[2] = (temp >> 16) & 0xFF;
	p[3] = (temp >> 24) & 0xFF;

	unsigned char msg[] = { 'T', 'C', 0x00, 0x80, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void PA(int pos, CAN_DATA &out)
{
	unsigned char p[4] = { 0, };
	p[0] = pos & 0xFF;
	p[1] = (pos >> 8) & 0xFF;
	p[2] = (pos >> 16) & 0xFF;
	p[3] = (pos >> 24) & 0xFF;
	unsigned char msg[] = { 'P', 'A', 0x00, 0x00, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void SF(int pos, CAN_DATA &out)
{
	unsigned char p[4] = { 0, };
	p[0] = pos & 0xFF;
	p[1] = (pos >> 8) & 0xFF;
	p[2] = (pos >> 16) & 0xFF;
	p[3] = (pos >> 24) & 0xFF;
	unsigned char msg[] = { 'S', 'F', 0x00, 0x00, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void SP(int pos, CAN_DATA &out)
{
	unsigned char p[4] = { 0, };
	p[0] = pos & 0xFF;
	p[1] = (pos >> 8) & 0xFF;
	p[2] = (pos >> 16) & 0xFF;
	p[3] = (pos >> 24) & 0xFF;
	unsigned char msg[] = { 'S', 'P', 0x00, 0x00, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void AC(int pos, CAN_DATA &out)
{
	unsigned char p[4] = { 0, };
	p[0] = pos & 0xFF;
	p[1] = (pos >> 8) & 0xFF;
	p[2] = (pos >> 16) & 0xFF;
	p[3] = (pos >> 24) & 0xFF;
	unsigned char msg[] = { 'A', 'C', 0x00, 0x00, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}
void DC(int pos, CAN_DATA &out)
{
	unsigned char p[4] = { 0, };
	p[0] = pos & 0xFF;
	p[1] = (pos >> 8) & 0xFF;
	p[2] = (pos >> 16) & 0xFF;
	p[3] = (pos >> 24) & 0xFF;
	unsigned char msg[] = { 'D', 'C', 0x00, 0x00, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}
void JV(int vel, CAN_DATA &out)
{
	unsigned char p[4] = { 0, };
	p[0] = vel & 0xFF;
	p[1] = (vel >> 8) & 0xFF;
	p[2] = (vel >> 16) & 0xFF;
	p[3] = (vel >> 24) & 0xFF;
	unsigned char msg[] = { 'J', 'V', 0x00, 0x00, p[0], p[1], p[2], p[3] };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void begin(CAN_DATA &out)
{
	//float a = 0.8;
	unsigned char msg[] = { 'B', 'G', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void PX(CAN_DATA &out)
{
	unsigned char msg[] = { 'P', 'X', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void ST(CAN_DATA &out)
{
	//float a = 0.8;
	unsigned char msg[] = { 'S', 'T', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}

void VX(CAN_DATA &out)
{
	unsigned char msg[] = { 'V', 'X', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//_canPort[0]->SendToReq(msg);
	for (int i = 0; i<8; i++)
		out.dByte[i] = msg[i];
}
