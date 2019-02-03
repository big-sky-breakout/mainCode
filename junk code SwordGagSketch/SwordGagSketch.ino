int sword1Pin = 3;
int sword2Pin = 4;
int sword3Pin = 5;
int sword4Pin = 6;
int magLockRelayPin = 7;
int lightRelayPin = 8;
int resetPin = 9;
int doorSensorPin = 10;

int doorIsClosedState = HIGH;
int resetPinPressedLevel = HIGH;

int magLockOnPinState = HIGH;
int magLockOffPinState = !magLockOnPinState;

int lightOnPinState = HIGH;
int lightOffPinState = !lightOnPinState;

int activeState = 1;
int doorUnlockedState = 2;
int lightOnState = 3;
int currentState = activeState;

void setup() {
  //set up the pin modes for each pin
  pinMode(sword1Pin, INPUT);
  pinMode(sword2Pin, INPUT);
  pinMode(sword3Pin, INPUT);
  pinMode(sword4Pin, INPUT);
  pinMode(resetPin, INPUT);
  pinMode(doorSensorPin, INPUT);

  pinMode(magLockRelayPin, OUTPUT);
  pinMode(lightRelayPin, OUTPUT);

  //set up the starting outputs for the output pins
  digitalWrite(magLockRelayPin, magLockOnPinState);
  digitalWrite(lightRelayPin, lightOffPinState);
 //we start our state in ActiveState
 currentState = activeState;
}

void loop() {
  if(currentState == activeState){
    digitalWrite(magLockRelayPin, magLockOnPinState);
    digitalWrite(lightRelayPin, lightOffPinState);
    if(allSwordsAreIn()){
      currentState == doorUnlockedState;
    }
  }
  //in the doorUnlockedState, we have to check to see if the door is closed,
  //if so, show the lights
  //if the reset pin is turned on, go back to activestate
  else if(currentState == doorUnlockedState){
    digitalWrite(magLockRelayPin, magLockOffPinState);
    digitalWrite(lightRelayPin, lightOffPinState);

    if(isResetButtonPressed()){
      currentState = activeState;
    }
    else if(isDoorClosed()){
      currentState = lightOnState;
    }
  }


  //light on state: turn the light on,
  //look for reset pin or door opens
  else if (currentState == lightOnState){
    digitalWrite(lightRelayPin, lightOnPinState);
    digitalWrite(magLockRelayPin, magLockOffPinState);

    if(isResetButtonPressed()){
      currentState = activeState;
    }
    else if(!isDoorClosed()){
      currentState = doorUnlockedState;
    } 
  }
  else{
    //if we didn't go into any of these states, something went horribly wrong,
    //check the code for errors
    Serial.println("ERROR: program enter illegal state, check for errors");
    currentState = activeState;
  }
}


//this function checks all the sword IR pins, and only returns true
//if all of the sword IR sensors are blocked
bool allSwordsAreIn(){
  bool areAllSwordIrSensorsBlocked = 
    (digitalRead(sword1Pin) == LOW) &&
    (digitalRead(sword2Pin) == LOW) &&
    (digitalRead(sword3Pin) == LOW) &&
    (digitalRead(sword4Pin) == LOW);
    
    return areAllSwordIrSensorsBlocked;
}

bool isResetButtonPressed(){
  return digitalRead(resetPin) == resetPinPressedLevel;
}

bool isDoorClosed(){
  return digitalRead(doorSensorPin) == doorIsClosedState;
}

