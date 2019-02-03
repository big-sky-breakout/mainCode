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

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

byte uuid_1[4] = {0x7A,0x18,0x95,0x35};

int ttl = 0;

/**
 * Initialize.
 */
void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    int timer = 0; // This makes it so that it checks only for 12 minutes
    int timercheck = 0; // Only check when this = 1

    // output led
    pinMode(7,OUTPUT);

}

void loop() {
    int timer;
    int timercheck;
    if (timer > 120){
      digitalWrite(7, LOW);
      exit(0);
    }
    if (ttl > 0) {
      digitalWrite(7,HIGH);
      timercheck = 1;
      ttl--;
    } else {
      digitalWrite(7,LOW);
    }
    
    // check the thing
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      if (checkUID(uuid_1)) {
        //digitalWrite(7,HIGH);
        ttl = 5;
      } 
      delay(50);
      mfrc522.PCD_Init();
      mfrc522.uid.uidByte[0] = 0;
    }
    delay(100);
    if (timercheck == 1){
      timer += 1;
    }
}


bool checkUID(byte *uid) {
  return (mfrc522.uid.uidByte[0] == uid[0] && mfrc522.uid.uidByte[1] == uid[1] && mfrc522.uid.uidByte[2] == uid[2] && mfrc522.uid.uidByte[3] == uid[3]);
}

