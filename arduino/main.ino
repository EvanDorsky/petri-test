#include <Servo.h>

// Servo variables
Servo servo;
int servoPin = 9;
int pos = 0;

// Sensor variables
int sensorPin = A0;

float rawRange = 1024; // 3.3v
float logRange = 5.0; // 3.3v = 10^5 lux

float processedLux() {
	return rawToLux(analogRead(sensorPin));
}

float rawToLux(int raw)
{
	float logLux = raw * logRange / rawRange;
	return pow(10, logLux);
}

void setup()
{
	analogReference(EXTERNAL);
	Serial.begin(9600);

	servo.attach(servoPin);
}

void loopServo() {
	for(pos = 0; pos < 180; pos += 1) {
		servo.write(pos);
		delay(15);
	}
	for(pos = 180; pos>=1; pos-=1) {
		servo.write(pos);
		delay(15);
	}
}

void loop() {
	if (Serial.available() > 0) {
		char incomingByte = Serial.read();

		Serial.print("I received: ");
		Serial.println(incomingByte);
	}
	
	loopServo();
}