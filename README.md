# GasMeter

This project is about a small device designed to read data from a home gas meter, visualize it in a web dashboard, and store it for long-term analysis. The requirements for this project are a gas meter with a magnet on the rotating shaft (detectable using the phyphox app) and a stable WiFi connection at the gas meter location (a WiFi repeater may be needed).

## Functionality

The device uses a hall sensor to detect changes in the magnetic field caused by the magnet on the gas meter's rotating wheel, which represents 0.01 m³ increments. The sensor chosen is the **ADXL335**, a 3-axis hall sensor with a built-in I2C ADC. This sensor offers detailed data without requiring precise placement. An ESP8266 (e.g., NodeMCU) processes and transmits the data. You can use smaller modules like the ESP-01, but code modifications may be needed.

## Hardware Requirements

- ESP8266 NodeMCU Microcontroller
- ADXL335 Magnetic Field Sensor
- Soldering Equipment
- 3D Printer

## Setup

### 1. Hardware Assembly

Connect the sensor to the ESP using this basic schematic:

![Schematic](https://github.com/user-attachments/assets/5e1fccb5-d3f4-4b5d-909b-80e2e2a47835)

I designed an enclosure for the sensor and NodeMCU to easily attach it to the gas meter. You can find the 3D model in this repository and modify/print it yourself.

![Device](https://github.com/user-attachments/assets/9182cbe1-2c75-4740-9626-8551ef7d8b6e)

Assemble the electronics and place them in the enclosure.

### 2. Sensor Calibration

Calibration is needed to account for variations in sensor alignment and gas meter types. Open the sketch in the `calibration` directory, modify WiFi credentials, and upload it to your ESP8266. Attach the device to the gas meter and open `calibration.html` in a web browser, entering the ESP8266's IP address. After a few minutes, you should see a chart like this:

![Calibration](https://github.com/user-attachments/assets/3a31157f-8c77-43bd-9e81-0ea84de66452)

Choose the sensor axis with the highest amplitude and set low and high threshold values within the range.

### 3. Server Configuration

Copy the `API` and `UI` directories to your home or remote server. Ensure PHP is installed. Modify the `config.php` and `script.js` files with your settings.

### 4. ESP8266 Setup

Open the sketch in the `esp8266` directory using the Arduino IDE, update WiFi credentials, enter the server API endpoint URL (e.g., `http://.../API/`), select the desired sensor axis, and set the threshold values.

That's it! Your GasMeter device is now ready to collect and display gas consumption data.
