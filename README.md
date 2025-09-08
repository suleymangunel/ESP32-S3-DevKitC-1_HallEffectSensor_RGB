# ESP32-S3-DevKitC-1_HallEffectSensor_RGB

In this project we will be turn on/off ESP32's built in RGB LED according to hall effect sensor's state which connected to ESP32's GPIO #4 Pin. ESP32's built in RGB LED connected to GPIO #48 in v1.0, GPIO #38 in v1.1 

Project parts:
- ESP32-S3-DevKitC-1 v1.1 [N8R8] [Espressif]
- A3144 Hall Effect Sensor
- Breadboard for prototype circuit before PCB design

Place ESP32 on board and connect Hall Effect Sensor's pins below order:
- Pin-1 -> ESP32 Pin-1 (3V3)
- Pin-2 -> ESP32 Pin-22 (GND)
- Pin-3 -> ESP32 Pin-4 (GPIO #4)
