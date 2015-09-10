# ESP-pimatic
ESP talking to pimatic

Things you need:
* Arduino core for ESP8266 https://github.com/esp8266/Arduino (follow install instructions there)
* ESP8266 I used the ESP-01
* FTDI to serial adapter http://www.banggood.com/FT232RL-FTDI-USB-To-TTL-Serial-Converter-Adapter-Module-For-Arduino-p-917226.html

I used the following settings in IDE to programm the ESP module:
Board: "Generic ESP8266 Module"
Flash Mode: "DIO"
Flash Frequency: "40MHz"
Upload using: "Serial"
CPU Freq: "80 MHz"
Flash size: "512K"
Upload speed: "115200"
Port: "COMxx" 

Programmer: "USBtinyISP"

![alt tag](https://github.com/incmve/ESP-pimatic/img.png)