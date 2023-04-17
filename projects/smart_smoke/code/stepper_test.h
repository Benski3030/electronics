#include <AccelStepper.h>

const int stepsPerRevolution = 360;

#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

#define MotorInterfaceType 2

AccelStepper stepper = AccelStepper(MotorInterfaceType, dirA, dirB);

void setup() {
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);

  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);

  stepper.setMaxSpeed(300);
  stepper.setAcceleration(150);
  stepper.setCurrentPosition(0);

  Serial.begin(9600);
}

void loop() {
  int steps45 = (45.0 / 360.0) * stepsPerRevolution;

  // turn 45 degrees clockwise
  stepper.moveTo(steps45);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  Serial.println("Position: " + String(stepper.currentPosition()));

  // return to zeor
  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  Serial.println("Position: " + String(stepper.currentPosition()));

  // turn 45 degrees counterclockwise
  stepper.moveTo(-steps45);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  Serial.println("Position: " + String(stepper.currentPosition()));

  // return to zero
  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  Serial.println("Position: " + String(stepper.currentPosition()));
}
