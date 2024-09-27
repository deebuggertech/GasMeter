#include <ArduinoOTA.h>

void initOTA(){
  ArduinoOTA.setHostname("GasMeter");
  ArduinoOTA.setPassword("nutella");
  ArduinoOTA.begin();
  appendToLogFile("OTA Updating Initialized");
}


void runOTA(){
  ArduinoOTA.handle();
}
