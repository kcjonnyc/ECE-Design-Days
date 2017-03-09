// LED control on arduino through push button

int Led = 13;         // define LED pin
int buttonpin = 10;   // define Button pin
int pressed;            

void setup ()
{
  pinMode (Led, OUTPUT);      // define LED as output
  pinMode (buttonpin, INPUT); // define the button as input
}

void loop ()
{
  val = digitalRead (buttonpin); // get digital reading from push button / push button pin
  if (val == HIGH) {  // when the button is pressed, LED turns on
    digitalWrite (Led, HIGH);
  }
  else {
    digitalWrite (Led, LOW); // else LED turns off
  }
}
