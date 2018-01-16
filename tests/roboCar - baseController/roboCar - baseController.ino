#include <Arduino.h>

class Joysticks{
private:
    const byte motorJoys[2] = {2, 3};
    const byte sonarJoy = 1;
    const byte signalBut = 3;
    const byte scanBut = 4;

    int preMotorsVals[2];
    int preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;

public:
    bool getMotorsJoys(int val[]) {void}
    bool getSonarJoy(int val) {void}
    bool getSonarState(void) {void}

};

void setup()
{
	Serial.begin(9600);

	// initialize the digital pin as an output.
	// Pin 13 has an LED connected on most Arduino boards:
	pinMode(13, OUTPUT);
}

void loop()
{
	Serial.println("Hello world!");

	delay(1000);              // wait for a second
	digitalWrite(13, HIGH);   // set the LED on
	delay(1000);              // wait for a second
	digitalWrite(13, LOW);    // set the LED off
}
