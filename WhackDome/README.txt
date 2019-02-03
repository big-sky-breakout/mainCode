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
  
  