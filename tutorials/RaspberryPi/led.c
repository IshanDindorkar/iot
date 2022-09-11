#include <wiringPi.h>

main() {

	// Initialize wiringPi
	wiringPiSetup();

	// Configure GPIO.0 as output
	pinMode(0, OUTPUT);

	// Blink
	while (1) {
		// Turn LED ON
		digitalWrite(0, 1);
		delay(500);

		// Turn LED OFF
		digitalWrite(0, 0);
		delay(500);
	}
}
