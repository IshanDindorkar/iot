#include <wiringPi.h>
#include <stdio.h>

void main() {
	int state = -1; // Button state

	// Initialise wiringPi, we will use wiringPi / simplified GPIO numbering
	wiringPiSetup();
	
	// Configure GPIO.2 as input, pull-up
	pinMode(2, INPUT);
	pullUpDnControl(2, PUD_UP);
	
	// Loop
	while (1) {
		int button = digitalRead(2);
		if (button != state) {
			if (button == 0) // Active LOW
				printf ("  -|: Pressed\n");
			else
				printf (" -| : Released\n");
			state = button;
		}
		
		delay(200);
	}
}
