/*

Demonstrates simple RX and TX operation.
Any of the Basic_RX examples can be used as a receiver.
Please read through 'NRFLite.h' for a description of all the methods available in the library.

Radio    Arduino
CE    -> 9
CSN   -> 10 (Hardware SPI SS)
MOSI  -> 11 (Hardware SPI MOSI)
MISO  -> 12 (Hardware SPI MISO)
SCK   -> 13 (Hardware SPI SCK)
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include <SPI.h>
#include <NRFLite.h>
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
#define MSG_SIZE 8


const static byte RADIO_ID = 0x01; // Our radio's id.
byte msg[MSG_SIZE];

NRFLite _radio;



void setup()
{
    msg[0]=0x3f; //header1
    msg[1]=0x5a; //header2
    msg[2]=RADIO_ID;
    
    Serial.begin(115200);
    
    Serial.println("This is the transmitter");
    
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    pinMode(5,INPUT);
    
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Cannot communicate with radio");
        while (1); // Wait here forever.
    }
    
    
}

void loop()
{
    bool isData=0;
    for (int i = 3; i<=6;i++) {
      msg[i] = digitalRead(i-1);
      isData |=msg[i];

    }
   
    byte msgChecksum = checksum(msg);

    msg[7] = msgChecksum;

  
      
     // Serial.print("Sending ");

      
      if(isData) {
        if (_radio.send(DESTINATION_RADIO_ID, &msg, sizeof(msg))) // Note how '&' must be placed in front of the variable name.
        {
           // Serial.println("...Success");
        }
        else
        {
            Serial.println("...Failed");
        }
        delay(300);
      }
    
  
}

byte checksum (byte data[]) {
  byte check = 0x00;

  for (int i=0; i <MSG_SIZE-1; i++) {
    check ^= data[i];
  }

  return check;
}
