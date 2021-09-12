
# VE.Direct-to-ESP8266-to-MQTT
Module to connect Victron BMV to MQTT.
For now this is not a fully working code since it stops sometimes after a few second and other times after a few days. Use it at your own risk

Parts of code are taken from this page and are NOT mine.

https://community.blynk.cc/t/victron-bmv-700-wemos-d1-mini/32558

I will be updating and writing code for this project WHEN I have time to do it.

# Connecting BMV712(in my case) to ESP8266 NodeMcu v3

Connect D7 PIN to PIN3 on BMV

Connect D8 PIN to PIN2 on BMV(not needed for now maybe in future)

Connect GND PIN to PIN1 on BMV

#DO NOT CONNECT PIN4 TO 3.3V ON ESP8266 BOARD SINCE BMV CANNOT PROVIDE ENOUGH CURRENT TO RUN ESP!!!

![victron pinout](https://user-images.githubusercontent.com/42915702/133002595-a9e81e5d-dcbd-4e17-8de0-89d49331e5db.png)
