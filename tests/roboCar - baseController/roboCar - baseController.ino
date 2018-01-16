#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
class Joysticks{
private:
    const byte motorJoys[2] = {2, 3};
    const byte sonarJoy = 1;
    const byte signalBut = 3;
    const byte scanBut = 4;

    int preMotorsVals[2];
    byte preSonarAngle;
    int motorJoysNeutral[2];
    int sonarJoyNeutral;

public:
    bool getMotorsJoys(int val[]) {void}
    bool getSonarJoy(int val) {void}
    bool getSonarState(void) {void}

};
class Indication{
private:
    //bool isMovingFlag;
    //bool isScanningFlag;

    const LiquidCrystal_I2C lcd;
    const byte movingFlagLED = 5;
    const byte scanningFlagLED = 6;
public:
    bool updateLCD(int data[]) {void}
    bool setMovingFlagLED(bool flag) {void}
    bool setScanningFlagLED
};
class Manager{
private:
    int motorVals[2];
    int sonarAngle;
    bool isScanningFlag;
    bool isSignallingFlag;
    bool isMovingFlag;
    int sensorData[3];
    int exertData[3];
public:
    bool readRadio();
    bool readControl();
    bool setIndication();
    bool sendCommandRadio();
    bool sendCommandSerial();
    void devSerialEvent();
    void ascSensors();
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
