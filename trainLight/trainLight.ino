const int red=10;
const int yellow=9;
const int green=8;

bool going = false;
void setup() {
  // Setup leds for output mode
  pinMode(red, OUTPUT);
  pinMode(green, INPUT);
  pinMode(yellow, OUTPUT);
}

void blinking(int led, int times, int seconds){
  if(led == 8){
    pinMode(yellow, INPUT);
    pinMode(green, OUTPUT);
    pinMode(red, INPUT);  
  }
  else if(led == 9){
    pinMode(green, INPUT);
    pinMode(yellow, OUTPUT);
    pinMode(red, INPUT); 
  }
  else{
    pinMode(green, INPUT);
    pinMode(yellow, INPUT);
    pinMode(red, OUTPUT); 
  }
  int count = 0;
  while(count<times){
    digitalWrite(led, HIGH);   
    delay(seconds*1000);                    
    digitalWrite(led, LOW);
    delay(seconds*1000);
    count += 1;   
  }
}

// Speed can't be below 1 
void loop() {
  if(!going){ // If we aren't going
    going = true; // Set variable to say that we are and blinking the leds
    blinking(yellow, 7, 1);
    blinking(red, 3, 1); // The first thing is the led color, the second one is how many times, and the third one is the delay between the blinks
    blinking(green, 1, 1);
    going = false; // stop the loop for a second
  } 
}



