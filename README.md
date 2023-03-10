# esphome-somfy-receiver
ESPHome configuration files and tutorial to detect whenever a Somfy RTS remote is pressed.

# Introduction
I have a lot of Somfy blinds (RTS protocol) at home I control with a RFXCOM in Home Assistant.
All the Somfy remotes are usable at home because I don't want to rely only on Home Assistant and RFXCOM.

I needed a way to dectect whenever one of the remotes was pressed in order to determine the current position of any blinds.
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
The new range is way better (about 20 meters with 2 walls).

## Wiring

The important point is to link DATA pin of the receiver with D1 pin.
If you change this wiring, be sure to adapt the code at https://github.com/rdorys/esphome-somfy-receiver/blob/17990dc6e11c2f40b47b40d1879e42ff74c75f1d/somfy_sniff/main.h#L8

![image](https://user-images.githubusercontent.com/46494654/210221803-fdbf3ddf-060e-404d-a9fd-691217b232d8.png)


Note: Wiring for Aurel tranceiver is a bit different. According to the datasheet (https://www.aurelwireless.com/wp-content/uploads/user-manual/650201033G_um.pdf)

- Enable PIN needs to be connected to VCC (+5V)
- TX/RX PIN needs to be connected to GND to be in receiver mode.
- A 100nF capacitor is recommanded between VCC and GND.


# Output
The project results in four sensors in Home Assistant :

![image](https://user-images.githubusercontent.com/46494654/210219960-e3497f3b-1e02-4e0e-866b-e682c9d68c0d.png)

- Address is the unique ID of the remote, you can use it to know what remote has been pressed.
- ControlCode is the order sent by the remote, from https://pushstack.wordpress.com/somfy-rts-protocol/ we have :

![image](https://user-images.githubusercontent.com/46494654/210218489-eafac4cf-3a19-4746-b353-35d43748a5f3.png)

In pratice, I only have 1,2 or 4 (STOP, UP or DOWN).
- RollingCode, which increases by one each time (not very useful for me)
- LastTimeUpdate, which gives you the timestamp of last update (may be useful to compute new blinds position).
