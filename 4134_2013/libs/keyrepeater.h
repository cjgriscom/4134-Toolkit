#ifndef KEY_REPEATER
#define KEY_REPEATER

// The key repeater emulates a computer keyboard-like response of pressing and holding a key
// Pass in and store the repeater reference with the declaration "long rep;" globally, and pass in as "repeater(&rep,..."

bool keyRepeater(long *reference, bool buttonState) {

	if (buttonState) {
		// Button is pressed
		if (*reference == 0) {
			// Timer has not started; return initial press and start timer
			*reference = time10[T4];
			return true;
		} else {
			if (time10[T4] > *reference+50) { // Passed delay limit?
				return true; // Start repeating
			}
			return false; // Still waiting
		}
	} else {
		// Feeding button is not pressed
		*reference = 0;
		return false;
	}
}

#endif //KEY_REPEATER
