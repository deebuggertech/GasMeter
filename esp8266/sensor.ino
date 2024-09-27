#include <QMC5883LCompass.h>

QMC5883LCompass sensor;

//Put Sensor Tresholds Here
int sensorHighTreshold = 5000;
int sensorLowTreshold = -10000;


void initSensor(){
  sensor.init();
  appendToLogFile("Sensor Initialized");
}

unsigned long lastReading = 0;
bool passedHighState = false;
void runSensor(){
  if(millis() - lastReading > 2000){
    sensor.read(); 
    //Modify Sensor Axis Here
    int currentValue = sensor.getY();
    if(currentValue > sensorHighTreshold){
      passedHighState = true;
    } else if (currentValue < sensorLowTreshold && passedHighState){
      appendToLogFile("       Rotation Detected");
      analogWrite(LED_BUILTIN, 0);
      countRotation();
      passedHighState = false;
      delay(100);
      analogWrite(LED_BUILTIN, 253);
    }
    lastReading = millis();
  }
}