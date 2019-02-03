/**
   ----------------------------------------------------------------------------
   This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
   for further details and other examples.

   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

byte uuid_1[4] = {0x7A, 0x18, 0x95, 0x35};

int ttl = 0;
int timer = 1; // This number increments during the loop
int timercheck = 0; // If this = 1, then the time variable goes up
/**
   Initialize.
*/
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card

  // output led
  pinMode(7, OUTPUT);

}

void loop() {


  if (timer > 5000) {      //Check the timer
    digitalWrite(7, LOW);  // If it's time, shut off LED'S
    exit(0);               // Exit loop
  }
  if (ttl > 0) { // If RFID's are ready
    digitalWrite(7, HIGH); // Turn on LED's

    ttl--;
  } else {
    timercheck = 0; // Reset counting when they pull Alice off
    timer = 1; // Reset counting when they pull Alice off
    digitalWrite(7, LOW); // Turn off LED's
  }

  // check the RFID's
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    if (checkUID(uuid_1)) {
      //digitalWrite(7,HIGH);
      ttl = 5;
      timercheck = 1; // Allow counting so that it checks for how long you set it to
    }

    delay(50);
    mfrc522.PCD_Init();
    mfrc522.uid.uidByte[0] = 0;
  }

  if (timercheck == 1) { // If Alice is put in the correct place
    delay(100); // Wait 1/10 second
    timer++; // Increment the counter
    Serial.print(timer); // Make the counting visible for debugging
  }
  else { // If Alice isn't there

    Serial.print(timer); // Print ou the count for debugging
  }

}


bool checkUID(byte *uid) {
  return (mfrc522.uid.uidByte[0] == uid[0] && mfrc522.uid.uidByte[1] == uid[1] && mfrc522.uid.uidByte[2] == uid[2] && mfrc522.uid.uidByte[3] == uid[3]);
}

