#ifndef __SHAREDUTILS__
#define __SHAREDUTILS__

#include "constants.h"

#define BTN_CENTER 3
#define BTN_LEFT   2
#define BTN_RIGHT  1
#define BTN_BACK   0

int powscl(int xy, int max) {
	return xy/128.0*max;
}

int powscl(int xy) {
	return powscl(xy,100);
}

int threshold(int x, int min) {
	return (abs(x) > min) ? x : 0;
}
float threshold(float x, float min) {
	return (abs(x) > min) ? x : 0;
}

int remoteToMotor(int xy, int maxPower) {
	return powscl(threshold(xy, 15), maxPower);
}
int remoteToMotor(int xy) {
	return powscl(threshold(xy, 15));
}

int coerce(int x, int min, int max) {
	if (x > max) {
		x = max;
	}
	else if (x < min) {
		x = min;
	}
	return x;
}

bool inRange(int x, int min, int max) {
	return ( (x < max) && (x > min) );
}

float max(float a, float b) {return (a>b ? a : b);}
float min(float a, float b) {return (a<b ? a : b);}


int getTargetingPower(int target, int currentPosition, float errorConstant, int maxPower) {
	// Position Targeter
	int error = target - currentPosition;
	return coerce((int)(errorConstant*error), -1*maxPower, maxPower);
}

void setClamp(bool clamped) {
	servo[LeftClamp] = (clamped ? CLAMP_LEFT_HOLD : CLAMP_LEFT_RELEASE);
	servo[RightClamp] = (clamped ? CLAMP_RIGHT_HOLD : CLAMP_RIGHT_RELEASE);
}

#endif
