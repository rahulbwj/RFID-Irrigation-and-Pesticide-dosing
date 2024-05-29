#include <SPI.h>
#include <MFRC522.h>

#define switch01 2
#define switch02 3
#define boardR 9600
#define SS_PIN 10
#define RST_PIN 9

byte readCard[4];
String tag_UID01 = "46248632";  
String tag_UID02 = "4915B06E";  
String tagID = "";
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup(){
  Serial.begin(boardR);
  
  pinMode(switch01,OUTPUT);
  pinMode(switch02,OUTPUT);

  digitalWrite(switch01,1);
  digitalWrite(switch02,1);

  SPI.begin(); 
  mfrc522.PCD_Init();
}

void loop(){
  while (readID())
  {
    if (tagID == tag_UID01)
    {
      digitalWrite(switch01,0);
      delay(2000);
    }
    else if (tagID == tag_UID02)
    {
      digitalWrite(switch02,0);
      delay(2000);
    }
    else
    {
      digitalWrite(switch01,1);
      digitalWrite(switch02,1);
    }
  }
  digitalWrite(switch01,1);
  digitalWrite(switch02,1);
  /*DEBUIG
  if(Serial.available()){
    char data = Serial.read();
    if(data=='a'){
      digitalWrite(switch01,1);
    }
    else if(data=='d'){
      digitalWrite(switch01,0);
    }
    else if(data=='s'){
      digitalWrite(switch02,1);
    }
    else if(data=='w'){
      digitalWrite(switch02,0);
    }
  }*/
}

boolean readID(){
  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return false;
  }
  tagID = "";
  
  for ( uint8_t i = 0; i < 4; i++)
  {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); 
  return true;
}