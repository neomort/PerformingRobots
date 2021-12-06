
   
/*
   Example using the nRF24L01 radio module to communicate 
   between two Arduinos,
   the transmitter is connected to some pushbuttons
   the receiver is connected to a motor driver
*/

// Pin usage
// nRF24L01 uses SPI which is fixed on pins 11, 12, and 13.
// It also requires two other signals
// (CE = Chip Enable, CSN = Chip Select Not)
// Which can be any pins:

const int CEPIN = 9;
const int CSNPIN = 10;

// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN  
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO 

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(CEPIN, CSNPIN);                // CE, CSN

// Byte of array representing the address. 
// This is the address where we will send the data. 
// This should be same on the receiving side.
const byte address[6] = "00001"; 

// Pins for the pushbuttons
const int fwdPinR = 2;
const int rightPinR = 3;
const int leftPinR = 4;
const int bkwdPinR = 5; 
const int fwdPinL = 6; 
const int rightPinL = 7;
const int leftPinL = 8;
//const int bkwdPinL = 1;
const int pot1 = A5;

void setup() {
  Serial.begin(115200);

   boolean retval = radio.begin();   //Starting the Wireless communication
  Serial.println(retval);
  radio.openWritingPipe(address);  //destination addres
  radio.setPALevel(RF24_PA_MIN);   // min or max
  radio.stopListening();           //This sets the module as transmitter
}
void loop() {

int leftR = digitalRead(fwdPinR) << 0;
int fwdR = digitalRead(rightPinR) << 1;
int rightR = digitalRead(bkwdPinR) << 2;
int bkwdR = digitalRead(leftPinR) << 3;
int leftL = digitalRead(leftPinL) << 4;
int fwdL = digitalRead(fwdPinL) << 5;
int rightL = digitalRead(rightPinL) << 6;
//int bkwdL = digitalRead(bkwdPinL) << 7;
int pot1Val = analogRead(pot1);



//Serial.print(leftR);
//Serial.print(",");
//Serial.print(fwdR);
//Serial.print(",");
//Serial.print(rightR);
//Serial.print(",");
//Serial.print(bkwdR);
//Serial.print(",");
//Serial.print(leftL);
//Serial.print(",");
//Serial.print(fwdL);
//Serial.print(",");
//Serial.print(rightL);
//Serial.print(",");
//Serial.println(bkwdL);
//delay(20);
// | bkwdL
int data = leftR | fwdR | rightR | bkwdR | leftL | fwdL | rightL;
//Serial.println(pot1Val);
    if (data) {
      
      Serial.print( "sending data = " );
      Serial.println(data);
      radio.write(&data, sizeof(data)) ;
    }

//    data = analogRead (A0);
//    radio.write(&data, sizeof(data)) ;
}
