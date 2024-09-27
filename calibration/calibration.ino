#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>
#include <QMC5883LCompass.h>

#define LED D4

ESP8266WebServer server(80);
ESP8266WiFiMulti wifiMulti;
QMC5883LCompass sensor;

void handleRoot() { 
server.send(200, "text/html", 
  String("<!DOCTYPE html><html><head><title>GasMeter - Calibration</title><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /><meta http-equiv=\"Cache-Control\" content=\"no-cache, no-store, must-revalidate\" /><meta http-equiv=\"Pragma\" content=\"no-cache\" /><meta http-equiv=\"Expires\" content=\"0\" /><style>:root {--font-color: #ffffff;--shadow-color: rgba(130, 130, 130, 0.4);--ui-appearance-button-color: #aebcce;--window-bg-color: #11111d;--content-bg-color: #1f1f2b;--color-chart-line: #595959;--color-chart-font: #ffffff;}body {margin: 0;padding: 0;background-color: var(--window-bg-color);cursor: default;color: var(--font-color);font-family: 'Inter', sans-serif;}.header {padding: 27px;display: flex;align-items: center;justify-content: space-between;flex-wrap: wrap;background-color: var(--content-bg-color);}.header .title {font-size: 22px;font-weight: bold;text-shadow: 2px 1px var(--shadow-color);}.content {margin: auto;max-width: 1250px;}.container-large {margin: 10px;background-color: var(--content-bg-color);border-radius: 15px; padding: 10px;}.container-large .title {font-size: 20px;font-weight: bold;padding-top: 5px;padding-left: 5px;}.chart-container { height: 400px;}@media (max-width: 1150px) {.chart-container {height: 350px;}}@media (max-width: 650px) {.chart-container {height: 240px;}}</style><script src=\"https://cdn.jsdelivr.net/npm/chart.js@4.4.0/dist/chart.umd.min.js\"></script><script>var chart;var gas_meter_address = \"") +
  String(WiFi.localIP().toString()) + 
  String("\";document.addEventListener(\"DOMContentLoaded\", (event) => {createCharts();setInterval(updateData, 1000);});var getJSON = function(url, callback) {var xhr = new XMLHttpRequest();xhr.open('GET', url, true);xhr.responseType = 'json';xhr.onload = function() {var status = xhr.status;if (status === 200) {callback(null, xhr.response);} else {callback(status, xhr.response);}};xhr.send();};function updateData(){getJSON('http://'+gas_meter_address+'/get',function(err, data) {if (err !== null) {alert('ERROR: ' + err);} else {var d = new Date();chart.data.labels.push(d.toLocaleTimeString());chart.data.datasets[0].data.push(data.sensor_value_x);chart.data.datasets[1].data.push(data.sensor_value_y);chart.data.datasets[2].data.push(data.sensor_value_z);chart.data.datasets[3].data.push(data.esp_wifi_rssi);chart.update();}});}function createCharts(){var ctx = document.getElementById('chart');if (ctx) {chart = new Chart(ctx.getContext('2d'), {type: 'line',data: {labels: [],datasets: [{label: 'Sensor Data X',data: [],borderColor: ['#007cb9'],yAxisID: 'y',borderWidth: 2},{label: 'Sensor Data Y',data: [],borderColor: ['#fda403'],yAxisID: 'y',borderWidth: 2},{label: 'Sensor Data Z',data: [],borderColor: ['#845ec2'],yAxisID: 'y',borderWidth: 2},{label: 'WiFi RSSI',data: [],borderColor: ['#7dd87d'],yAxisID: 'y2',borderWidth: 2}]},options: {animation: {duration: 500 },scales: {y: {grid: {color: getComputedStyle(ctx).getPropertyValue(\"--color-chart-line\")},gridLines: {display: false,drawBorder: false,drawOnChartArea: false},ticks: {maxTicksLimit: 6,color: getComputedStyle(ctx).getPropertyValue(\"--color-chart-font\"),},suggestedMax: 10,suggestedMin: -10,},y2: {position: 'right',grid: {display: false},gridLines: {display: false,drawBorder: false,drawOnChartArea: false},ticks: {maxTicksLimit: 6,color: getComputedStyle(ctx).getPropertyValue(\"--color-chart-font\"),callback: function(value, index, ticks) {return value + \" dBm\";}},suggestedMax: -50,suggestedMin: -100,},x: {grid: {color: getComputedStyle(ctx).getPropertyValue(\"--color-chart-line\")},ticks: {maxTicksLimit: 6,color: getComputedStyle(ctx).getPropertyValue(\"--color-chart-font\"),},}},elements: {point: {radius: 4,hitRadius: 20}},plugins: {legend: {position: 'top',align: 'end',labels: {boxWidth: 6,boxHeight: 6,usePointStyle: true,color: getComputedStyle(ctx).getPropertyValue(\"--color-chart-font\"),font: {size: 12,weight: 'bold',}}},tooltip: {displayColors: false,callbacks: {label: function(context) {var label = [];if(context.dataset.yAxisID == \"y2\"){label.push(context.dataset.label + ': ' + context.parsed.y + 'dBm');}else{label.push(context.dataset.label + ': ' + context.parsed.y);}return label;}}}},tooltips: {mode: 'index',intersect: false},hover: {mode: 'nearest',intersect: true}}});}}</script></head><body><div class=\"header\"><div class=\"title\">GasMeter - Calibration</div></div><div class=\"content\"><div class=\"container-large\"> <div class=\"title\">Raw Sensor Data</div><div class=\"chart-container\"><canvas id=\"chart\" style=\"height: 100%; width: 100%;\"></canvas></div></div></div></body></html>")
);
}

void handleGet() {
sensor.read(); 
server.send(200, "application/json", 
  String("{\"sensor_value_x\": ") + String(sensor.getX()) +String(", \"sensor_value_y\": ") + String(sensor.getY()) +String(", \"sensor_value_z\": ") + String(sensor.getZ()) + String(", \"esp_wifi_rssi\": ") + String(WiFi.RSSI()) + String("}")
);
}

void setup() {

  pinMode(LED, OUTPUT);

  WiFi.mode(WIFI_STA);
  
  //Put WiFi Credentials Here
  wifiMulti.addAP("SSID0", "PASS0");
  wifiMulti.addAP("SSID1", "PASS1");

  if(wifiMulti.run() != WL_CONNECTED) {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
  }

  ArduinoOTA.setHostname("GasMeter__Calibration");
  ArduinoOTA.setPassword("nutella");
  ArduinoOTA.begin();

  sensor.init();
  
  server.on("/", handleRoot);
  server.on("/get", handleGet);
  server.onNotFound([]() {
        server.send(404, "text/plain", "Error");
  });  
  server.enableCORS(true);
  server.begin();
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
}
