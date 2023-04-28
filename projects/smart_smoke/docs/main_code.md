
Explanation of Smart Smoke Control System Code

Importing Required Libraries

```c++
#include <Adafruit_MAX31856.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>

```

This block imports the necessary libraries for the smart smoke control system.

- Adafruit_MAX31856.h is the library for the MAX31856 thermocouple amplifier.
- AccelStepper.h is the library for the stepper motor driver.
- LiquidCrystal_I2C.h is the library for the LCD display.
- PID_v1.h is the library for the PID controller.

Constants

```c++
const int desiredTemperature = 74;
const int deadband = 1;
const int stepsPerRevolution = 360;
const int minStepperPosition = -43;
const int maxStepperPosition = 43;

```

This block defines the constants for the smart smoke control system.

- desiredTemperature is the temperature that the system is trying to maintain.
- deadband is the acceptable range of temperatures.
- stepsPerRevolution is the number of steps per revolution of the stepper motor.
- minStepperPosition and maxStepperPosition are the minimum and maximum positions of the stepper motor.

Pin Assignments

```c++
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

#define MotorInterfaceType 2

```

This block defines the pin assignments for the various components used in the smart smoke control system.

- pwmA, pwmB, brakeA, brakeB, dirA, and dirB are the pins used for controlling the stepper motor.
- MotorInterfaceType is the interface type used for the stepper motor driver.

Component Initialization

```c++
Adafruit_MAX31856 maxthermo(4, 5, 6, 7);
AccelStepper stepper(MotorInterfaceType, dirA, dirB);
LiquidCrystal_I2C lcd(0x27, 20, 4);

```

This block initializes the components used in the smart smoke control system.

- maxthermo initializes the MAX31856 thermocouple amplifier with pins 4, 5, 6, and 7.
- stepper initializes the stepper motor driver with the specified interface type and direction pins.
- lcd initializes the LCD display with the specified I2C address, number of columns, and number of rows.

PID Controller Variables and Gains

```c++
double inputTemperature, outputStepperPosition, setTemperature;

// testing values
double Kp = 1.0; // Proportional gain
double Ki = 1.0; // Integral gain (increased from 0.05)
double Kd = 0.5; // Derivative gain (increased from 0.01) 

```

This block defines the variables and gains for the PID controller.

- inputTemperature is the current temperature read from the thermocouple amplifier.
- outputStepperPosition is the desired position of the stepper motor.
- setTemperature is the desired temperature for the system.
- Kp, Ki, and Kd are the proportional, integral, and derivative gains for the PID controller.

PID Controller Initialization

```c++
PID myPID(&inputTemperature, &outputStepperPosition, &setTemperature, Kp, Ki, Kd, DIRECT);

```

with the gains, input and output parameters, and the direction of the controller.

- &inputTemperature is a pointer to the input temperature.
- &outputStepperPosition is a pointer to the output position of the stepper motor.
- &setTemperature is a pointer to the desired temperature.
- Kp, Ki, and Kd are the gains for the proportional, integral, and derivative control, respectively.
- DIRECT indicates that the controller should be direct acting.

Setup Function

```c++
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

```

This block initializes and configures the system components and the PID controller.

- Serial.begin(115200) initializes the serial communication with the specified baud rate.
- The LCD display is initialized and configured to show the system name and the PID values used.
- delay(5000) adds a delay of 5 seconds before initializing the thermocouple amplifier to allow it to stabilize.
- The thermocouple amplifier is initialized and configured to use the K-type thermocouple.
- The stepper motor is initialized and configured with the specified pins and values for maximum speed, acceleration, and current position.
- The LCD display is cleared.
- The PID controller is configured with the desired temperature as the setpoint, and the output limits are set to the minimum and maximum stepper motor positions.

Print Temperature Function

```c++
void printTemperature(int temp) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" F");
}

```

This function prints the current temperature to the LCD display.

Print Stepper Position Function

```c++
void printStepperPosition(int pos) {
  lcd.setCursor(0, 1);
  lcd.print("Position: ");
  lcd.print(pos);
  lcd.print("   ");
}

```

This function prints the current position of the stepper motor to the LCD display.

Loop Function

```c++
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
```

This block of code is executed repeatedly in the main loop. It reads the current temperature using the `maxthermo.readThermocoupleTemperature()` function and converts it to Fahrenheit. Then it calls the `printTemperature()` function to display the current temperature on the LCD.

The current temperature is assigned to the `inputTemperature` variable, which is used as input to the PID controller. The `myPID.Compute()` function runs the PID algorithm and computes the new output value for the stepper motor position, which is stored in the `outputStepperPosition` variable.

The `stepper.moveTo()` function is called to move the stepper motor to the calculated position, and the `stepper.runToPosition()` function is called to run the stepper motor to that position.

Finally, the `printStepperPosition()` function is called to print the current position of the stepper motor on the LCD, and a delay of 1 second is added to improve the stability of temperature readings. This loop is then repeated, updating the temperature, calculating the new stepper motor position, and running the motor to that position.

