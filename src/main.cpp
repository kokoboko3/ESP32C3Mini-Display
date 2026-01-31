#include <Arduino.h>
#include "WifISetup.h"
#include "SetupWebServer.h"
#include "U8g2Setup.h"



void setup() {

  // put your setup code here, to run once:
   Serial.begin(115200);
  Serial.println("Hello, ESP32-C3!");
  initScreen();
  drawScreen("Hello, ESP32-C3!","WiFi...");
  initWifi();
  drawScreen((WiFi.localIP().toString()).c_str(),myTime().c_str());
  drawScreen("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
}

