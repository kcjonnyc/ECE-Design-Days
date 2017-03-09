// Servo control to drive robot

#include <Servo.h>
#include <string.h>

Servo myservo;  // create servo object to control a servo
Servo myservo1;

int pos = 90;    // variable to store the servo position
int pos1;
String posA = "";
String posB = "";
String posC = "";
String cmd;
int count = 0;

void setup() {

  Serial.begin(9600); // serial initialization
  while (!Serial);
  
  myservo.attach(9);  // attaches a servo on pin 9 to the servo object
  myservo1.attach(10);
}

void loop() {

  // pos is 0 to drive back, 180 to drive forward, 90 to stop movement
  // write position to first servo
  myservo.write(pos);
  pos1 = abs(pos - 180);
  // the second servo is pos-180 as it is flipped in relation to first servo
  myservo1.write(pos1);

  if (Serial.available() > 0) {
    pos = Serial.parseInt(); // obtain the position
    /*
    Code to take in 3 different readings and parse the string to
    control 3 different degrees of movement on the robot
    cmd = Serial.readString();
      do {
        posA += cmd[count];
        count++;
      } while (cmd[count] != ' ');
      count++;

      do {
        posB += cmd[count];
        count++;
      } while (cmd[count] != ' ');
      count++;
      
      do {
        posC += cmd[count];
        count++;
      } while (cmd[count] != ' ');
      */
  }

  Serial.print("POS: ");
  Serial.println(pos);
  
  /*
  Serial.print("POSA: ");
  Serial.print(posA);
  Serial.print("POSB: ");
  Serial.print(posB);
  Serial.print("POSC: ");
  Serial.println(posC); */

}

