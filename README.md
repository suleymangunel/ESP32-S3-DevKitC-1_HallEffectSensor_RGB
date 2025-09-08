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


After you create the project with "idf.py create-project rgb_pin" command (the name "rgb_pin" is the name of my local project, of course you are free to give it any name you want) you must be add "led_strip_encoder.c" string into CMakeLists.txt located in folder named "main" in your project folder (for my project: rgb_pin/main/CMakeLists.txt). After this update you must copy "led_strip_encoder.h" and "led_strip_encoder."c files from their original location (this two files located under examples/../.. for my installation) to main folder. After completing all this, we must be run below commands

Step-1) list /dev (Find "tty.usbserial-XXXX" string in this list and note that for use in Step-4)
Step-2) idf.py set-target esp32s3
Step-3) idf.py build
Step-4) idf.py -p /dev/tty.usbserial-XXXX build flash

If everything is OK, you should see the built in RGB LED on the ESP32 turn red when you move the magnet closer to the hall effect sensor connected to GPIO #4.
