#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S4,     ForceSensor,    sensorAnalogActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "sensors/drivers/hitechnic-force.h"

// Takes into account in-between positions
#define POVUpPressed(a) ((a)==7 || (a)==0 || (a)==1)
#define POVDownPressed(a) ((a)==3 || (a)==4 || (a)==5)
#define POVLeftPressed(a) ((a)==5 || (a)==6 || (a)==7)
#define POVRightPressed(a) ((a)==1 || (a)==2 || (a)==3)

// Use these like joystick x or y variables.
#define POVAsJoystickX(a) (POVLeftPressed(a) ? -128 : (POVRightPressed(a) ? 127 : 0))
#define POVAsJoystickY(a) (POVDownPressed(a) ? -128 : (POVUpPressed(a) ? 127 : 0))

// Example: BUTTON_ID(2, 5) returns the ID for remote 2 button 5.
#define BUTTON_ID(remote1or2, buttonNumber) ((remote1or2) <= (1) ? (buttonNumber) : (buttonNumber+16))

#define POV_1_UP 		1+12
#define POV_1_RIGHT 	2+12
#define POV_1_DOWN 		3+12
#define POV_1_LEFT	 	4+12
#define POV_2_UP 		1+28
#define POV_2_RIGHT 	2+28
#define POV_2_DOWN		3+28
#define POV_2_LEFT	 	4+28

#define NXT_CENTER 		3+32
#define NXT_LEFT   		2+32
#define NXT_RIGHT  		1+32
#define NXT_BACK   		0+32

bool buttonPressed(short buttonID) {
	if      (buttonID <= 12) {return joy1Btn(buttonID) > 0;}				//Check R1 button state (possibly incorrect method)
	else if (buttonID == POV_1_UP) {return POVUpPressed(joystick.joy1_TopHat);}		//Individual POV cases
	else if (buttonID == POV_1_DOWN) {return POVDownPressed(joystick.joy1_TopHat);}
	else if (buttonID == POV_1_LEFT) {return POVLeftPressed(joystick.joy1_TopHat);}
	else if (buttonID == POV_1_RIGHT) {return POVRightPressed(joystick.joy1_TopHat);}
	else if (buttonID <= 28) {return joy2Btn(buttonID-16) > 0;}				//R2 Buttons
	else if (buttonID == POV_2_UP) {return false;}//POVUpPressed(joystick.joy2_TopHat);} //Set by default bug?
	else if (buttonID == POV_2_DOWN) {return POVDownPressed(joystick.joy2_TopHat);}
	else if (buttonID == POV_2_LEFT) {return POVLeftPressed(joystick.joy2_TopHat);}
	else if (buttonID == POV_2_RIGHT) {return POVRightPressed(joystick.joy2_TopHat);}
	else if (buttonID <= NXT_BACK)   {return nNxtButtonPressed == buttonID-32;}	//Check NXT button equality
	else {return false;}
	//1-36 Cases
}

void initializeRobot()
{
	nNxtExitClicks = 3;
	return;
}

float getAngle(int x, int y) {
	return atan2(x,y);
}
int getMagnitude(int x, int y) {
	return sqrt(x*x + y*y);
}

float angle = 0;
int magnitude = 0;
float w1angle = 0;
float w2angle = 2*PI/3;
float w3angle = 4*PI/3;

int mA, mB, mC;

task main() {


	initializeRobot();

	//waitForStart();   // wait for start of tele-op phase

	while (true) {
		if (!buttonPressed(BUTTON_ID(1,1)))	{

			int joy_x = joystick.joy1_x1/128.0*100;
			int joy_y = joystick.joy1_y1/128.0*-100;

			angle = getAngle(joy_x,joy_y);
			magnitude = getMagnitude(joy_x,joy_y);

			mA = magnitude*sin(angle + w1angle);
			mB = magnitude*sin(angle + w2angle);
			mC = magnitude*sin(angle + w3angle);
		} else {
			mA = 100;
			mB = mA;
			mC = mA;
		}
		motor[motorA] = mA;
		motor[motorB] = mB;
		motor[motorC] = mC;
		wait1Msec(5);
	}
}