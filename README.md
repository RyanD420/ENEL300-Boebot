# ENEL300 Boebot Last updated Mar 28, 2018

This is the main code used for my ENEL 300 project (2nd year Electrical Engineering design class) in which the task is to navigate around a course using an Arduino Uno, two servo motors and 3 infrared sensors. 
This couldn't have been done without the help of my team members Devon, Akhil, and Levin!

The code requires the 'StopWatch' library that can be found here: http://playground.arduino.cc/Code/StopWatchClass
Thanks to robtillaart.

------------------------------------------------------------------------------------------------------------------------------------------

### Required Materials
 -  Arduino UNO
 -  6 Resistors (Values can be changed based on needs)
 -  Arduino UNO Proto Shield
 -  Wires
 -  Computer with Arduino IDE
 -  2 Servo Motors
 -  Battery holder and batteries
 -  Chassis or Frame

------------------------------------------------------------------------------------------------------------------------------------------
### Boebot Hardware and Construction
1. Attach Arduino UNO to Protoshield
2. Construct your Chassis and attach battery pack
3. Attach servo motors on either side of the chassis
4. Attach Arduino UNO unit to chassis
5. Connect servo motor connectors to the Proto Shield digital pins
6. Wire the Transistor and IR LED as listed below
7. Repeat step 6 for the three LED's and Transistors

#### Note about resistances
The three IR LED's required various resistances based on the use of each sensor. The higher the resistance the lower the current and therefor the lower the range, whereas the lower the resistance the higher the current and range. From our findings the resistors we found best suited our needs are 6.8k Ohms (Left), 22k Ohms (Middle), and 1.5k Ohms (Right). 

#### Note about wiring LED's
Diagram for Transistors and LED terminals:
https://imgur.com/a/pPTCK

Schematic for the LED's
https://imgur.com/a/ziqwp

Digital Inputs and resistors can be adjusted to whatever inputs you'd like, just remember to change the pins on lines 16-20 in Boebot.ino

#### Note about wiring Servo motors
Schematic for the Servo motors:
https://imgur.com/a/UsnZz

The 12 and 11 in the diagram above represent the pins we attached the motors to. Remember to change in your code on lines 24 and 25 of Boebot.ino!

------------------------------------------------------------------------------------------------------------------------------------------

Image of the course can be found from the URL:
https://imgur.com/a/BgmR7

------------------------------------------------------------------------------------------------------------------------------------------
Videos of the BoeBot:
----------------------

---------------------------------


https://youtu.be/o4FN1WEVlwQ


----------------------------------
https://youtu.be/o4FN1WEVlwQ


Image and video soon!
------------------------------------------------------------------------------------------------------------------------------------------
