#include <Servo.h>

int inches = 0;

int cm = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_9;

Servo servo_10;

void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  servo_9.attach(9, 500, 2500);

  servo_10.attach(10, 500, 2500);

}

void loop()
{
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  if (cm < 50) {
    digitalWrite(4, LOW);
    delay(1000); // Wait for 1000 millisecond(s)
    servo_9.write(0);
    servo_10.write(180);
    Serial.print("Now, Sanitization is off\n");
  } else {
    servo_9.write(90);
    servo_10.write(90);
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(4, HIGH);
    Serial.print("Now, Sanitizing\n");
  }
}
