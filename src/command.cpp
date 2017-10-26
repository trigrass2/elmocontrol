// 

#include "elmocontrol/command.h"
#include <string>
#include "elmocontrol/motor.h"
#include <sys/time.h>
#include "canlib.h"

int motormode;
CanHandle h;

namespace elmocontrol
{
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

	for (int i = 0; i<7; i++)
	{
		can_id = 0;
		canData.dByte[0] = 0x82;				//
		canData.dByte[1] = i + 72;
		CanSendMessage(can_id, canData, 8);
		Wait();	// for delay

	}

	for (int i = 0; i<7; i++)
	{
		can_id = 0;
		canData.dByte[0] = 0x01;				//Ÿêµµ ±×·³. ±×³É ÃÊ±âÈ­ ŽÜ°èÀÓ.
		canData.dByte[1] = i + 72;
		CanSendMessage(can_id, canData, 8);
		Wait();	// for delay

	}

	for (UINT i = 0; i<7; i++)
	{
		can_id = 0x0300 | (72 +i);	//Ÿê³×µéµµ ŽÙ ž¶Âù°¡Áö. žðÅÍµå¶óÀÌ¹ö¿¡ Á€ÇØÁ®ÀÖŽÂ ÇÔŒö.
		stop(canData);
		CanSendMessage(can_id, canData, 8);
		if (motormode == 5)
		{
			selectMode(5, canData); //Æ÷ÁöŒÇ ÁŠŸî žðµå
			//GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
		}
		else if (motormode == 1)
		{
			selectMode(1, canData); //Àü·ùÁŠŸîžðµå
			//GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
		}

		CanSendMessage(can_id, canData, 8);

		Wait();	// for delay
		SF(100, canData);
		CanSendMessage(can_id, canData, 8);
		SP(40000, canData);
		CanSendMessage(can_id, canData, 8);
		AC(50000, canData);
		CanSendMessage(can_id, canData, 8);
		DC(50000, canData);
		CanSendMessage(can_id, canData, 8);

		Wait();	// for delay
	}

	for (int i = 0; i<7; i++)
	{
		can_id = 0x0300 | (72 + i);
		start(canData);
		CanSendMessage(can_id, canData, 8);
		Wait();	// for delay
	}
};

//

void command::MotorOn()
{
	CAN_DATA canData;
	UINT32 can_id;

	canData.dU32[0] = 0;
	for (int i = 0; i<7; i++)
	{
		can_id = 0x0300 | (72 + i);
		start(canData);
		CanSendMessage(can_id, canData, 8);
		Wait();	// for delay
	}
};

//
void command::MotorOff()
{
	CAN_DATA canData;
	UINT32 can_id;

	canData.dU32[0] = 0;
	for (int i = 0; i<7; i++)
	{
		can_id = 0x0300 | (72 + i);
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
{
	char msg[8] = { 0, };

	for (int i = 0; i<len; i++)
		msg[i] = canData.dByte[i];

	canWrite(h, id, msg, len, 0);
};

}
