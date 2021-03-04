# esp8266_dmx512
Minimal example of how to update DMX512 signals from ESP8266 via url params.

Uses ESP DMC library: https://github.com/Rickgg/ESP-Dmx

To use:

- connect D4 / GPIO2 / TX1 of ESP8266 to DI of MAX485
- connect 3v3 of ESP8266 to DE and VCC of MAX485
- connect GND to GND
- connect A of MAX485 to A of the DMX decoder, sometimes this is also called +
- connect B of MAX485 to B of the DMX decoder, sometimes this is also called -
- change SSID and PW values in the ino file
- Flash with ArduinoIDE
- send a GET request to /update, where the key/value pairs are the channels and their values ex:

    curl 1.2.3.4/update?1=10&2=5&3=8

will set channel 1 to 10, channel 2 to 5 and channel 3 to 8