#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <AccelStepper.h>

// WiFi
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Web server
ESP8266WebServer server(80);

// Stepper motor
#define STEP_PIN 5
#define DIR_PIN 4
AccelStepper stepper(1, STEP_PIN, DIR_PIN);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  // Set up stepper motor
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(1000);

  // Set up web server
  server.on("/move", []() {
    int steps = server.arg("steps").toInt();
    stepper.move(steps);
    server.send(200, "text/plain", "Stepper moved");
  });

  server.on("/stop", []() {
    stepper.stop();
    server.send(200, "text/plain", "Stepper stopped");
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient(); // Handle incoming requests
  stepper.run(); // Execute stepper movement
}

