// TODO: https://github.com/me-no-dev/ESPAsyncWebServer#send-large-webpage-from-progmem
// https://navody.arduino-shop.cz/navody-k-produktum/esp8266-vyvojova-deska-wemos-d1.html
// https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
// https://navody.arduino-shop.cz/navody-k-produktum/esp-wifi-webserver.html
// https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/
// https://www.arduino.cc/en/Hacking/libraryTutorial


// WemosD1 Smart thermometer
#include <EEPROM.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "html_templates.h"

const char* apSsid     = "IOT-ThermoHumid";
const char* apPassword = "123456789";

AsyncWebServer server(80);

void setup() {
  // Initialize EEPROM
  EEPROM.begin(512);
  // Initialize Serial
  Serial.begin(9600);
  delay(500);

  loadSsidAndPassword();
  // TODO - IF - state

  startNoNetworkServer();
  // Print ESP8266 Local IP Address
}

void loop() {
  
}

void writePassword()
{
    // Write password and SSID
  /*
  const String defaultNetwork = "myNetwork";
  const String defaultPassword = "password";
  
  writeSsidAndPasswordToEEPROM(defaultNetwork, defaultPassword);
  EEPROM.commit();
  */
}

void loadSsidAndPassword()
{
  String savedSSIDAndPassword = readStringFromEEPROM(0);
  Serial.println("Saved SSID and password are " + savedSSIDAndPassword);

  String savedSSID = getSSIDFromString(savedSSIDAndPassword);
  Serial.println("Saved SSID ais " + savedSSID);

  String savedPassword = getPasswordFromString(savedSSIDAndPassword);
  Serial.println("Saved password is " + savedPassword);
}

void startNoNetworkServer()
{
  WiFi.softAP(apSsid, apPassword, 4);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->redirect("/setup");
  });
  
  server.on("/setup", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });

  server.on("/api/confirmSsidAndPassword", HTTP_POST, [](AsyncWebServerRequest *request){
    if(request->hasParam("ssid", true) && request->hasParam("password", true)){
      AsyncWebParameter* ssid = request->getParam("ssid", true);
      AsyncWebParameter* password = request->getParam("password", true);
      Serial.println("Saving ssid and password");
      writeSsidAndPasswordToEEPROM(ssid->value().c_str(), password->value().c_str());
    }
    request->send(200);
  });
  
  server.begin();
}
