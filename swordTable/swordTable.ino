
// Declare pin functions on Redboard
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6
#define rd  8
#define A0  9
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
//#define IN1 0  
//#define IN2 1  
//#define IN3 2
//#define IN4 3  

//Declare variables for functions

char user_input;
int x;
int y;
int state;
int resetPin = 9;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(rd, INPUT);
  pinMode(resetPin, INPUT);
  pinMode(A0, INPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. Turn at default microstep mode.");
  Serial.println("2. Reverse direction at default microstep mode.");
  Serial.println();
}


//int ain1, ain2, ain3, ain0;


 //Main loop
void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(sensorValue);
//  ain1 = analogRead(IN1);
//  ain2 = analogRead(IN2);
//  ain3 = analogRead(IN3);
//  ain0 = analogRead(IN4);
  while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
      if (user_input =='1')
      {
         StepForwardDefault();
      }
      
      if (user_input =='2')
      {
        ReverseStepDefault();
      }
  }
  if (rd == HIGH) {
      //&& A1 == HIGH && A2 == HIGH && A3 == HIGH){
        ReverseStepDefault();//parenthesis after A0 high to be removed
      } 
      
  if (resetPin = LOW){
        StepForwardDefault();
      } //else {
        //Serial.println("Invalid option entered.");
      //}
      resetEDPins();
}


//Default microstep mode function
void StepForwardDefault()
{
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<2900; x++)  //Loop the forward stepping enough times for motion to be visible 1 is reset direction closing bolt 2900 is whoe slide do not go over
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}


//Reverse default microstep mode function
void ReverseStepDefault()
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<2900; x++)  //Loop the stepping enough times for motion to be visible 2 is the hero direction openeing bolt 2900 is the whole slide do not go over
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
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



  






