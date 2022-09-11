#include <wiringPi.h>

void main() {

	// Initialise wiringPi, we will use wiringPi / simplified GPIO numbering
	wiringPiSetup();
	
	// Configure GPIO.0 as output
	pinMode(0, OUTPUT);
	
	// Blink
	while (1) {
		// Turn LED ON (drive GPIO.0 HIGH)
		digitalWrite(0, 1);
		// Sleep
		delay(1000);
		// Turn LED OFF (drive GPIO.0 LOW)
		digitalWrite(0, 0);
		// Sleep
		delay(1000);
	}
}
