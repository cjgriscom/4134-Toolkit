//#include "sensors/drivers/hitechnic-sensormux.h"
#include "sensors/drivers/lego-ultrasound.h"
#include "sensors/drivers/lego-light.h"

#define n_readings 8
#define CLEAR_RANGE 1200 //was 640

//Obstr ~= <48cm
//Light black <40   ~=30
//Light white >40   ~=50
bool findClearRamp(tMUXSensor sonar, int maxDist) {
	armState=0;
	HTSMUXsetAnalogueActive(lightSensor);

	//int maxDist = 3000; // Must be defined as the max distance past start position

	int avgSonar[n_readings];

	int rampPos = 0; //0-2
	time1[T3]=0; //Time since light trigger

	int power = -60;
	motor[FLDrive] = power; motor[FRDrive] = power;
	motor[BLDrive] = power; motor[BRDrive] = power;

	while (true) {
		wait1Msec(5);

		int lightValue = LSvalNorm(lightSensor);
		bool whiteLine = time1[T3]>1000 && lightValue>31;  //make sure 1 sec has passed since last detection
		int driveDist = abs(nMotorEncoder[FLDrive]);

		int divPosition = (driveDist/(CLEAR_RANGE/n_readings) ) % n_readings; // current region based on distance

		bool tooFar = driveDist>maxDist || rampPos==2;

		int sonarValue = USreadDist(sonar);

		if (sonarValue<55) sonarValue=0;
		if (sonarValue>=55) sonarValue=100;  // Keep sonar readings black and white

		avgSonar[divPosition] = sonarValue; // Assign final value to current segmented average position

		int percentClear = 0;
		for (int i=0; i<n_readings;i++) {
			percentClear += avgSonar[i];
		}
		percentClear /= n_readings; // Calculate current average

		if ((rampPos>0 && percentClear>90) || tooFar) {Sleep(160);resetDrive();return !tooFar;}  // If view clear or at max position, stop
		if (whiteLine) {
			rampPos++;
			time1[T3]=0;
		}  // increment position

		if (DEBUG) nxtDisplayCenteredTextLine(2,"%i", divPosition);
		if (DEBUG) nxtDisplayCenteredTextLine(3,"%i", rampPos);
		if (DEBUG) nxtDisplayCenteredTextLine(4,"%i", percentClear);
		if (DEBUG) nxtDisplayCenteredTextLine(5,"%i", lightValue);
		if (DEBUG) nxtDisplayCenteredTextLine(6,"%i", driveDist);
	}
}

bool findLine(int maxDist, int nLine) {
	armState=0; // deactivate arm
	HTSMUXsetAnalogueActive(lightSensor);

	//int maxDist = 3000; // Must be defined as the max distance past start position

	int rampPos = 0; //0-2
	time1[T3]=0; //Time since light trigger

	int power = -60;
	motor[FLDrive] = power; motor[FRDrive] = power;
	motor[BLDrive] = power; motor[BRDrive] = power;

	while (true) {
		wait1Msec(5);

		int lightValue = LSvalNorm(lightSensor);
		bool whiteLine = time1[T3]>1000 && lightValue>31;  //make sure 1 sec has passed since last detection
		int driveDist = abs(nMotorEncoder[FLDrive]);

		bool tooFar = driveDist>maxDist;

		if ((rampPos>=nLine) || tooFar) {Sleep(160);resetDrive();return !tooFar;}  // If view clear or at max position, stop
		if (whiteLine) {
			rampPos++;
			time1[T3]=0;
		}  // increment position

		if (DEBUG) nxtDisplayCenteredTextLine(0,"%i", rampPos);
		if (DEBUG) nxtDisplayCenteredTextLine(1,"%i", lightValue);
		if (DEBUG) nxtDisplayCenteredTextLine(2,"%i", driveDist);
	}
}
