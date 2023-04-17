#include <Wire.h>
#include <Adafruit_MAX31855.h>
#include <PID_v1.h>
#include <AccelStepper.h>

// Thermocouple
#define THERMO_CLK_PIN 3
#define THERMO_CS_PIN 4
#define THERMO_DO_PIN 5
Adafruit_MAX31855 thermocouple(THERMO_CLK_PIN, THERMO_CS_PIN, 
THERMO_DO_PIN);

// PID
double setPoint = 220;
double input, output;
double kp = 2, ki = 5, kd = 1;
PID myPID(&input, &output, &setPoint, kp, ki, kd, DIRECT);

// Stepper motor
#define STEP_PIN 6
#define DIR_PIN 7
AccelStepper stepper(1, STEP_PIN, DIR_PIN);

// Gate control
int gateStepSize = 10; // Adjust this value based on your specific setup

// Stepper motor limits
long stepperMinPos = 0;  // Minimum stepper position
long stepperMaxPos = 200;  // Maximum stepper position

void setup() {
  Serial.begin(9600);
  
  // Initialize thermocouple
  thermocouple.begin();

  // Initialize PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-gateStepSize, gateStepSize);

  // Initialize stepper motor
  stepper.setMaxSpeed(500); // Set maximum stepper speed
  stepper.setAcceleration(1000); // Set stepper acceleration
}

void loop() {
  // Read temperature in Fahrenheit
  double tempC = thermocouple.readCelsius();
  double tempF = tempC * 9.0 / 5.0 + 32.0;
  input = tempF;
  
  // Compute PID output
  myPID.Compute();

  // Control stepper motor based on PID output
  if (output > 0 && stepper.currentPosition() > stepperMinPos) {
    // Rotate stepper motor clockwise to close the gate
    stepper.move(-output);
  } else if (output < 0 && stepper.currentPosition() < stepperMaxPos) {
    // Rotate stepper motor counter-clockwise to open the gate
    stepper.move(-output);
  }

  // Execute stepper movement
  stepper.run();

  // Print temperature and stepper position (optional)
  Serial.print("Temperature: ");
  Serial.print(tempF);
  Serial.print("F | Stepper position: ");
  Serial.println(stepper.currentPosition());
  delay(1000);
}

