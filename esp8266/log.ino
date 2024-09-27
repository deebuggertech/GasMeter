#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient logWifiClient;
HTTPClient logHttpClient;

bool debug = false;

void initLogging() {
  debug = true;
  appendToLogFile(".");
  appendToLogFile(".");
  appendToLogFile(".");
  appendToLogFile("BOOT");
  appendToLogFile("Reason: "+String(ESP.getResetReason()));
  appendToLogFile("Logging Connection Initialized");
}

void appendToLogFile(String text) {
  if(debug){

  time(&now);
  localtime_r(&now, &tm);

  logHttpClient.begin(logWifiClient, apiBaseURL+"log/"+apiToken);
  logHttpClient.addHeader("Content-Type", "application/json");
  logHttpClient.POST("{\"esp_time\":\""+String(tm.tm_mday)+"."+String(tm.tm_mon+1)+"."+String(tm.tm_year+1900)+" "+String(tm.tm_hour)+":"+String(tm.tm_min)+":"+String(tm.tm_sec)+"\",\"message\":\""+text+"\"}");
  logHttpClient.end();

  }
}
