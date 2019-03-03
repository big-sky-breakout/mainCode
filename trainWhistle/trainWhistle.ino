
const int switchPin = 4;
// variables will change:

int debounce = 0;
// End of sound
void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600); // Open Serial connection for debugging
}


void loop() {
//  buttonState = digitalRead(buttonPin);
//  if (buttonState == HIGH) {
//    Serial.println("ON");    
//    
//  } else {
//    Serial.println("OFF");
//    }
//  }
  if(digitalRead(switchPin) != debounce) {
    Serial.println("TRUE");
    debounce = 1;
  }
  else{
    debounce = 0;
    Serial.println("FALSE");
  }

}

