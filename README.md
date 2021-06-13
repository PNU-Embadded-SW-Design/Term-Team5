# Term-Team5
김준우, 이예경, 아산노브 다미르
# Embedded System Software Design
## Term Group Project Team 5
## Smart Sanitizing and Temperature Measurement system 
### Project Description
* The System was used to work by the following scenario:
1. Temperature Sensors constantly checking the temperature in the room.
2. Once, person pressed the button on the board, temperature sensor will check the normal conditions to go for the next step.
3. Also, LCD will show the temperature and the status of the situation.
4. Then, in case the person has normal body temperature it comes to the timer, which will wait for some time to detect the motion near the sanitizer.
5. When, the motion sensor detects person(motion),  it gaves command to servo motor to press the sanitizer. 
6. Lastly, after successfully finished sanitizing step, another servo motor will open the door.
7. After some time, the door will be closed, and system will go back to the initial states. 
* This is the scenario for the system. However, in case when person will have high temperature, system will notify person through LCD that he/she has a fever, and can not access to the room or building. 
## Goals
* The main goal of the project was to create a smart system to facilitate life during the COVID situation in the world. Due to the serious danger to the world, smart system would be really good solution to prevent spreading of COVID. 
* Also, it was a good opportunity to understand details of the embedded system, and get knew experience on working with board.
## Board
* STM32F107
## Program environment
* IAR Embedded Workbench
## Sensors and Controllers
* Liquid-Crystal Display
* PIR motion sensor
* Servo Motor
* LM35dz body temperature sensor
## Functions
* Checking body temperature
* Open and Close the door functions 
* Sanitizing function
* Data presenting function (LCD)
* Motion Detecting function
