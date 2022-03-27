#define HRJ_Left_Horizontal_Port  0x0001
#define HRJ_Left_Vertical_Port    0x0101
#define HRJ_Right_Horizontal_Port 0x0000
#define HRJ_Right_Vertical_Port   0x0100

/*
	The following routine will sample the joystick port / axis when used with the Tandy
	Hi resolution joystick interface

	Input:

	port: Joystick port / axis to sample.

	Output:

	Unsigned 16 bit counter of time it took the operational amplifier to cross the DAC
	threshold.

*/

unsigned short HiResJoyIn( unsigned short port );
void setMasterSoundSwitch(BOOL silent);
