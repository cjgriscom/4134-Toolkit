// * MENU DEFINITIONS * //

#define N_MENUS 6

#define STARTPOS_MENU 0
#define BUCKET_MENU 1
#define DELAY_MENU 2
#define GYRO_MENU 3
#define RAMP_MENU 4
#define SONAR_MENU 5

short menuSizes[N_MENUS] = {3,7,31,2,4,4};
short wrapSelection(short menu, short sel) {
	if (sel < 0) return menuSizes[menu]-1;
	return (sel%menuSizes[menu]);
}

short selection[N_MENUS];
void updateMenus(short currentMenu, short currentSelection) {
	string textLine="";
	for (int menu=0; menu < sizeof(menuSizes)/2; menu++) {
		if (menu==STARTPOS_MENU) {
			switch (selection[menu]) { // 3 Options, Starting Position
				case 0: textLine = "Flag Corner"; break;
				case 1: textLine = "Left of Ramp"; break;
				case 2: textLine = "Right of Ramp"; break;
			}
		} else if (menu==BUCKET_MENU) {
			switch (selection[menu]) { // 7 Options; seeker override
				case 0: textLine = "Seek All"; break;
				case 1: textLine = "Bucket 1"; break;
				case 2: textLine = "Bucket 2"; break;
				case 3: textLine = "Bucket 3"; break;
				case 4: textLine = "Bucket 4"; break;
				case 5: textLine = "Seek Left"; break;
				case 6: textLine = "Seek Right"; break;
			}
		} else if (menu==DELAY_MENU) {
			textLine = "";
			sprintf(textLine, "%i", selection[menu]);
			strcat(textLine, " sec delay");
		} else if (menu==GYRO_MENU) {
			switch (selection[menu]) { // 2 Options; gyro disable
				case 0: textLine = "Gyro Disabled"; break;
				case 1: textLine = "Gyro Enabled"; break;
			}
		} else if (menu==RAMP_MENU) {
			switch (selection[menu]) { // 4 Options; ramp stop location
				case 0: textLine = "Ramp w/ leveler"; break;
				case 1: textLine = "~Top (no gyro)"; break;
				case 2: textLine = "~Close Side"; break;
				case 3: textLine = "~Far Side"; break;
			}
		} else if (menu==SONAR_MENU) {
			switch (selection[menu]) { // 3 Options; ramp stop location
				case 0: textLine = "FindFreeLocation"; break;
				case 1: textLine = "Our Side (blind)"; break;
				case 2: textLine = "Their Side (blin"; break;
				case 3: textLine = "Fallback-deadMUX"; break;
			}
		} else {textLine = "!CHECK SIZES!";}

		if (currentMenu==menu) {
			string csel="*";
			strcat(csel,textLine);
			nxtDisplayTextLine(menu, csel);
		} else {
			nxtDisplayCenteredTextLine(menu, textLine);
		}
	}
	return;
}

// * END MENU DEFINITIONS * //

void setGyroEnabled(bool enabled) {
	selection[3] = (enabled ? 1 : 0);
}

bool gyroEnabled() {
	return selection[3]==1;
}

void initMenus() {
	updateMenus(0,0);
	return;
}

long leftRep;
long rightRep;
long centerRep;
bool menuLocked = false;
short currentMenu=0;
short currentSelection=0;

void processMenuInput() {
	if (keyRepeater(&centerRep, (nNxtButtonPressed==3))) {
		currentMenu++;
		if (currentMenu>N_MENUS) currentMenu=0;
		if (currentMenu==N_MENUS) {
			PlaySound(soundException);
			menuLocked=true;
			nxtDisplayCenteredTextLine(7, "**LOCKED**");
		} else {
			PlaySound(soundBlip);
			menuLocked=false;
			eraseDisplay();
			currentSelection=selection[currentMenu];
			updateMenus(currentMenu, currentSelection);
		}
	} else if (nNxtButtonPressed>=1 && !menuLocked) {
		if (keyRepeater(&leftRep, (nNxtButtonPressed==2))) {currentSelection--;PlaySound(soundBlip);}
		if (keyRepeater(&rightRep, (nNxtButtonPressed==1))) {currentSelection++;PlaySound(soundBlip);}
		currentSelection=wrapSelection(currentMenu, currentSelection);
		selection[currentMenu]=currentSelection;
		updateMenus(currentMenu, currentSelection);
	} else {
		leftRep=0;rightRep=0; //These two don't get checked every time around
	}
	return;
}
