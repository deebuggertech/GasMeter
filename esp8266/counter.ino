#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "LittleFS.h"
#include <time.h>

time_t now;
tm tm;

WiFiClient counterWifiClient;
HTTPClient counterHttpClient;

DynamicJsonDocument jsonDoc(2048);

String jsonDocFileName = "data.json";

//Put Server URL And Token Here
String apiBaseURL = "http://.../..../api/";
String apiToken = "?token=4QHWYyM";

int pushInterval = 5*60*1000;
int updateInterval = 10*60*1000;


bool dataChanged = false;
unsigned long lastPush = -pushInterval;
unsigned long lastUpdate = -updateInterval;


void initCounter() {
  

  LittleFS.begin();
  appendToLogFile("Counter Initialized");
}

void countRotation() {
  String hour = getCurrentHourString();
  String day = getCurrentDayString();

  checkForHourAndDayChange(hour, day);

  readJsonFile();
  jsonDoc["data"][hour]["consumption"] = String(jsonDoc["data"][hour]["consumption"]).toInt() + 10;
  writeJsonFile();

  dataChanged = true;
}

void runCounter() {

  if(millis() - lastPush > pushInterval){
    if(dataChanged){
      dataChanged = false;
      pushToServer();
    }
    lastPush = millis();
  }

  if(millis() - lastUpdate > updateInterval){
    checkForHourAndDayChange(getCurrentHourString(), getCurrentDayString());
    pushToServer();
    lastUpdate = millis();
  }
  
}


void pushToServer(){
  appendToLogFile("Pushing To Server");

  File file = LittleFS.open(jsonDocFileName, "r");
  String jsonString = file.readString();
  file.close();

  counterHttpClient.begin(counterWifiClient, apiBaseURL+"push/"+apiToken);
  counterHttpClient.addHeader("Content-Type", "application/json");
  counterHttpClient.POST(jsonString);
  counterHttpClient.end();
}


void checkForHourAndDayChange(String hour, String day) {
  readJsonFile();

  String hour_json = String(jsonDoc["current"]["hour"]);
  String day_json = String(jsonDoc["current"]["day"]);
  int consumption  = String(jsonDoc["current"]["consumption"]).toInt();

  if (!day.equals(day_json)) {
    appendToLogFile("Day Change Detected");
    if(dataChanged) pushToServer();
    clearJsonFile();
    jsonDoc["current"]["hour"] = hour;
    jsonDoc["current"]["day"] = day;

    jsonDoc["data"][hour]["consumption"] = 0;
    writeJsonFile();
  } else if (!hour.equals(hour_json)) {
    appendToLogFile("Hour Change Detected");
    jsonDoc["current"]["hour"] = hour;

    jsonDoc["data"][hour]["consumption"] = 0;
    writeJsonFile();
  }
}


void readJsonFile() {
  jsonDoc.clear();
  File file = LittleFS.open(jsonDocFileName, "r");
  deserializeJson(jsonDoc, file.readString());
  file.close();
}


void writeJsonFile() {
  File file = LittleFS.open(jsonDocFileName, "w");
  String output;
  serializeJson(jsonDoc, output);
  file.print(output);
  file.close();
  jsonDoc.clear();
}


void clearJsonFile() {
  File file = LittleFS.open(jsonDocFileName, "w");
  file.print("{}");
  file.close();
  jsonDoc.clear();
}


String getCurrentHourString() {
  time(&now);
  localtime_r(&now, &tm);
  int hour = tm.tm_hour;
  if(hour < 10){
  return "0" + String(hour) + ".00";
  }else{
  return String(hour) + ".00";
  }
}


String getCurrentDayString() {
  time(&now);
  localtime_r(&now, &tm);
  return String(tm.tm_mday) + "." + String(tm.tm_mon + 1) + "." + String(tm.tm_year + 1900);
}

