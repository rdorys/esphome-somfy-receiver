# esphome-somfy-receiver
ESPHome configuration files and tutorial to detect whenever a Somfy RTS remote is pressed.

# Introduction
I have a lot of Somfy blinds (RTS protocol) at home I control with a RFXCOM in Home Assistant.
All the Somfy remotes are usable at home because I don't want to rely only on Home Assistant and RFXCOM.

I needed a way to dectect whenever one of the remotes were pressed in order to determine the current position of any blinds.
This is actually not doable with a RFXCOM as Somfy works on 443.42MHz and the RFXCOM only listens on 443.92MHz.
The project doesn't describe how to determine this position. It only describes how to use the hardware and how to configure ESPHome.

This project is an adaptation of the great work of https://github.com/walterbrebels/somfy-rts
It worked well on my esp8266 and I wanted to get all the information in Home Assistant via ESPHome.

# Hardware

I use : 
- ESP8266 (D1 MINI)
- XY-MK-5V receiver
