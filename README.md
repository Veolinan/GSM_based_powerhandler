# GSM_based_powerhandler
# Arduino Uno, DS1302 RTC, and SD Card Module Connections

# Connection Readme for DS1302 RTC and SD Card Module

This document provides the connection details for the DS1302 RTC module and the SD card module when used with an Arduino Uno. Please ensure you have the necessary libraries installed in your Arduino IDE for RTC and SD card functionality.

## DS1302 RTC Module:

1. **DS1302 Module to Arduino Uno:**

   - CE (Chip Enable) of the DS1302 module to Arduino Pin 6.
   - IO (Data Input/Output) of the DS1302 module to Arduino Pin 5.
   - SCLK (Serial Clock) of the DS1302 module to Arduino Pin 4.
   - VCC (Power) of the DS1302 module to Arduino 5V.
   - GND (Ground) of the DS1302 module to Arduino GND.

2. **Backup Battery (Optional):**
   - If your DS1302 module has a battery slot, insert a CR2032 or similar coin cell battery to retain time when the main power is disconnected. Connect the positive side of the battery to the BAT pin and the negative side to GND on the DS1302 module.

3. **Library Installation:**

   To use the DS1302 RTC module, you need to install the TimeLib library. Follow these steps to manually install the library:

   - Download the TimeLib library by downloading the arduino-ds1302-master.zip file from the official GitHub repository (https://github.com/PaulStoffregen/Time).

   - In your Arduino IDE, click on "Sketch" in the menu and then select "Include Library" and then "Add .ZIP Library..."

   - Browse to the location where you downloaded the arduino-ds1302-master.zip file and select it.

   - The TimeLib library will be installed.

## SD Card Module:

1. **SD Card Module to Arduino Uno:**

   - CS (Chip Select) of the SD card module to Arduino Pin 10.
   - MOSI (Master Out Slave In) of the SD card module to Arduino Pin 11.
   - MISO (Master In Slave Out) of the SD card module to Arduino Pin 12.
   - SCK (Serial Clock) of the SD card module to Arduino Pin 13.
   - VCC (Power) of the SD card module to Arduino 5V.
   - GND (Ground) of the SD card module to Arduino GND.

2. **SD Card Insertion:**
   - Insert a microSD card into the SD card module. Ensure that the card is properly formatted (FAT16 or FAT32) and contains the necessary directories and files for data storage.

3. **SD Card Module Wiring Notes:**
   - Make sure the connections are secure, and the wires are not loose.
   - Double-check the wiring to ensure there are no loose or disconnected wires.

**Note:** The buzzer connection is not specified in the code and should be connected separately.

---
👥 **Contributors**




![GitHub Contributors Image](https://contrib.rocks/image?repo=Veolinan/GSM_based_powerhandler)




A special thanks to all the contributors who have played a vital role in enhancing this project with their technical expertise and creative solutions. Your contributions have been instrumental in shaping the success of this Arduino Uno, DS1302 RTC, and SD Card Module project. Together, we're building a more connected and innovative future through open-source collaboration.



## 👁️ Profile Views
![Profile View Counter](https://komarev.com/ghpvc/?username=Veolinan)






