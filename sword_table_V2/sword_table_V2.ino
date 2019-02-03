#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6
#define rd  8
const int switchPin = 8;
const int switchPin2 = 9;
const int switchPin3 = 10;
const int switchPin4 = 11;
int x;
int y;
int sta;
int onOff;
int onOffButton;
// variables will change:
int buttonPin = 12;         // variable for reading the pushbutton status
int buttonState;

// Start of sound
int speakerPin = 13;
int p;
char notes[] = "gabygabypzCDpzCDabywabywzCDEzCDEbywFCDEqywFGDEqi        azbC"; // a space represents a rest
int length = sizeof(notes); // the number of notes
int beats[] = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 2,3,3,16,};
int tempo = 75;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'p', 'a', 'z', 'b', 'C', 'y', 'D', 'w', 'E', 'F', 'q', 'G', 'i' };
  // c=C4, C = C5. These values have been tuned.
  int tones[] = { 1898, 1690, 1500, 1420, 1265, 1194, 1126, 1063, 1001, 947, 893, 843, 795, 749, 710, 668, 630, 594 };
   
  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

// End of sound
void setup() {
  onOff = 1;
  onOffButton = 1;
  pinMode(buttonPin, INPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(rd, INPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
}


void loop() {
  onOffButton = 1;
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if(onOffButton == 1){
    onOff = 1;
    Serial.println("ON");
    StepForwardDefault();
    resetEDPins();
    
    
  } else {
    Serial.println("OFF");
    }
  }
  digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
  if(digitalRead(switchPin) == 1 and digitalRead(switchPin2) == 1 and digitalRead(switchPin3) == 1 and digitalRead(switchPin4) == 1) {
    Serial.println("TRUE");
    if(onOff == 1) {
      p = 0;
      ReverseStepDefault();
    }
    
  }

}

//Default microstep mode function
void StepForwardDefault()
{
  onOffButton = 0;
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<2900; x++)  //Loop the forward stepping enough times for motion to be visible 1 is reset direction closing bolt 2900 is whoe slide do not go over
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  p = 0;
  while(p<1){
    music();
    p = p + 1;
  }
}

//Reverse default microstep mode function
void ReverseStepDefault()
{
  onOff = 0;
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<2900; x++)  //Loop the stepping enough times for motion to be visible 2 is the hero direction openeing bolt 2900 is the whole slide do not go over
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  p = 0;
  // Start of sound
  while(p<1){
    music();
    p = p + 1;
  }
  // End of sound

}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

// Start of sound
void music() {
    pinMode(speakerPin, OUTPUT);
    for (int i = 48; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
  
  // pause between notes
    delay(tempo / 2); 
  }
  delay(100);

}
// End of sound
