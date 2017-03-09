# ECE-Design-Days
Our team used hardware and software to solve different challenges issued by the University of Waterloo for their ECE Desgin Days event.
We used an arduino and arduino motor shield to program a ball launcher, robot (servos), motor, and led.

BallLauncher
The hardware for the ball launcher consisted of two motors with wheels attached. The wheels are marked with a while line so that
rotations could be tracked using IR sensors. Using this, we were able to specify a speed and have the motors adjust themselves based
on observed RPM readings.

Robot(Servos)
A robot was constructed using 5 different servos allowing for various degrees of movement. The ball launcher was mounted on top so we
could control the position the ball would launch at. 

We were able to control both the ball launcher and robot through a website by writing to the serial port of the arduino.
