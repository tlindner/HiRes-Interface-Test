/*
	Hi-res joystick interface testing program.

	This program displays raw counter values calculated by waiting for
	the RC circuit to discharge inside the device.

	It does this at normal and double clock speed.

	It also keeps track of each minimum and maximum and other statictics.
*/

#include <cmoc.h>
#include <coco.h>

#include "hiresjoyIntrf.h"

#define ADDR0 (byte *)0xe00 + 32 + ((48*0) * 8)
#define ADDR1 (byte *)0xe00 + 32 + ((48*3) * 8)
#define ADDR2 (byte *)0xe00 + 32 + ((48*6) * 8)
#define ADDR3 (byte *)0xe00 + 32 + ((48*9) * 8)
#define ADDR4 (byte *)0xe00 + 32 + ((48*12) * 8)

unsigned short min( unsigned short a, unsigned short b)
{
	if(a<b)
		return a;
	else
		return b;
}

unsigned short max( unsigned short a, unsigned short b)
{
	if(a>b)
		return a;
	else
		return b;
}

void setBit(unsigned short x, byte *base)
{
	base[x] = 0xff;
}

extern byte _CMOC_pmodeNo;
extern byte *_CMOC_pmodeScreenBuffer;

unsigned countBitsInBuffer( byte *start, byte *end )
{
	unsigned i = 0;
	byte *j;

	for( j=start; j<end; j++ )
	{
		i += *j ? 1 : 0;
	}

	return i;
}

int main()
{
	BOOL showText = TRUE;
	BOOL version = TRUE;

	unsigned short x;
	unsigned short hi_min_x, hi_max_x;
	unsigned short lo_min_x, lo_max_x;

	unsigned short y;
	unsigned short hi_min_y, hi_max_y;
	unsigned short lo_min_y, lo_max_y;

	lo_min_x = 0xffff;
	lo_max_x = 0;

	lo_min_y = 0xffff;
	lo_max_y = 0;

	hi_min_x = 0xffff;
	hi_max_x = 0;

	hi_min_y = 0xffff;
	hi_max_y = 0;

	initCoCoSupport();
	setMasterSoundSwitch(FALSE);
	cls(1);

	if(version)
		printf( "HI RES JOYSTICK TESTING PROGRAM\n" );
	else
		printf( "CM3 JOYSTICK TESTING PROGRAM   \n" );

	printf( "USE RIGHT JOYSTICK PORT\n");
	printf( "\n");
	printf( "    MIN     CURRENT      MAX\n" );
	printf( "SX\n" );
	printf( "SY\n" );
	printf( "FX\n" );
	printf( "FY\n" );
	printf( "\n");
	printf( "    MEAN    PERCENT\n" );
	printf( "SX\n" );
	printf( "SY\n" );
	printf( "FX\n" );
	printf( "FY\n" );

	pmode(4, 0xe00);
	pcls(0);

	while(1)
	{
		setHighSpeed(FALSE);

		if(version)
		{
			x = HiResJoyIn(HRJ_Right_Horizontal_Port);
			y = HiResJoyIn(HRJ_Right_Vertical_Port);
		}
		else
		{
			PIA0_CM3_Mode();
			x = HiResJoyIn_CM3(HRJ_Right_Horizontal_Port);
			y = HiResJoyIn_CM3(HRJ_Right_Vertical_Port);
			PIA0_Normal_Mode();
		}

		setHighSpeed(TRUE);

		if(x>20 && x<1000)
		{
			setBit(x, ADDR0);
			lo_min_x = min(x, lo_min_x);
			lo_max_x = max(x, lo_max_x);
		}

		if(y>20 && y<1000)
		{
			setBit(y, ADDR1);
			lo_min_y = min(y, lo_min_y);
			lo_max_y = max(y, lo_max_y);
		}

		if( showText )
		{
			locate(3,4);
			printf( "%05u", lo_min_x );

			locate(13,4);
			printf( "%05u", x );

			locate(24,4);
			printf( "%05u", lo_max_x );

			locate(3,5);
			printf( "%05u", lo_min_y );

			locate(13,5);
			printf( "%05u", y );

			locate(24,5);
			printf( "%05u", lo_max_y );
		}

		if(version)
		{
			x = HiResJoyIn(HRJ_Right_Horizontal_Port);
			y = HiResJoyIn(HRJ_Right_Vertical_Port);
		}
		else
		{
			PIA0_CM3_Mode();
			x = HiResJoyIn_CM3(HRJ_Right_Horizontal_Port);
			y = HiResJoyIn_CM3(HRJ_Right_Vertical_Port);
			PIA0_Normal_Mode();
		}

		if(x>20 && x<1000)
		{
			setBit(x, ADDR2);
			hi_min_x = min(x, hi_min_x);
			hi_max_x = max(x, hi_max_x);
		}

		if(y>20 && y<1000)
		{
			setBit(y, ADDR3);
			hi_min_y = min(y, hi_min_y);
			hi_max_y = max(y, hi_max_y);
		}

		if( showText )
		{
			locate(3,6);
			printf( "%05u", hi_min_x );

			locate(13,6);
			printf( "%05u", x );

			locate(24,6);
			printf( "%05u", hi_max_x );

			locate(3,7);
			printf( "%05u", hi_min_y );

			locate(13,7);
			printf( "%05u", y );

			locate(24,7);
			printf( "%05u", hi_max_y );
		}

		if (showText && isKeyPressed(KEY_PROBE_G, KEY_BIT_G))
		{
			screen(1,0);
			showText = FALSE;

			byte mode = 4;
			byte *pia1bData = (byte *) 0xff22;
			*pia1bData = *pia1bData & 7 | ((mode + 3) << 4) | 0x80;
		}

		if (!showText && isKeyPressed(KEY_PROBE_T, KEY_BIT_T))
		{
			screen(0,0);
			showText = TRUE;
		}

		if (isKeyPressed(KEY_PROBE_C, KEY_BIT_C))
		{
			pcls(0);

			lo_min_x = 0xffff;
			lo_max_x = 0;
			lo_min_y = 0xffff;
			lo_max_y = 0;

			hi_min_x = 0xffff;
			hi_max_x = 0;
			hi_min_y = 0xffff;
			hi_max_y = 0;
		}

		if (isKeyPressed(KEY_PROBE_S, KEY_BIT_S))
		{
			screen(0,0);
			showText = TRUE;

			locate( 3,10 );
			printf( "%05u", (lo_min_x + lo_max_x) >> 1 );
			locate( 3,11 );
			printf( "%05u", (lo_min_y + lo_max_y) >> 1 );
			locate( 3,12 );
			printf( "%05u", (hi_min_x + hi_max_x) >> 1 );
			locate( 3,13 );
			printf( "%05u", (hi_min_y + hi_max_y) >> 1 );

			locate( 12, 10);
			printf( "%05d of %05d", countBitsInBuffer( ADDR0, ADDR1 ), (lo_max_x-lo_min_x));
			locate( 12, 11);
			printf( "%05d of %05d", countBitsInBuffer( ADDR1, ADDR2 ), (lo_max_y-lo_min_y));
			locate( 12, 12);
			printf( "%05d of %05d", countBitsInBuffer( ADDR2, ADDR3 ), (hi_max_x-hi_min_x));
			locate( 12, 13);
			printf( "%05d of %05d", countBitsInBuffer( ADDR3, ADDR4 ), (hi_max_y-hi_min_y));
		}

		if (isKeyPressed(KEY_PROBE_R, KEY_BIT_R))
		{
			version = TRUE;

			locate(0, 0);
			printf( "HI RES JOYSTICK TESTING PROGRAM" );

			pcls(0);

			lo_min_x = 0xffff;
			lo_max_x = 0;
			lo_min_y = 0xffff;
			lo_max_y = 0;

			hi_min_x = 0xffff;
			hi_max_x = 0;
			hi_min_y = 0xffff;
			hi_max_y = 0;
		}

		if (isKeyPressed(KEY_PROBE_M, KEY_BIT_M))
		{
			version = FALSE;

			locate(0, 0);
			printf( "CM3 JOYSTICK TESTING PROGRAM   " );

			pcls(0);

			lo_min_x = 0xffff;
			lo_max_x = 0;
			lo_min_y = 0xffff;
			lo_max_y = 0;

			hi_min_x = 0xffff;
			hi_max_x = 0;
			hi_min_y = 0xffff;
			hi_max_y = 0;
		}
	}

	return 0;
}
