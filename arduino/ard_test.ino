// get this party started

void setup()
{
    // set up a pinMOde for an LED
    pinMode(LED_BUILTIN, OUTPUT);
    // start the serial port
    Serial.begin(9600);
    // print a message to the serial port
    Serial.println("Hello World!");
}

void loop()
{

    // create a function to blink the LED


    // blink the light even 2 seconds
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(2000);

}