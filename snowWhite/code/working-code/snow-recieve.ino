#include <Servo.h>
   Servo arms;
   Servo leftArm;
   Servo rightArm;

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

const byte address[6] = "10001";

    const int drive1 = 2;
    const int drive2 = 3;//PWM
    const int drive3 = 4;//PWM
    const int drive4 = 5;
    

    int armsAngle = 90;
    int leftAngle = 90;
    int rightAngle = 90;

void setup() {
  
 
    pinMode(drive1, OUTPUT);
    pinMode(drive2, OUTPUT);
    pinMode(drive3, OUTPUT);
    pinMode(drive4, OUTPUT);
    arms.attach(23);
    leftArm.attach(22);
    rightArm.attach(21);
    
    

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
  radio.startListening();  
}

void loop() {
  
 
 uint8_t pipeNum;
 
 
  if (radio.available(&pipeNum))  //Looking for the data.x
  {
    int data;
  
    Serial.print("data available on pipe ");
    Serial.println(pipeNum);

    radio.read(&data, sizeof(data));  //Reading the data
    Serial.print("data = ");
    Serial.println( data);

    

     switch (data) {
        
      case 1:
        
        Serial.println("forward");
        digitalWrite(drive1, LOW);
        digitalWrite(drive2, HIGH);
        digitalWrite(drive3, HIGH);
        digitalWrite(drive4, LOW);
        break;
      case 8:
        Serial.println("backward");
        digitalWrite(drive1, HIGH);
        digitalWrite(drive2, LOW);
        digitalWrite(drive3, LOW);
        digitalWrite(drive4, HIGH);
        break;
      case 2:
        Serial.println("turning left");
        digitalWrite(drive1, LOW);
        digitalWrite(drive2, HIGH);
        digitalWrite(drive3, LOW);
        digitalWrite(drive4, HIGH);
        break;
      case 4:
        Serial.println("turning right");
        digitalWrite(drive1, HIGH);
        digitalWrite(drive2, LOW);
        digitalWrite(drive3, HIGH);
        digitalWrite(drive4, LOW);
        break;
         case 16:
        Serial.println("arms");
        armsAngle--;
        arms.write(armsAngle);
        break;
          case 3:
        armsAngle++;
        arms.write(armsAngle);
          break;
         case 32:
          armsAngle++;
          arms.write(armsAngle);
//        leftAngle++;
//        rightAngle--;
//        leftArm.write(leftAngle);
//        rightArm.write(rightAngle);
        break;
         case 64:
        leftAngle--;
        rightAngle++;
        leftArm.write(leftAngle);
        rightArm.write(rightAngle);
        break;
        case 128:
        leftAngle++;
        rightAngle--;
        leftArm.write(leftAngle);
        rightArm.write(rightAngle);
        break;
      }
  } else {
    Serial.println("stop");
    stop();
  }
  delay(5);
}


void stop() {

  digitalWrite(drive1, LOW);
  digitalWrite(drive2, LOW);
  digitalWrite(drive3, LOW);
  digitalWrite(drive4, LOW);
  
  
}
