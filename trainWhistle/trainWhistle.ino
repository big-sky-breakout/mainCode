const byte limitSwitchPin = 6;
const int reedSwitch = 4;
const int relayF1 = 8;
const int relayF2 = 9;
//Use constants for the relay pins in case you need to change these later
const int relay1 = 2;   //Arduino pin that triggers relay #1
const int relay2 = 3;   //Arduino pin that triggers relay #2
bool reset = false;
bool pushed = false;
int limitSwitchState,reedSwitchState;
void setup() {
  //Set pinMode to OUTPUT for the two relay pins
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relayF1, OUTPUT);
  pinMode(relayF2, OUTPUT);
  pinMode (limitSwitchPin, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(reedSwitch, INPUT);
  digitalWrite(relayF1, HIGH);
  digitalWrite(relayF2, HIGH);
}


void extendActuator() {

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, LOW);
}

void retractActuator() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, HIGH);
}

void stopActuator() {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
}

void loop() {
  reedSwitchState = digitalRead(reedSwitch);
  limitSwitchState = digitalRead(limitSwitchPin);
  // Check to see if all limit switches are pressed
  if (limitSwitchState == LOW and reedSwitchState == HIGH)
  {
    Serial.println("Both");
    digitalWrite(relayF1, HIGH);
    digitalWrite(relayF2, LOW);
    if (not pushed) {
      reset = false;
      extendActuator();
      delay(1000);
      stopActuator();
      pushed = true;
    }
  }
  else if (limitSwitchState == LOW) {
    Serial.println("Limit");
    digitalWrite(relayF1, LOW);
    digitalWrite(relayF2, HIGH);
    if (not pushed) {
      reset = false;
      extendActuator();
      delay(1000);
      stopActuator();
      pushed = true;
    }
  }
  else {
    Serial.println("None");
    digitalWrite(relayF1, LOW);
    digitalWrite(relayF2, LOW);
    if (not reset) {
      reset = true;
      retractActuator();
      delay(1000);
      stopActuator();
      pushed = false;
    }

  }
  delay(500);

}

