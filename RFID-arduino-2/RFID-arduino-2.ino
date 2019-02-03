/**
 * ----------------------------------------------------------------------------
 * This is a MFRC522 library example; see https://github.com/miguelbalboa/rfid
 * for further details and other examples.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 * 
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN_1        A0         // Configurable, see typical pin layout above
#define SS_PIN_2        A1         // Configurable, see typical pin layout above
#define SS_PIN_3        A2         // Configurable, see typical pin layout above
#define SS_PIN_4        A3         // Configurable, see typical pin layout above

MFRC522 mfrc522_1(SS_PIN_1, RST_PIN);   // Create MFRC522 instances.
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN);
MFRC522 mfrc522_3(SS_PIN_3, RST_PIN);
MFRC522 mfrc522_4(SS_PIN_4, RST_PIN);

byte uuid_1[4] = {0x7A,0x18,0x95,0x35};
byte uuid_2[4] = {0x7A,0x18,0x95,0x35};
byte uuid_3[4] = {0x7A,0x18,0x95,0x35};
byte uuid_4[4] = {0x7A,0x18,0x95,0x35};


int ttl1 = 0, ttl2 = 0, ttl3 = 0, ttl4 = 0;

/**
 * Initialize.
 */
void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    
    SPI.begin();        // Init SPI bus
    mfrc522_1.PCD_Init(); // Init MFRC522 cards
    mfrc522_2.PCD_Init();
    mfrc522_3.PCD_Init();
    mfrc522_4.PCD_Init();

    // output led
    pinMode(8,OUTPUT);
    // input from arduino #1
    pinMode(7,INPUT);
    
}

byte read1 = 0, read2 = 0, read3 = 0, read4 = 0;

void loop() {
    // check the things
    if (mfrc522_1.PICC_IsNewCardPresent() && mfrc522_1.PICC_ReadCardSerial()) {
      if (checkUID1(uuid_1)) { read1 = 1; }
      else if (checkUID1(uuid_2)) { read1 = 2; }
      else { read1 = 0; }

      if (read1) ttl1 = 5;
      
      delay(50);
      mfrc522_1.PCD_Init();
      mfrc522_1.uid.uidByte[0] = 0;
    }

    if (mfrc522_2.PICC_IsNewCardPresent() && mfrc522_2.PICC_ReadCardSerial()) {
      if (checkUID2(uuid_1)) { read2 = 1; }
      else if (checkUID2(uuid_2)) { read2 = 2; }
      else { read2 = 0; }

      if (read2) ttl2 = 5;
      
      delay(50);
      mfrc522_2.PCD_Init();
      mfrc522_2.uid.uidByte[0] = 0;
    }

    if (mfrc522_3.PICC_IsNewCardPresent() && mfrc522_3.PICC_ReadCardSerial()) {
      if (checkUID3(uuid_3)) { read3 = 1; }
      else if (checkUID3(uuid_4)) { read3 = 2; }
      else { read3 = 0; }

      if (read3) ttl3 = 5;
      
      delay(50);
      mfrc522_3.PCD_Init();
      mfrc522_3.uid.uidByte[0] = 0;
    }

    if (mfrc522_4.PICC_IsNewCardPresent() && mfrc522_4.PICC_ReadCardSerial()) {
      if (checkUID4(uuid_3)) { read4 = 1; }
      else if (checkUID4(uuid_4)) { read4 = 2; }
      else { read4 = 0; }

      if (read4) ttl4 = 5;
      
      delay(50);
      mfrc522_4.PCD_Init();
      mfrc522_4.uid.uidByte[0] = 0;
    }

    if (ttl1) ttl1--;
    if (ttl2) ttl2--;
    if (ttl3) ttl3--;
    if (ttl4) ttl4--;

    if (!ttl1) read1 = 0;
    if (!ttl2) read2 = 0;
    if (!ttl3) read3 = 0;
    if (!ttl4) read4 = 0;

    if (read1) {
      // brighten LEDs near reader 1
    }
    if (read2) {
      // brighten LEDs near reader 2
    }
    if (read3) {
      // brighten LEDs near reader 3
    }
    if (read4) {
      // brighten LEDs near reader 4
    }

    // win logic
    // When you activate all of the RFID'S
    if (((read1 == 1 && read2 == 2) || (read1 == 2 && read2 == 1)) && ((read3 == 1 && read4 == 2) || (read3 == 2 && read4 == 1))) {
      // brighten LEDs all the way
      // send a signal back to arduino 1
      digitalWrite(8,HIGH);
      // i think we want to halt here?
      while(1) {delay(100);}
    }
}


bool checkUID1(byte *uid) {
  return (mfrc522_1.uid.uidByte[0] == uid[0] && mfrc522_1.uid.uidByte[1] == uid[1] && mfrc522_1.uid.uidByte[2] == uid[2] && mfrc522_1.uid.uidByte[3] == uid[3]);
}
bool checkUID2(byte *uid) {
  return (mfrc522_2.uid.uidByte[0] == uid[0] && mfrc522_2.uid.uidByte[1] == uid[1] && mfrc522_2.uid.uidByte[2] == uid[2] && mfrc522_2.uid.uidByte[3] == uid[3]);
}
bool checkUID3(byte *uid) {
  return (mfrc522_3.uid.uidByte[0] == uid[0] && mfrc522_3.uid.uidByte[1] == uid[1] && mfrc522_3.uid.uidByte[2] == uid[2] && mfrc522_3.uid.uidByte[3] == uid[3]);
}
bool checkUID4(byte *uid) {
  return (mfrc522_4.uid.uidByte[0] == uid[0] && mfrc522_4.uid.uidByte[1] == uid[1] && mfrc522_4.uid.uidByte[2] == uid[2] && mfrc522_4.uid.uidByte[3] == uid[3]);
}

