# Stepper Motor Control with AccelStepper Library

This code demonstrates how to control a stepper motor using the AccelStepper library. The motor rotates +/- 45 degrees from the initial position.

### Setup Function

In the `setup()` function:

1. The motor control and brake pins are set as OUTPUT.
2. The PWM pins are set to HIGH and brake pins are set to LOW to enable motor movement.
3. The maximum speed and acceleration for the motor are set using setMaxSpeed() and setAcceleration().
4. The current motor position is set to 0.
5. The serial communication is initialized for monitoring motor position.

### Loop Function

The loop() function contains four main sections:

1. Turn 45 degrees clockwise: The target position is calculated and the motor moves to this position. The motor's position is printed to the serial monitor.
2. Return to zero: The motor moves back to the initial position. The motor's position is printed to the serial monitor.
3. Turn 45 degrees counterclockwise: The target position is calculated and the motor moves to this position. The motor's position is printed to the serial monitor.
4. Return to zero: The motor moves back to the initial position. The motor's position is printed to the serial monitor.

These steps are repeated indefinitely.

## Dependencies

- AccelStepper library

## Constants and Pin Definitions

- `stepsPerRevolution`: The number of steps required for the motor to complete one revolution (360 degrees). In this case, the value is set to 360.
- `pwmA`, `pwmB`: PWM pins for motor control
- `brakeA`, `brakeB`: Brake pins for motor control
- `dirA`, `dirB`: Direction pins for motor control
- `MotorInterfaceType`: The motor driver interface type (set to 2 for two wire control)

## AccelStepper Object Initialization

An AccelStepper object called `stepper` is initialized with the motor interface type and the direction pins.

```cpp
AccelStepper stepper = AccelStepper(MotorInterfaceType, dirA, dirB);
```