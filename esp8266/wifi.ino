#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void initWiFiConnection() {

  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  //Put WiFi Credentials Here
  wifiMulti.addAP("SSID0", "PASS0");
  wifiMulti.addAP("SSID1", "PASS1");

  while (wifiMulti.run() != WL_CONNECTED) {
    for (int i = 250; i >= 0; i -= 10) {
      analogWrite(LED_BUILTIN, i);
      delay(50);
    }
    for (int i = 0; i <= 250; i += 10) {
      analogWrite(LED_BUILTIN, i);
      delay(50);
    }
  }

  analogWrite(LED_BUILTIN, 253);

}


void maintainWiFiConnection() {
  while (wifiMulti.run() != WL_CONNECTED) {
    for (int i = 250; i >= 0; i -= 10) {
      analogWrite(LED_BUILTIN, i);
      delay(50);
    }
    for (int i = 0; i <= 250; i += 10) {
      analogWrite(LED_BUILTIN, i);
      delay(50);
    }
  }
}
