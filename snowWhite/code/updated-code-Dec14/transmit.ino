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
const byte address[6] = "10001";

// Pins for the pushbuttons
int fwdPinR = 2;  //both wheels on
int rightPinR = 3;  //left wheel on
int leftPinR = 4;   //right wheel on
int bkwdPinR = 5; //both wheels on (backwards)
int fwdPinL = 6;  //Happy
int rightPinL = 7;  //Surprised
int leftPinL = 8;   //Shutdown + Head servo
int bkwdPinL = A0;  //Arms
int button9 = A1; //Arms

const int pot1 = A5;  //waist

//const int pot3 = A3;
//const int pot4 = A2;

void setup() {
  Serial.begin(115200);

  pinMode(fwdPinR, INPUT_PULLUP);
  pinMode(rightPinR, INPUT_PULLUP);
  pinMode(leftPinR, INPUT_PULLUP);
  pinMode(bkwdPinR, INPUT_PULLUP);
  pinMode(fwdPinL, INPUT_PULLUP);
  pinMode(rightPinL, INPUT_PULLUP);
  pinMode(leftPinL, INPUT_PULLUP);
  pinMode(bkwdPinL, INPUT_PULLUP);
  pinMode(button9, INPUT_PULLUP);


  boolean retval = radio.begin();   //Starting the Wireless communication
  Serial.println(retval);
  radio.openWritingPipe(address);  //destination addres
  radio.setPALevel(RF24_PA_MAX);   // min or max
  radio.stopListening();           //This sets the module as transmitter
}
void loop() {
 //read the potentiometers
  int pot1Val = analogRead(pot1);
//  int pot3Val = analogRead(pot3);
//  int pot4Val = analogRead(pot4);

int potMap = map(pot1Val, 0, 1023, 0, 128);

//shift everything over
  int leftR = digitalRead(fwdPinR) << 0;
  int fwdR = digitalRead(rightPinR) << 1;
  int rightR = digitalRead(bkwdPinR) << 2;
  int bkwdR = digitalRead(leftPinR) << 3;
  int leftL = digitalRead(leftPinL) << 4;
  int fwdL = digitalRead(fwdPinL) << 5;
  int rightL = digitalRead(rightPinL) << 6;
  int bkwdL = digitalRead(bkwdPinL) << 7;
  int b9 = digitalRead(button9) << 8;

  if (leftR == HIGH) {
    digitalWrite(fwdPinR, LOW);
//    Serial.print("lowA");

  } else {

    digitalWrite(fwdPinR, HIGH);
//    Serial.print("highA");
  }
  if (rightR == HIGH) {
    digitalWrite(bkwdPinR, LOW);
//    Serial.print("lowC");

  } else {

    digitalWrite(bkwdPinR, HIGH);
//    Serial.print("highC");
  }
  if (fwdR == HIGH) {
    digitalWrite(rightPinR, LOW);
//    Serial.print("lowB");

  } else {

    digitalWrite(rightPinR, HIGH);
//    Serial.print("highB");
  }
  if (bkwdR == HIGH) {
    digitalWrite(leftPinR, LOW);
//    Serial.print("lowD");

  } else {

    digitalWrite(leftPinR, HIGH);
//    Serial.print("highD");
  }
  if (leftL == HIGH) {

    digitalWrite(leftPinL, LOW);
//    Serial.print("lowE");

  } else {

    digitalWrite(leftPinL, HIGH);
//    Serial.print("highE");
  }
  if (fwdL == HIGH) {
    digitalWrite(fwdPinL, LOW);
//    Serial.print("lowF");

  } else {

    digitalWrite(fwdPinL, HIGH);
//    Serial.print("highF");
  }
  if (rightL == HIGH) {
    digitalWrite(rightPinL, LOW);
//    Serial.print("lowG");

  } else {
    digitalWrite(rightPinL, HIGH);
//    Serial.print("highG");
  }
  if (bkwdL == HIGH) {
    digitalWrite(bkwdPinL, LOW);
//    Serial.print("lowH");

  } else {
    digitalWrite(bkwdPinL, HIGH);
//    Serial.print("highH");
  }

 if (b9 == HIGH) {
    digitalWrite(button9, LOW);
//    Serial.print("lowI");

  } else {
    digitalWrite(button9, HIGH);
//    Serial.print("highI");
  }
  Serial.println(potMap);


  int data[2];
  data[0] = leftR | fwdR | rightR | bkwdR | leftL | fwdL | rightL | bkwdL | b9;
  data[1] = potMap;
  

  if (data) {
    Serial.print( "sending data = " );
    Serial.println(data[0]);
    radio.write(&data, sizeof(data)) ;
  }

}
