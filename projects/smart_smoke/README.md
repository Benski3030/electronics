# Temperature Controlled Smoker with Arduino, Stepper Motor, PID, and Thermocouple

## Table of Contents
- [Temperature Controlled Smoker with Arduino, Stepper Motor, PID, and Thermocouple](#temperature-controlled-smoker-with-arduino-stepper-motor-pid-and-thermocouple)
  - [Table of Contents](#table-of-contents)
  - [Introduction ](#introduction-)
  - [Components ](#components-)
    - [Step 1: Connect the Thermocouple to Arduino ](#step-1-connect-the-thermocouple-to-arduino-)
    - [Step 2: Connect the Stepper Motor and Driver ](#step-2-connect-the-stepper-motor-and-driver-)
    - [Step 3: Implementing the PID Controller ](#step-3-implementing-the-pid-controller-)
    - [Step 4: Programming the Logic ](#step-4-programming-the-logic-)
    - [Step 5: Testing and Fine-tuning ](#step-5-testing-and-fine-tuning-)

## Introduction <a name="introduction"></a>
This documentation will guide you through the process of setting up an Arduino-based temperature control system for your smoker. This system will help maintain the optimal temperature of 220°F (104°C) while smoking meat.

## Components <a name="components"></a>

- Arduino (Uno or similar)
- Stepper motor (with driver)
- PID controller
- Thermocouple temperature sensor (K-type)
- Jumper wires
- Breadboard
- Power supply for the stepper motor

### Step 1: Connect the Thermocouple to Arduino <a name="step1"></a>

1. Connect the thermocouple sensor's positive (red) wire to the A0 analog input pin on the Arduino.
2. Connect the thermocouple sensor's negative (black) wire to the GND (ground) pin on the Arduino.

### Step 2: Connect the Stepper Motor and Driver <a name="step2"></a>

1. Connect the stepper motor to the driver as per the motor's datasheet.
2. Connect the driver's input pins (step, direction, and enable) to the corresponding digital pins on the Arduino (e.g., pins 2, 3, and 4).
3. Connect the driver's ground (GND) to the Arduino's GND.
4. Connect the motor's power supply to the driver, ensuring it meets the motor's voltage and current requirements.

### Step 3: Implementing the PID Controller <a name="step3"></a>

1. Upload the PID library to the Arduino IDE (if not already installed) using Sketch > Include Library > Manage Libraries.
2. In the Arduino IDE, create a new sketch and include the following libraries: PID_v1.h and OneWire.h.
3. Declare global variables for the PID controller, setpoint, and input/output values.
4. Initialize the PID controller in the setup() function by setting the tuning parameters (Kp, Ki, and Kd) and specifying the input, output, and setpoint variables.
5. Set the PID mode to AUTOMATIC and the sample time to an appropriate value (e.g., 1000ms).

### Step 4: Programming the Logic <a name="step4"></a>

1. In the loop() function, read the thermocouple temperature and store it in the input variable.
2. Call the PID.Compute() function to update the output value based on the current temperature.
3. Use the output value to control the stepper motor's rotation, adjusting the smoker's gate accordingly.
4. Implement a delay (e.g., 5 seconds) to prevent rapid fluctuations in the gate's position.

### Step 5: Testing and Fine-tuning <a name="step5"></a>

1. Upload the sketch to the Arduino and monitor the smoker's temperature.
2. Observe the system's performance and fine-tune the PID parameters
