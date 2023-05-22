# Prepark
The Prepark App Prototype is a GitHub repository showcasing a proof-of-concept parking reservation system. The Prepark app prototype is an exciting step towards creating a seamless parking reservation solution that aims to transform the way people reserve parking spaces.

## Main Equipment
1. ESP32
2. Ultrasonic Module HC-SR04
3. 12V Gear motor
4. IBT-2 Motor drive
5. 220V AC to 12V DC 
6. stepdown 12V to 6V 

## In folder "main"
The Prepark Arduino code controls a parking system prototype using a motor and a sonar sensor. When the user initiates the unlock command in the accompanying app, the code activates the motor to unlock the parking place. It then measures the distance using the sonar sensor to determine if a car is passing by. If the car passes within the specified range, the code locks the parking place again, simulating a normal parking scenario. This code demonstrates the basic functionality of the Prepark system, providing a foundation for further enhancements and integrations.
