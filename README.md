# GSM_based_powerhandler
# Arduino Uno, DS1302 RTC, and SD Card Module Connections

This guide explains the connections required to set up an Arduino Uno with a DS1302 RTC module and an SD card module as used in the provided code.

## Components

1. Arduino Uno
2. DS1302 RTC Module
3. SD Card Module
4. Buzzer (if applicable, not mentioned in the code)

## Connections

**DS1302 RTC Module:**

- GND (Ground) - Connect to GND on Arduino Uno.
- VCC (Voltage) - Connect to 5V on Arduino Uno.
- CLK (Clock) - Connect to digital pin 2 on Arduino Uno.
- DAT (Data) - Connect to digital pin 3 on Arduino Uno.
- RST (Reset) - Connect to digital pin 4 on Arduino Uno.

**SD Card Module:**

- GND (Ground) - Connect to GND on Arduino Uno.
- VCC (Voltage) - Connect to 5V on Arduino Uno.
- MOSI (Master Out Slave In) - Connect to digital pin 11 on Arduino Uno.
- MISO (Master In Slave Out) - Connect to digital pin 12 on Arduino Uno.
- SCK (Serial Clock) - Connect to digital pin 13 on Arduino Uno.
- CS (Chip Select) - Connect to digital pin 10 on Arduino Uno.

Please ensure that the connections are made correctly according to the above descriptions. The code provided assumes these pin connections. If you decide to use different pins, make sure to update the code accordingly.

**Note:** The buzzer connection is not specified in the code and should be connected separately.

---

👥 **Contributors**

![GitHub Contributors Image](https://contrib.rocks/image?repo=Veolinan/GSM_based_powerhandler)

A special thanks to all the contributors who have played a vital role in enhancing this project with their technical expertise and creative solutions. Your contributions have been instrumental in shaping the success of this Arduino Uno, DS1302 RTC, and SD Card Module project. Together, we're building a more connected and innovative future through open-source collaboration.

👁️ **Profile Views**
![Hits](https://hitcounter.pythonanywhere.com/count/tag.svg?url=Paste_Your_GitHub_Repository_Link_Here)
