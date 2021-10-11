/*
   Example using the nRF24L01 radio module to communicate 
   between two Arduinos,
   the transmitter is connected to some pushbuttons
   the receiver is connected to a motor driver
*/
#include <Servo.h>
   Servo servo1;
   Servo servo2;
   Servo servo3;


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


RF24 radio(CEPIN, CSNPIN);  // CE, CSN


// Byte of array representing the address. 
// This is the address where we will send the data. 
// This should be same on the receiving side.
const byte address[6] = "00001";

// Motor controller pins
const int rightDirPin = 3;
const int rightPWMPin = 4;
const int leftDirPin = 5;
const int leftPWMPin = 6;
const int button = 14;

void setup() {


  pinMode(button, INPUT);

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);

  Serial.begin(115200);

  // RF24 setup
   if (!radio.begin()) {
    Serial.println("radio  initialization failed");
    while (1)
      ;
  } else {
    Serial.println("radio successfully initialized");
  }
  radio.openReadingPipe(0, address);  // Destination address
  radio.setPALevel(RF24_PA_MIN);      // Min or max
  radio.startListening();             // sets  module as receiver


  servo1.attach(2); 
   servo2.attach(7);
    servo3.attach(8);


  servo1.write(100);   // Tell servo to go to 180 degrees
  servo2.write(90);
  servo3.write(80);

}
void loop() {
  uint8_t pipeNum;
  if (radio.available(&pipeNum))  //Looking for the data.
  {
    int data;

    Serial.print("data available on pipe ");
    Serial.println(pipeNum);

    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("data = ");
    Serial.println( data);

    switch (data) {
        
      case 0b10000000:
//        Serial.println("turning right");
//        digitalWrite(rightDirPin, LOW);
//        analogWrite(rightPWMPin, 255);
//        break;
        Serial.println("backward");
        digitalWrite(rightDirPin, HIGH);
        analogWrite(rightPWMPin, 0);
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 0);
        break;
      case 0b01000000:
        Serial.println("forward");
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 255);
        digitalWrite(leftDirPin, LOW);
        analogWrite(leftPWMPin, 255);
        break;
      case 0b00100000:
        Serial.println("turning left");
        digitalWrite(leftDirPin, LOW);
        analogWrite(leftPWMPin, 255);
        digitalWrite(rightDirPin, HIGH);
        analogWrite(rightPWMPin, 0);
        break;
      case 0b00010000:
        Serial.println("turning right");
        digitalWrite(leftDirPin, HIGH);
        analogWrite(leftPWMPin, 0);
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 255);
        break;
        case 0b00001000:
        Serial.println("Nod");
         servo1.write(100);
         delay(300);
         servo1.write(0);
         delay(300);
        break;
        case 0b00000100:
        Serial.println("Nod");
         servo1.write(50);
         servo2.write(180);
         servo3.write(40);
        break;
        case 0b00000010:
        Serial.println("shake");
         servo1.write(0);
         servo2.write(0);
         servo3.write(130);
        break;
      default:
        Serial.println("no info");
        stop();
        digitalWrite(rightDirPin, LOW);
        digitalWrite(rightPWMPin, LOW);
        break;
    }
  } else {
    Serial.println("stop");
    stop();
  }
  delay(5);
}


void stop() {

  digitalWrite(rightDirPin, LOW);
  analogWrite(rightPWMPin, 0);
  digitalWrite(leftDirPin, LOW);
  analogWrite(leftPWMPin, 0);
  servo1.write(100);  
  servo2.write(90);
  servo3.write(80);
}
