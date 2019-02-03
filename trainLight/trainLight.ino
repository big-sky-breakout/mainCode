const int red=10;
const int yellow=9;
const int green=8;

bool going = false;
void setup() {
  // Setup leds for output mode
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
}

void blinking(int led, int times, int seconds){
  int count = 0;
  while(count<times){
    digitalWrite(led, HIGH);   
    delay(seconds*1000);                    
    digitalWrite(led, LOW);
    delay(seconds*1000);
    count += 1;   
  }
}

void loop() {
  if(!going){ // If we aren't going
    going = true; // Set variable to say that we are and blink the leds
    blinking(red, 5, 1); // The first thing is the led color, the second one is how many times, and the third one is the delay between the blinks
    blinking(green, 5, 1);
    blinking(yellow, 5, 1);
    going = false; // stop the loop for a second
  }
}



