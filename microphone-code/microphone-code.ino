
const byte code[] = {1,1,2,1,1,2};

int index = 0;
bool solved = true;

void setup() {
  pinMode(9,OUTPUT); // solenoid output
  pinMode(10,OUTPUT); // candle 1 output
  pinMode(11,OUTPUT); // candle 2 output
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);

  Serial.begin(9600);
}

long lastpressed = 0;
bool needsreset = false;
long flickertimer = 0;

void loop() {
  bool pressed = false;
  //Serial.print(analogRead(0));Serial.print(" ");Serial.println(analogRead(1));
  
  if (analogRead(0) < 20) {
    if (code[index] != 1) {
      solved = false;
    }
    pressed = true;
    Serial.println("1");
    digitalWrite(10,LOW);
    
    while (analogRead(0) < 70) {}
    delay(100);
    analogWrite(10,100);
  } else if (analogRead(1) < 20) {
    if (code[index] != 2) {
      solved = false;
    }
    pressed = true;
    Serial.println("2");
    digitalWrite(11,LOW);
   
    while (analogRead(1) < 70) {}
    delay(100);
    analogWrite(11,100);
  }
  
  if (pressed) {
    needsreset = true;
    lastpressed = millis();
    delay(200);
    index++;
    if (index == 6) {
      needsreset = false;
      if (solved) {
        Serial.println("Solved!");
        digitalWrite(9,HIGH);
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
        delay(60000);
        digitalWrite(9,LOW);
      } else {
        Serial.println("Nope!");
        digitalWrite(10,HIGH);
        digitalWrite(11,HIGH);
        delay(1000);
      }
      index = 0;
      solved = true;
    }
  }

  if (lastpressed > millis()) lastpressed = millis();

  if (needsreset && millis() - lastpressed > 1000) {
    index = 0;
    solved = true;

    Serial.println("Reset!");
    needsreset = false;
  }

  if (millis() > flickertimer) {
    analogWrite(10,random(100,200));
    analogWrite(11,random(100,200));
    flickertimer = millis() + random(20,100);
  }
}
