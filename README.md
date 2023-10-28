# GSM_based_powerhandler
# Arduino Uno, DS1302 RTC, and SD Card Module Connections

This guide explains the connections required to set up an Arduino Uno with a DS1302 RTC module and an SD card module as used in the provided code.
1. **DS1302 Module to Arduino Uno:**

   - CE (Chip Enable) of the DS1302 module to Arduino Pin 6.
   - IO (Data Input/Output) of the DS1302 module to Arduino Pin 5.
   - SCLK (Serial Clock) of the DS1302 module to Arduino Pin 4.
   - VCC (Power) of the DS1302 module to Arduino 5V.
   - GND (Ground) of the DS1302 module to Arduino GND.

2. **Backup Battery (Optional):**
   - If your DS1302 module has a battery slot, insert a CR2032 or similar coin cell battery to retain time when the main power is disconnected. Connect the positive side of the battery to the BAT pin and the negative side to GND on the DS1302 module.

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
   - Make sure the connections are secure and the wires are not loose.
   - Double-check the wiring to ensure there are no loose or disconnected wires.

Please ensure that the connections are made correctly according to the above descriptions. The code provided assumes these pin connections. If you decide to use different pins, make sure to update the code accordingly.

**Note:** The buzzer connection is not specified in the code and should be connected separately.

---

👥 **Contributors**

## 👁️ Profile Views
![Profile View Counter](https://komarev.com/ghpvc/?username=Veolinan)


![GitHub Contributors Image](https://contrib.rocks/image?repo=Veolinan/GSM_based_powerhandler)

👁️ **Repository Views**
![Repository Views](https://img.shields.io/github/views/Veolinan/GSM_based_powerhandler?label=Views&style=flat-square)


A special thanks to all the contributors who have played a vital role in enhancing this project with their technical expertise and creative solutions. Your contributions have been instrumental in shaping the success of this Arduino Uno, DS1302 RTC, and SD Card Module project. Together, we're building a more connected and innovative future through open-source collaboration.






