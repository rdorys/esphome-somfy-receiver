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

The XY-MK-5V is a pretty cheap receiver, it works well but as RTS is modulated over 433.42MHz, you won't get a better range than a few meter with it.

I recently bought https://www.nodo-shop.nl/en/transmitters-and-receivers/194-aurel-tranceiver-rtx-mid-5v.html
I will keep you in touch about new range.

# Output
The project results in four sensors in Home Assistant :

![image](https://user-images.githubusercontent.com/46494654/210217882-6b7367fe-08da-4b4c-abab-603963c85f4a.png)

- Address is the unique ID of the remote, you can use it to know what remote has been pressed.
- ControlCode is the order sent by the remote, from https://pushstack.wordpress.com/somfy-rts-protocol/ we have :

![image](https://user-images.githubusercontent.com/46494654/210218489-eafac4cf-3a19-4746-b353-35d43748a5f3.png)
In pratice, I only have 1,2 or 4 (STOP, UP or DOWN).
- Rolling code, which increases by one each time (not very useful for me)
- lastTimeUpdate, which gives you the timestamp of last update.
