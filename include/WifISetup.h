#ifndef WIFISetup_h
#define WIFISetup_h

 

#include <LittleFS.h>
#include <ESPAsyncWiFiManager.h>
#include <ESPAsyncWebServer.h>
#define HTTP_PORT           80

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>ESP Image Web Server</h2>
  <img src="/sun" widht="100px" height="100px">
</body>  
</html>)rawliteral";


AsyncWebServer webServer(HTTP_PORT);
void initWebServer();
DNSServer dns;

void setClock() {
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Waiting for NTP time sync: ");
  time_t now = time(nullptr);
  uint cnt=0;
  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
    if(cnt %2 ==0 )
      {
         digitalWrite(LED_BUILTIN, LOW);
      }
      else
      {
          digitalWrite(LED_BUILTIN, HIGH);
        }
    cnt++;
  }
  Serial.println("");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
  
}
String myTime()
{
  time_t now;
  struct tm timeinfo;
  char buffer[80];
  time(&now);
  localtime_r(&now, &timeinfo);
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buffer);
}


#pragma region Wifi Part 
void configModeCallback (AsyncWiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
  
 
}

void initWifi()
{
  bool res;

   WiFi.mode(WIFI_STA);

    AsyncWiFiManager  wm(&webServer, &dns);
    wm.setAPCallback(configModeCallback);
    //wm.resetSettings();
    wm.setDebugOutput(true);  
  res = wm.autoConnect("ESP32AP"); // Anonymous AP
 // Uncomment to reset settings
  if(!res) {
       
        Serial.println("Failed to connect.");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("Connected.");
       
        setClock();
       initWebServer();
    }
  /* webServer.on("/sun", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, IMAGE_NAME, "image/jpg");
  });
  */

}




void initWebServer()
{
  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", "<h1>Hello, this is your web server!</h1>");
  });

  //ElegantOTA.begin(&webServer);   // Start ElegantOTA
  webServer.begin();
}
#pragma endregion
#endif