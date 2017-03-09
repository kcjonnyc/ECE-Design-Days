// MOTOR control using arduino motor shield
// Single motor with controllable speed through serial monitor

#define A_DIR_PIN 12  // define pins used
#define A_SPD_PIN 3

int speed = 255;      // initial speed

void setup() {

  Serial.begin(9600);  // serial monitor initialization
  while (! Serial);
  
  pinMode(A_DIR_PIN, OUTPUT);
}

void loop(){

  digitalWrite(A_DIR_PIN, HIGH); // set direction and speed
  analogWrite(A_SPD_PIN, speed);

  if (Serial.available() > 0) {  // command entered through serial
    speed = Serial.parseInt();   // obtain the speed
  }

  analogWrite(A_SPD_PIN, speed); // change motor speed

  Serial.print("Speed: ");       // output to monitor
  Serial.println(speed);
  
}

