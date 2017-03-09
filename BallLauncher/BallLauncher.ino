  // Arduino Ball Launcher
  // Made by Ben Chapman-Kish, Andrew Seto, Jonathan Chan, and Allison Chow
  // For ECE Design Days (2017)
  
  // Motor A is right, motor B is left

  // definte pins used
  #define A_DIR_PIN 12
  #define B_DIR_PIN 13
  
  #define A_SPD_PIN 3
  #define B_SPD_PIN 11
  
  #define A_BRK_PIN 9
  #define B_BRK_PIN 8
  
  #define A_CUR_PIN 0
  #define B_CUR_PIN 1
  
  #define A_IR_PIN A2
  #define B_IR_PIN A3
  
  // ir refers to an infared sensor
  #define IR_THRES 300
  #define TIME_WAIT 1000
  
  int speed = 255;
  
  double desired_rpm = 5000;
  double rpm;
  
  double avgTime = 0;
  int IR_hist[5];
  
  #define MIN(a,b) (a < b ? a : b)
  #define MAX(a,b) (a > b ? a : b)
  
  int spins;
  unsigned long lastTime;
  
  
  // For ISR
  void pciSetup(byte pin)
  {
      *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
      PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
      PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
  }
  
  // Initialization
  void setup() {
  
    Serial.begin(9600); // serial initialization
    while (! Serial);
    
    pinMode(A_DIR_PIN, OUTPUT); // pin setup
    pinMode(A_BRK_PIN, OUTPUT);
  
    pinMode(B_DIR_PIN, OUTPUT);
    pinMode(B_BRK_PIN, OUTPUT);
  
    lastTime = millis();
    spins = 0;
   
    pciSetup(A_IR_PIN);
    
  }
  
  void loop(){

    // start motors up
    digitalWrite(A_DIR_PIN, HIGH);
    digitalWrite(A_BRK_PIN, LOW);
    analogWrite(A_SPD_PIN, speed);
  
    digitalWrite(B_DIR_PIN, HIGH);
    digitalWrite(B_BRK_PIN, LOW);
    analogWrite(B_SPD_PIN, speed);
  
    // obtain electric current readings
    int current1 = analogRead(A_CUR_PIN);
    int current2 = analogRead(B_CUR_PIN);

    // obtain infared sensor readings
    int ir1 = analogRead(A_IR_PIN);
    int ir2 = analogRead(B_IR_PIN);
  
  //  Serial.print("IR A: ");
  //  Serial.println(ir1);
  
  //  Serial.print("IR B: ");
  //  Serial.println(ir2);
    
  //  int c1 = map(current1, 0, 676, 0, 2000);
  //  int c2 = map(current2, 0, 676, 0, 2000);
   
  //  Serial.print("current1 = ");
  //  Serial.print(c1);
  //  Serial.print(" mA \n");
  
  //  Serial.print("current2 = ");
  //  Serial.print(c2);
  //  Serial.print(" mA \n");

    
    unsigned long curTime = millis();
    unsigned long elapsed = curTime - lastTime;

    // after a period of time has passed, we calculate the RPM
    // of the motors
    if (elapsed > TIME_WAIT) {
      lastTime = curTime;
      // add time is called to add elapsed time to history to obtain new avgTime
      addTime(elapsed); 
      rpm = 60 * spins / (avgTime / 1000);
        
      spins = 0; // number of spins is reset

      // based on our calculated rpm and desired rpm
      // adjust the speed of the motor
      if (abs(rpm - desired_rpm) > 1000) {
        speed *= desired_rpm / rpm;
      }
      else if (rpm > desired_rpm && speed > 0) {
        speed -= 1;
      }
      else if (rpm < desired_rpm && speed < 255) {
        speed += 1;
      }
  
      speed = MIN(MAX(0, speed), 255);
    }
  
    // obtain desired rpm from serial monitor
    if (Serial.available() > 0) {
      desired_rpm = Serial.parseInt();
    }

    // write the new speed to arduino
    analogWrite(A_SPD_PIN, speed);
    analogWrite(B_SPD_PIN, speed);

    // display details on serial monitor
    Serial.print("Speed: ");
    Serial.print(speed);
    
    Serial.print("  RPM: ");
    Serial.print(rpm);
    Serial.print("  Desired: ");
    Serial.println(desired_rpm);
    
  }
  
  void addTime(unsigned long time) {
    // shift array and add time
    for (int i=0; i<4; i++) {
      IR_hist[i+1] = IR_hist[i];
    }
    IR_hist[0] = time;

    // calculate average time over last 5 calls
    long sum = 0;
    for (int i=0; i<5; i++) {
      sum += IR_hist[i];
    }
    avgTime = (double)sum / 5;
  }
  
  ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
  {
       if(analogRead(A_IR_PIN) < 2){
          spins++;
       }
  }

