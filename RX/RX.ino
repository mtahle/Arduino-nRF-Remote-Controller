/*
By Mujahed Altahleh
Demonstrates simple RX and TX operation.
Any of the Basic_TX examples can be used as a transmitter.
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

int noDataConter = 0;

const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
#define MSG_SIZE 8

byte RADIO_ID = 0x00;  // Our radio's id.  The transmitter will send to this id.
byte msg[MSG_SIZE];

NRFLite _radio;

void setup()
{
    Serial.begin(115200);
    pinMode(2,OUTPUT);
    digitalWrite(2,HIGH);
    pinMode(3,OUTPUT);
    digitalWrite(3,HIGH);
    pinMode(4,OUTPUT);
    digitalWrite(3,HIGH);
    pinMode(5,OUTPUT);
    digitalWrite(3,HIGH);
    // By default, 'init' configures the radio to use a 2MBPS bitrate on channel 100 (channels 0-125 are valid).
    // Both the RX and TX radios must have the same bitrate and channel to communicate with each other.
    // You can run the 'ChannelScanner' example to help select the best channel for your environment.
    // You can assign a different bitrate and channel as shown below.
    //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100) // THE DEFAULT
    //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE1MBPS, 75)
    //   _radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 0)
    Serial.println("This is the reciever");
    if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
    {
        Serial.println("Cannot communicate with radio");
        while (1); // Wait here forever.
    }
}

void loop()
{
    while (_radio.hasData())
    {
        noDataConter=0;

        _radio.readData(&msg); // Note how '&' must be placed in front of the variable name.
        if (msg[0] ==0x3f && msg[1] == 0x5a ) {

        if ( msg[7] == checksum(msg)) {
        
        String consoleMsg = "Checksum ";

        for (int i=3;i<=6;i++){
           digitalWrite(i-1,!msg[i]);
        }
    


   

       // Serial.println(consoleMsg);
        }
        
        }
      
    }


    
    if(!_radio.hasData()){
      noDataConter++;
      delay(50);
      if(noDataConter>10) {
      //  Serial.println("no data");
         for (int i=2;i<=5;i++){
             
              digitalWrite(i,HIGH);
             
         }
    }
    }
   
}

byte checksum (byte data[]) {
  
  byte check = 0x00;
  
  for (int i=0; i <MSG_SIZE-1; i++) {
    check ^=data[i];
    }
   return check;
}
