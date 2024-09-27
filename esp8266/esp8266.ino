

void setup() {
  configTime("CET-1CEST,M3.5.0,M10.5.0/3", "europe.pool.ntp.org");
  initWiFiConnection();
  //initLogging();   //Optional
  initOTA();
  initSensor();
  initCounter();
  appendToLogFile("Starting Operation");
}

void loop() {
  maintainWiFiConnection();
  runOTA();
  runSensor();
  runCounter();
}
