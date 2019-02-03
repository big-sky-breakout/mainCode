
const byte code[] = {4,4,1,2,2,3,1,3,2};

int index = 0;
bool solved = true;

void setup() {
  pinMode(9,OUTPUT); // solenoid output
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);

  Serial.begin(9600);
}

long lastpressed = 0;
bool needsreset = false;

void loop() {
  bool pressed = false;
  if (!digitalRead(A0)) {
    if (code[index] != 1) {
      solved = false;
    }
    pressed = true;
    Serial.println("Button 1 pressed");
    tone(6,500 + index*30,100);
    while (!digitalRead(A0)) {}
  } else if (!digitalRead(A1)) {
    if (code[index] != 2) {
      solved = false;
    }
    pressed = true;
    Serial.println("Button 2 pressed");
    tone(6,500 + index*30,100);
    while (!digitalRead(A1)) {}
  } else if (!digitalRead(A2)) {
    if (code[index] != 3) {
      solved = false;
    }
    pressed = true;
    Serial.println("Button 3 pressed");
    tone(6,500 + index*30,100);
    while (!digitalRead(A2)) {}
  } else if (!digitalRead(A3)) {
    if (code[index] != 4) {
      solved = false;
    }
    pressed = true;
    Serial.println("Button 4 pressed");
    tone(6,500 + index*30,100);
    while (!digitalRead(A3)) {}
  }
  
  if (pressed) {
    needsreset = true;
    lastpressed = millis();
    delay(400);
    index++;
    if (index == 9) {
      needsreset = false;
      if (solved) {
        digitalWrite(9,HIGH);
        Serial.println("Solved!");
        tone(6,400,200);
        delay(100);
        tone(6,600,200);
        delay(100);
        tone(6,800,400);
        delay(3000);
        digitalWrite(9,LOW);
   //     while (1) {};
      } else {
        Serial.println("Nope!");
        tone(6,300,500);
      }
      index = 0;
      solved = true;
    }
  }

  if (lastpressed > millis()) lastpressed = millis();

  if (needsreset && millis() - lastpressed > 2500) {
    index = 0;
    solved = true;
    tone(6,600,100);
    delay(100);
    tone(6,600,100);
    delay(100);
    tone(6,300,100);
    Serial.println("Reset!");
    needsreset = false;
  }
}
