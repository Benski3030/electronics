#include <Adafruit_MAX31856.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>

// Constants
const int desiredTemperature = 74;
const int deadband = 1;
const int stepsPerRevolution = 360;
const int minStepperPosition = -43;
const int maxStepperPosition = 43;

// Pin assignments
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

#define MotorInterfaceType 2

// Initialize components
Adafruit_MAX31856 maxthermo(4, 5, 6, 7);
AccelStepper stepper(MotorInterfaceType, dirA, dirB);
LiquidCrystal_I2C lcd(0x27, 20, 4);

// PID controller variables
double inputTemperature, outputStepperPosition, setTemperature;

// PID controller gains
//double Kp = 0.1; // Proportional gain
//double Ki = 0.1; // Integral gain
//double Kd = 0.01; // Derivative gain

// testing values
double Kp = 1.0; // Proportional gain
double Ki = 1.0; // Integral gain (increased from 0.05)
double Kd = 0.5; // Derivative gain (increased from 0.01) 

// Initialize PID controller
PID myPID(&inputTemperature, &outputStepperPosition, &setTemperature, Kp, Ki, Kd, DIRECT);

// Setup function
void setup() {
  Serial.begin(115200);
  // Initialize and configure LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Smart Smoke!");
  lcd.setCursor(2, 1);
  // display the PID values used
  lcd.print("PID:");
  lcd.print(Kp);
  lcd.print(Ki);
  lcd.print(Kd);
  
  delay(5000);
  while (!Serial) delay(100);


  // Initialize and configure thermocouple
  maxthermo.begin();
  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

  // Initialize and configure stepper motor
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

  // Clear the LCD
  lcd.clear();

  // Configure PID controller
  setTemperature = desiredTemperature;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(minStepperPosition, maxStepperPosition);
}

void printTemperature(int temp) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" F");
}

// Function to print stepper position on LCD
void printStepperPosition(int pos) {
  lcd.setCursor(0, 1);
  lcd.print("Position: ");
  lcd.print(pos);
  lcd.print("   ");
}


void loop() {
  // Read and print thermocouple temperature
  int currentTemperature = (int)round(maxthermo.readThermocoupleTemperature() * 9.0 / 5.0 + 32.0);
  printTemperature(currentTemperature);

  inputTemperature = currentTemperature; // Assign the current temperature to inputTemperature for PID calculation

  // Run the PID controller
  myPID.Compute();

  // Move stepper to the calculated position
  stepper.moveTo((int)outputStepperPosition);

  // Run the stepper motor
  stepper.runToPosition();

  // Print stepper position on LCD
  printStepperPosition(stepper.currentPosition());

  // Add a delay for better temperature reading stability
  delay(1000);
}