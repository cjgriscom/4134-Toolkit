#ifndef __AUTONOMOUSDRIVER__
#define __AUTONOMOUSDRIVER__

#include "sharedutils.h"
#include "../sensors/drivers/hitechnic-sensormux.h"
#include "../sensors/drivers/hitechnic-gyro.h"
#include "../sensors/drivers/hitechnic-irseeker-v2.h"
#include "JoystickDriver.c"

bool programStarted() {
	getJoystickSettings(joystick);
    return !joystick.StopPgm;
}

float dt = 0;
float dx = 0;
float angle = 0;
bool reset=false;
float gyroAngle() {
	if (reset) {
		angle=0;dx=0;reset=false;
		return 0;
	}
	time1[T1] = 0;
	dx = HTGYROreadRot(gyro);
	if (abs(dx) > 2) {
		angle += dx * dt;
		//if (angle > 360) angle -= 360;
		//else if (angle < 0) angle += 360;
	}
	wait1Msec(5);
	dt = ((float)time1[T1]) / 1000;
	return angle;
}
void resetGyro() {
	reset=true;
}

#define LEFT_DECISION true		// Readability constants :P
#define RIGHT_DECISION false
#define DUMP_DECISION true
#define WAIT_DECISION false

bool decideLR(int stage, bool prev, int menuSelection, tMUXSensor infared) {
	int region = HTIRS2readACDir(infared);
	int dummy = 0;
	int lregion = 0;
	int rregion = 0;

	HTIRS2readAllACStrength(infared, dummy, rregion, dummy, lregion, dummy);

	nxtDisplayCenteredTextLine(-1+stage, "%i", region);
	nxtDisplayCenteredTextLine(2, "%i", lregion);
	nxtDisplayCenteredTextLine(3, "%i", rregion);

	if (stage==1) {
		if (region==5) region = (rregion>lregion ? 6 : 4);
		switch (menuSelection) {
			case 0: return (region>=5 ? LEFT_DECISION : RIGHT_DECISION);
			case 1: return LEFT_DECISION;		//Left bucket (1)
			case 2: return LEFT_DECISION;		//Left bucket (2)
			case 3: return RIGHT_DECISION;		//Right bucket(3)
			case 4: return RIGHT_DECISION;		//Right bucket(4)
			case 5: return LEFT_DECISION;		//Left only   (1or2)
			case 6: return RIGHT_DECISION;		//Right only  (3or4)
		}
	} else if (stage==2) {
		switch (menuSelection) {
			case 1: return WAIT_DECISION;		//Outer bucket (1)
			case 2: return DUMP_DECISION;		//Inner bucket (2)
			case 3: return DUMP_DECISION;		//Inner bucket (3)
			case 4: return WAIT_DECISION;		//Outer bucket (4)
		}
		if (prev == LEFT_DECISION) {
			return (region>=6 ? WAIT_DECISION : DUMP_DECISION);  // Left IR
		} else {
			return (region<=4 ? WAIT_DECISION : DUMP_DECISION);  // Right IR
		}
	}
	return false; //invalid request
}

void resetDrive() {
	nMotorEncoder[FLDrive]=0; nMotorEncoder[FRDrive]=0;
	motor[FLDrive]=0; motor[FRDrive]=0; motor[BLDrive]=0; motor[BRDrive]=0;
	return;
}

int currentGyroPos = -1;
void setGyroPos(bool vert) { // Vertical:1, Horiz:0
	int intPos = (vert?1:0);
	if (currentGyroPos!=intPos) {
		currentGyroPos=intPos;
		servo[GyroServo]=(vert ? GYRO_SERVO_VERT : GYRO_SERVO_HORIZ); // Set servo
		wait1Msec(600); // Wait for position
		gyroAngle();    // Take a dummy reading to clear variables
		resetGyro();    // Set gyro to 0
		wait1Msec(100);
		resetGyro();
	}
}



#endif
