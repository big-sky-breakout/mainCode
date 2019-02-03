#define IN1 0  // analog...
#define IN2 1
#define IN3 2
#define IN4 3
#define THREASHOLD 512
#define REEDSW 5  // digital...
#define LIGHTS 6
#define LOCK 7



boolean activated = false;
boolean opened = false;

void setup() {
  pinMode(REEDSW, INPUT);
  pinMode(LOCK, OUTPUT);
  pinMode(LIGHTS, OUTPUT);
  digitalWrite(LOCK, HIGH);
  Serial.begin(115200);
}

int ain1, ain2, ain3, ain4;

void loop() {
  ain1 = analogRead(IN1);
  ain2 = analogRead(IN2);
  ain3 = analogRead(IN3);
  ain4 = analogRead(IN4);

//  Serial.print(ain1);   // for debugging
//  Serial.print(' ');
//  Serial.print(ain2);
//  Serial.print(' ');
//  Serial.print(ain3);
//  Serial.print(' ');
//  Serial.println(ain4);
  
  if (ain1 < THREASHOLD &&
      ain2 < THREASHOLD &&
      ain3 < THREASHOLD &&
      ain4 < THREASHOLD) {
    activated = true;
    digitalWrite(LOCK, LOW);
  }

  if (activated && digitalRead(REEDSW)) {
    opened = true;
  }

  if (opened && !digitalRead(REEDSW)) {
    digitalWrite(LIGHTS, HIGH);
  } else {
    digitalWrite(LIGHTS, LOW);
  } 
}
