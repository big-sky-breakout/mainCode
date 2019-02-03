/*
 6/29/2012
  N.Poole
  SparkFun Electronics
  
  This is the code used in our May 25, 2012 "Whack-Dome" product demonstration. It tracks 16 of our large dome buttons
  and controls the 16 LEDs therein to play a "Whack-A-Mole" style reaction time game. The score increments with each 
  successful press and the pace of the game increases. When the wrong button is pressed or you don't react in time,
  the game triggers a car horn. I got lazy and used an Arduino Mega to avoid multiplexing the buttons.
  
  You can see the demo here: http://www.sparkfun.com/news/874
  
  The score incrementation engine has some bugs that need to be worked out, also, you may want to move the *beep* time 
  to the beginning of a scoring cycle instead of the end.
  
  This code uses AlphaNumeric_Driver-v13 to drive our Serial Alphanumeric Display Driver 
  (both can be found at: http://www.sparkfun.com/products/10103)
  
  
  Hardware: 
  Pins 50-53 : Serial Display Driver (Pin Defs Below)
  Pins 22-37 : Dome Button LEDs
  Pins 38-49&2-5: Dome Button Switches to Ground
  Pin 6 : Relay to Car Horn
  
  Go build one, what are you waiting for?
 
  Enjoy!
  
  */


//#define FLIPDISPLAY  // Comment this out if you want the characters flipped 180 degrees

//First we need to setup the Alphanumeric mess:

#include <AlphaNumeric_Driver.h> 
#define NUMBER_OF_DISPLAYS 4  

// --------- Pin Definitions -----------
int SDIpin = 51;
int CLKpin = 52;
int LEpin = 53;
int OEpin = 50;
// -------------------------------------

alphaNumeric myDisplay(SDIpin, CLKpin, LEpin, OEpin, NUMBER_OF_DISPLAYS);  // Create an instance of Alpha Numeric Displays

int gameDelay = 1500; //This is the millisecond delay between "moles" at the start of the game

boolean inPlay = 1; //This is a boolean flag that we'll use to determine where in the scoring cycle we are

void setup()
{
  //Serial.begin(9600); //Pour a bowl of Serial... for debugging
  //LED SETUP - Here's all of the pins we'll need to use. First we set them as outputs, then we make sure they're low.
  pinMode(22, OUTPUT); pinMode(23, OUTPUT); pinMode(24, OUTPUT); pinMode(25, OUTPUT);
  pinMode(26, OUTPUT); pinMode(27, OUTPUT); pinMode(28, OUTPUT); pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); pinMode(31, OUTPUT); pinMode(32, OUTPUT); pinMode(33, OUTPUT);
  pinMode(34, OUTPUT); pinMode(35, OUTPUT); pinMode(36, OUTPUT); pinMode(37, OUTPUT); pinMode(6, OUTPUT); digitalWrite(6, LOW); 
  
  digitalWrite(22, LOW); digitalWrite(23, LOW); digitalWrite(24, LOW); digitalWrite(25, LOW); 
  digitalWrite(26, LOW); digitalWrite(27, LOW); digitalWrite(28, LOW); digitalWrite(29, LOW); 
  digitalWrite(30, LOW); digitalWrite(31, LOW); digitalWrite(32, LOW); digitalWrite(33, LOW); 
  digitalWrite(34, LOW); digitalWrite(35, LOW); digitalWrite(36, LOW); digitalWrite(37, LOW); 
  
  //BUTTON SETUP - Here's all of the pins we'll need for the buttons. First set them as inputs, then set the internal pull-ups.
  //Yes, I could have use a FOR loop for a lot of this.
  pinMode(38, INPUT); pinMode(39, INPUT); pinMode(40, INPUT); pinMode(41, INPUT); 
  pinMode(42, INPUT); pinMode(43, INPUT); pinMode(44, INPUT); pinMode(45, INPUT); 
  pinMode(46, INPUT); pinMode(47, INPUT); pinMode(48, INPUT); pinMode(49, INPUT); 
  pinMode(2, INPUT); pinMode(3, INPUT); pinMode(4, INPUT); pinMode(5, INPUT); 

  digitalWrite(38, HIGH); digitalWrite(39, HIGH); digitalWrite(40, HIGH); digitalWrite(41, HIGH); 
  digitalWrite(42, HIGH); digitalWrite(43, HIGH); digitalWrite(44, HIGH); digitalWrite(45, HIGH); 
  digitalWrite(46, HIGH); digitalWrite(47, HIGH); digitalWrite(48, HIGH); digitalWrite(49, HIGH); 
  digitalWrite(2, HIGH); digitalWrite(3, HIGH); digitalWrite(4, HIGH); digitalWrite(5, HIGH);     
}

//Let's get ready to rumble.

void loop()
{

  //Tell the stupid human what to do:
  myDisplay.scroll("PRESS ANY BUTTON TO PLAY", 100);
  while(anyKey()==0){} //Wait for an input, the anyKey function throws TRUE when it gets a press
  
  gameDelay = 1000; //Another chance to play with the game delay
  inPlay = 1; //Reset the inPlay flag from last game
  playagame(); //Whack some moles
  
}

//This function (anyKey) just looks for a button press on any of the 16 buttons and throws a flag.
//Similar functions are usueful in a lot of different applications.

boolean anyKey(){

  boolean press = 0;
  
  if(
  digitalRead(38)==LOW || digitalRead(39)==LOW || digitalRead(40)==LOW || digitalRead(41)==LOW || 
  digitalRead(42)==LOW || digitalRead(43)==LOW || digitalRead(44)==LOW || digitalRead(45)==LOW || 
  digitalRead(46)==LOW || digitalRead(47)==LOW || digitalRead(48)==LOW || digitalRead(49)==LOW || 
  digitalRead(2)==LOW || digitalRead(3)==LOW || digitalRead(4)==LOW || digitalRead(5)==LOW){
  press = 1; 
  }
  
  return press;
  
}

//It's time to whack some moles, here comes the fun:

void playagame(){
String scorestr; //This is the string that we'll put the score into before we display it
int score = 0; //This is the "mathy" version of the score that we'll increment in code
int newLight; //This is the number of the LED that we're goign to light next
boolean hit = 1; //This is the flag that tells the scoring engine whether or not to give you the hor... umm, car horn.

randomSeed(analogRead(A0)); //Seed the pseudo-random engine with some true randomness.

delay(1000); //give everyone a second to chill

myDisplay.scroll("READY", 100); //Well? Are you?

delay(2000); //Two seconds of mind-bending suspense

myDisplay.clear(); //Clear the display
myDisplay.scroll("GO", 100); //GO! DO IT NOW!

while(inPlay == 1){ 

inPlay=0; //Assumed guilty until proven innocent 
newLight = random(22,38); //Pick a random light
//Serial.println(newLight); //Serial debug stuff
int newButtn = getButtn(newLight); //The getButtn function returns the button number corresponding to the LED that's lit.

digitalWrite(newLight, HIGH); //Light up the random light.

for(int t=0; t<gameDelay; t++){ //Okay, I said it was a millisecond value, but it's really a cycle count value. This is the amount of time you have. Go.
hit = digitalRead(newButtn); //Grab the button status
if(hit==0){inPlay=1;} //if you get a button press: proven innocent.
delay(1);} //take a breather
digitalWrite(newLight, LOW); //now that you've either slapped that mole or not, we need it to go back in it's hole
score=score+5; //give 'em a few points
gameDelay=gameDelay-5; //make the game faster
tone(10, 440, 250); //Play a beepy sound
scorestr = String(score); //Turn the mathy score into a stringy score
scorestr.trim(); //chop off the end
myDisplay.clear(); //clear the display
myDisplay.print(scorestr.charAt(0)); myDisplay.print(scorestr.charAt(1)); myDisplay.print(scorestr.charAt(2)); myDisplay.print(scorestr.charAt(3)); myDisplay.print(scorestr.charAt(4));
} //This is my attempt to correctly display a score that was tranformed from an integer... it doesn't work.

myDisplay.clear(); //So if you've made it this far in the code, you've lost. (Pro-Tip: You always lose eventually)
digitalWrite(6, HIGH); //HONK
delay(500); //STILL HONKING
digitalWrite(6, LOW); //Okay, if the powersupply hasn't locked-down or browned out your Arduino we can turn off the horn. (8 Amps?!?!)

  
  myDisplay.scroll("GOTCHA DUDE!!", 100); //Har Har Har
  delay(3000);
  myDisplay.scroll("YOUR SCORE", 100); //Here's your score (ish)
  delay(3000);
myDisplay.clear(); //Again with the not-so-good score display
myDisplay.print(scorestr.charAt(0)); myDisplay.print(scorestr.charAt(1)); myDisplay.print(scorestr.charAt(2)); myDisplay.print(scorestr.charAt(3)); myDisplay.print(scorestr.charAt(4));
  delay(2000); //Flash it on and off, like an Arcade machine.
  myDisplay.off(); //off?
  delay(500);
  myDisplay.on(); //on!
  delay(1000);
  myDisplay.off(); //off?
  delay(500);
  myDisplay.on(); //on! Isn't this fun?
  delay(1000);

while(anyKey()==0){} //Hang out here until the user presses a button.
  
}

//Here's the function that returns the corresponding switch pin for a given LED pin.
//It's just a massive switch-case

int getButtn(int newLight){ 

int Buttn; 
  
 switch (newLight) {
  
   case 22:
   Buttn = 38;
   break;
   case 23:
   Buttn = 39;   
   break;
   case 24:
   Buttn = 40;   
   break;
   case 25:
   Buttn = 41;   
   break;
   case 26:
   Buttn = 42;   
   break;
   case 27:
   Buttn = 43;   
   break;
   case 28:
   Buttn = 44;   
   break;
   case 29:
   Buttn = 45;   
   break;
   case 30:
   Buttn = 46;   
   break;
   case 31:
   Buttn = 47;   
   break;
   case 32:
   Buttn = 48;   
   break;
   case 33:
   Buttn = 49;   
   break;
   case 34:
   Buttn = 2;   
   break;
   case 35:
   Buttn = 3;   
   break;
   case 36:
   Buttn = 4;   
   break;
   case 37:
   Buttn = 5;   
   break;
 } 
  
  return Buttn; //Button, button, whose got the button?
  
}
