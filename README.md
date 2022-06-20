# Arduino-Social-Distancing-Robot
### Building Instructions
You will need the following parts:

1 Arduino (Uno or Mega works best for this project)

1 Buzzer (I used a buzzer but feel free to use whichever type of buzzer you want)

1 L298N DC motor controller 

1 SG90 Servo 180 degree

1 HC-SR04 Ultrasonic Distance Sensor

1 Tiny breadboard

### Once you have gathered these components we are ready to begin!
Navigate to the Pictures file in the repository. There is a schematic inside for the circuit.
Here are the connections:

Servo - Pin 11

L298N - ENB => Pin 5
		
	IN4 => Pin 6

	IN3 => Pin 7
	
	IN2 => Pin 8
	
	IN1 => Pin 9
	
	ENA => Pin 10

Trigger - A0

Echo - A1

VCC - 5V

buzzer - Pin 12 

You can open the .ino file in the editor then verify and upload the code to your Arduino. 
If you have hooked everything up correctly you should have a fully functioning Social Distancing Robot.



#### Stay safe out there!

