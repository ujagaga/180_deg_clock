# ESP8266 Semi-mechanical Clock

This is a wall clock based on ESP8266. It uses a simple phone charger for power. 
The time is synchronized from local network. Hours are displayed using a servo motor that rotates only 180 degrees. Minutes are displayed using two 7 segment LED displays.

## Implementation  Details

The hour hand is moved by the servo motor using two gears so that the hand can be supported by a 3D printed bearing and relieve some weight from the motor. You can either use same sized gears for 180 degree movement or make a custom ratio like 1:2 to achieve 360 degrees.
For hour numbers, you can use anything you like, custom printed shapes, familly photos, wall art, light bulbs,...
I am using an addressable RGB LED strip in a 3D printed 7 segment display because it only requires one pin for communication, which simplifies the schematic and allows for color change.

## Local time server

Using internet NTP server is accurate, but only shows UTC time. Adjusting for daylight savings can be tricky in an embedded device like ESP8266, so I wrote a simple python script to broadcast local time on a custom UDP port. It can be deployed on any computer on local network, so the clock can synchronize when ever this computer is online. The server broadcasts the number of seconds passed in the current day, so you only need to run it one per day.
It's only dependency is Python3.

## Status

Not yet ready, but soon... If you wish to be notified when it is ready, let me know.


## Contact

email: ujagaga@gmail.com

