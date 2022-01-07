# ESP8266 Semi-mechanical Clock

This is a wall clock based on ESP8266. It uses a 12V power supply. 
The time is synchronized from local network. Hours and minutes are displayed using servo motors that rotate only 180 degrees.

## Implementation  Details

The hour hand is moved by the servo motor using two gears so that the hand can be supported by a 3D printed bearing and relieve some weight from the motor. You can either use same sized gears for 180 degree movement or make a custom ratio like 1:2 to achieve 360 degrees as is here.
For hour numbers, you can use anything you like, custom printed shapes, familly photos, wall art, light bulbs,...
There is also a pendulum for purely aesthetic resons. It uses two coils and a neodimium magnet to run. It is controlled by the ESP8266.

## Local time server

Using internet NTP server is accurate, but only shows UTC time. Adjusting for daylight savings can be tricky in an embedded device like ESP8266, so I wrote a simple python script to broadcast local time on a custom UDP port. It can be deployed on any computer on local network, so the clock can synchronize when ever this computer is online. The server broadcasts the number of seconds passed in the current day, so you only need to run it one per day.
It's only dependency is Python3.

## Status

Not yet ready, but soon... If you wish to be notified when it is ready, let me know.


## Contact

email: ujagaga@gmail.com

