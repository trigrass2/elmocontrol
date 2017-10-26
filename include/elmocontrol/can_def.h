
#pragma once
// CAN msg 
// 2012.11.04
// by Donmin

typedef unsigned int UINT;
typedef unsigned char UINT8;
typedef unsigned int UINT32;

typedef union _CAN_DATA
{
	UINT8			dByte[8];
	int				dInt[2];
	float			dFloat[2];
	UINT32			dU32[2];
	signed short	dInt16[4];
	unsigned short  dU16[4];
}CAN_DATA;
