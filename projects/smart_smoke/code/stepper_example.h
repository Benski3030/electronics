#include <Adafruit_MAX31856.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>


// set constants
const int stepsPerRevolution = 360;


// set variables
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

#define MotorInterfaceType 2

// initialize thermocouple
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(4, 5, 6, 7); // note the conflict

// initialize stepper motor
AccelStepper stepper(MotorInterfaceType, dirA, dirB);

// initialize LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// setup component for use
void setup() {
  Serial.begin(115200); //only needed for debugging
  while (!Serial) delay(100); 
  Serial.println("MAX31856 thermocouple test");

  lcd.init();                      // initialize the lcd 
  
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Smart Smoke!");
  
  //start the thermocouple
  maxthermo.begin();
  //configure the thermocouple
  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

  // configure the stepper
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
// clear the LCD
      lcd.clear();
}

void loop() {
  // clear the LCD



  Serial.print("Thermocouple Temp: ");
  // modift to convert to F

  float temp = maxthermo.readThermocoupleTemperature() * 9.0 / 5.0 + 32.0;
  Serial.print(maxthermo.readThermocoupleTemperature() * 9.0 / 5.0 + 32.0);

  // print the temp on the first row of the LCD
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" F");

  // calibrate the steppers
  int steps45 = (45.0 / 360.0) * stepsPerRevolution;
  
  // turn 45 degrees clockwise
  stepper.moveTo(steps45);
  stepper.runToPosition();
  Serial.println("Position: " + String(stepper.currentPosition()));
  // print the current position on the second row of the LCD
    lcd.setCursor(0,1);
    lcd.print("Position: ");
    lcd.print(stepper.currentPosition());
    lcd.print("   ");

  // return to zero
  stepper.moveTo(0);
  stepper.runToPosition();
  Serial.println("Position: " + String(stepper.currentPosition()));
      lcd.setCursor(0,1);
    lcd.print("Position: ");
    lcd.print(stepper.currentPosition());
    lcd.print("   ");

  // turn 45 degrees counterclockwise
  stepper.moveTo(-steps45);
  stepper.runToPosition();
  Serial.println("Position: " + String(stepper.currentPosition()));
      lcd.setCursor(0,1);
    lcd.print("Position: ");
    lcd.print(stepper.currentPosition());
    lcd.print("   ");

  // return to zero
  stepper.moveTo(0);
  stepper.runToPosition();
  Serial.println("Position: " + String(stepper.currentPosition()));  
      lcd.setCursor(0,1);
    lcd.print("Position: ");
    lcd.print(stepper.currentPosition());
    lcd.print("   ");

}
