#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
// buzzer connected to pin 9
// relay on pin 10

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const char code[] = {'5','2','8','3'};

int index = 0;
bool solved = true;

void setup() {
  pinMode(9,OUTPUT); // solenoid output

  Serial.begin(9600);
}

long lastpressed = 0;
bool needsreset = false;

void loop() {
  bool pressed = false;

  char key = keypad.getKey();
  
  if (key) {
    if (code[index] != key) {
      solved = false;
    }
    pressed = true;
    Serial.print(key);
    Serial.println(" pressed");
    tone(9,600 + index*30,100);
    while (!digitalRead(A0)) {}
  }
  
  if (pressed) {
    needsreset = true;
    lastpressed = millis();
    delay(200);
    index++;
    if (index == 12) {
      needsreset = false;
      if (solved) {
        digitalWrite(10,HIGH);
        Serial.println("Solved!");
        tone(9,400,200);
        delay(100);
        tone(9,600,200);
        delay(100);
        tone(9,800,400);
        delay(1000);
        digitalWrite(10,LOW);
   //     while (1) {};
      } else {
        Serial.println("Nope!");
        tone(9,300,500);
      }
      index = 0;
      solved = true;
    }
  }

  if (lastpressed > millis()) lastpressed = millis();

  if (needsreset && millis() - lastpressed > 2000) {
    index = 0;
    solved = true;
    tone(9,600,100);
    delay(100);
    tone(9,600,100);
    delay(100);
    tone(9,300,100);
    Serial.println("Reset!");
    needsreset = false;
  }
}
