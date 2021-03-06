#include <Servo.h>
#include <Stepper.h>

Servo arms;
Servo leftArm;
Servo rightArm;
Servo head;

const int CEPIN = 9;
const int CSNPIN = 10;

int buttons;



// In summary,
// nRF 24L01 pin    Arduino pin   name
//          1                     GND
//          2                     3.3V
//          3             9       CE
//          4             10      CSN
//          5             13      SCLK
//          6             11      MOSI/COPI
//          7             12      MISO/CIPO

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

float startTime;
boolean isActive = false;
int currentFrame = 0;

#define LED_PIN    18

#define LED_COUNT 89  //ADD EYES

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB);

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
int headAngle = 90;

Stepper myStepper(200, 14, 15, 22, 23);


void setup() {

  // set the speed at 60 rpm:
  myStepper.setSpeed(20);

  pinMode(drive1, OUTPUT);
  pinMode(drive2, OUTPUT);
  pinMode(drive3, OUTPUT);
  pinMode(drive4, OUTPUT);
  arms.attach(23);
  leftArm.attach(22);
  rightArm.attach(21);
  //head.attach( 16 ,17, 18, 19, 20?  //COME BACK TO THIS

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  strip.begin();
  strip.show();
  strip.setBrightness(30);


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
  radio.setPALevel(RF24_PA_MAX);      // Min or max
  radio.startListening();
}

void loop() {

  uint8_t pipeNum;
  int data[2];
  if (radio.available()) {

    Serial.print("data available on pipe ");
    Serial.println(pipeNum);

    radio.read(&data, sizeof(data));

    buttons = data[0];

    Serial.print("data = ");
    Serial.println(buttons);

    switch (buttons) {
      case 383:
        Serial.println("left");
        digitalWrite(drive1, LOW);
        digitalWrite(drive2, HIGH);
        digitalWrite(drive3, LOW);
        digitalWrite(drive4, LOW);
        break;
      case 255:
        Serial.println("forward");
        digitalWrite(drive1, LOW);
        digitalWrite(drive2, HIGH);
        digitalWrite(drive3, HIGH);
        digitalWrite(drive4, LOW);
        break;
      case 510:
        Serial.println("turning right");
        digitalWrite(drive1, LOW);
        digitalWrite(drive2, LOW);
        digitalWrite(drive3, HIGH);
        digitalWrite(drive4, LOW);
        break;
      case 509:
        Serial.println("backwards");
        digitalWrite(drive1, HIGH);
        digitalWrite(drive2, LOW);
        digitalWrite(drive3, LOW);
        digitalWrite(drive4, HIGH);
        break;
      case 479:
        Serial.println("arms down and in");  //go down and in
        armsAngle--;
        arms.write(armsAngle);
        leftAngle--;    //COME BACK TO THIS PLS
        rightAngle++;
        leftArm.write(leftAngle);
        rightArm.write(rightAngle);
        break;

      case 447:
        Serial.println("arms up and out");
        armsAngle++;
        arms.write(armsAngle);  //go up and out
        leftAngle++;
        rightAngle--;
        leftArm.write(leftAngle);
        rightArm.write(rightAngle);
        break;
      case 503:
        Serial.println("happy");
        startShow(4);
        break;
      case 507:
        Serial.println("surprised");
        startShow(8);
        break;
      case 495:
        Serial.println("shutdown");
        startShow(2);
        head.write(headAngle);
        break;
    }

    switch (data[1]) {
      case 1:
        Serial.println("waist moving");
        float potentiometer = map(data[1], 0, 1023, -200, 200);
        myStepper.step(potentiometer);
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
  strip.clear();

}

void startShow(int i) {
  switch (i) {
      break;
    case 2:
      Serial.println("shutdown");
      if (isActive == false) {
        startTime = millis();
        isActive = true;
        currentFrame = 0;
      }
      if (millis() > startTime + 300) {
        currentFrame = 1 - currentFrame;
        startTime = millis();
      }
      if (currentFrame == 0) {
        strip.setPixelColor(9, 150, 0, 0);
        strip.setPixelColor(18, 150, 0, 0);
        strip.setPixelColor(27, 150, 0, 0);
        strip.setPixelColor(36, 150, 0, 0);
        strip.setPixelColor(45, 150, 0, 0);
        strip.setPixelColor(54, 150, 0, 0);

        strip.setPixelColor(14, 150, 0, 0);
        strip.setPixelColor(21, 150, 0, 0);
        strip.setPixelColor(28, 150, 0, 0);
        strip.setPixelColor(35, 150, 0, 0);
        strip.setPixelColor(42, 150, 0, 0);
        strip.setPixelColor(49, 150, 0, 0);


        for (int i = 64; i < 70; i++) {
          strip.setPixelColor(i, 250, 0, 0);
        }
        for (int i = 77; i < 83; i++) {
          strip.setPixelColor(i, 250, 0, 0);
        }

        strip.show();
        strip.clear();
      } else {

        strip.setPixelColor(42, 150, 150, 150);
        strip.setPixelColor(53, 150, 150, 150);
        strip.setPixelColor(51, 150, 150, 150);
        strip.setPixelColor(52, 150, 150, 150);
        strip.setPixelColor(33, 150, 150, 150);
        strip.setPixelColor(25, 150, 150, 150);
        strip.setPixelColor(17, 150, 150, 150);
        strip.setPixelColor(46, 150, 150, 150);
        strip.setPixelColor(39, 150, 150, 150);
        strip.setPixelColor(31, 150, 150, 150);
        strip.setPixelColor(23, 150, 150, 150);
        strip.setPixelColor(14, 150, 150, 150);
        strip.setPixelColor(10, 150, 150, 150);
        strip.setPixelColor(5, 150, 150, 150);
        strip.setPixelColor(4, 150, 150, 150);
        strip.setPixelColor(3, 50, 50, 50);

        //eyes
        for (int i = 64; i < 100; i++) {
          strip.setPixelColor(i, 250, 250, 250);
        }


        strip.show();
        strip.clear();
      }
      break;
    case 4:
      Serial.println("happy");
      if (isActive == false) {
        startTime = millis();
        isActive = true;
        currentFrame = 0;
      }
      if (millis() > startTime + 800) {
        currentFrame = 1 - currentFrame;
        startTime = millis();
      }
      if (currentFrame == 0) {


        strip.setPixelColor(58, 0, 255, 0);
        strip.setPixelColor(59, 0, 255, 0);
        strip.setPixelColor(60, 0, 255, 0);
        strip.setPixelColor(50, 0, 255, 0);
        strip.setPixelColor(42, 0, 255, 0);
        strip.setPixelColor(34, 0, 255, 0);
        strip.setPixelColor(26, 0, 255, 0);
        strip.setPixelColor(18, 0, 255, 0);
        strip.setPixelColor(10, 0, 255, 0);
        strip.setPixelColor(11, 0, 255, 0);
        strip.setPixelColor(12, 0, 255, 0);
        strip.setPixelColor(21, 0, 255, 0);
        strip.setPixelColor(46, 0, 255, 0);
        strip.setPixelColor(38, 0, 255, 0);
        strip.setPixelColor(30, 0, 255, 0);
        strip.setPixelColor(53, 0, 255, 0);


        for (int i = 64; i < 100; i++) {
          strip.setPixelColor(i, 0, 250, 0);
        }

        strip.show();
        strip.clear();
      } else {


        strip.setPixelColor(36, 0, 255, 0);

        strip.setPixelColor(38, 0, 255, 0);

        strip.setPixelColor(46, 0, 255, 0);

        strip.setPixelColor(52, 0, 255, 0);
        strip.setPixelColor(53, 0, 255, 0);
        strip.setPixelColor(60, 0, 255, 0);
        strip.setPixelColor(44, 0, 255, 0);
        strip.setPixelColor(28, 0, 255, 0);
        strip.setPixelColor(20, 0, 255, 0);
        strip.setPixelColor(12, 0, 255, 0);
        strip.setPixelColor(21, 0, 255, 0);
        strip.setPixelColor(30, 0, 255, 0);

        //eyes
        for (int i = 64; i < 100; i++) {
          strip.setPixelColor(i, 0, 250, 0);
        }

        strip.show();
        strip.clear();
      }

      break;
    case 8:
      Serial.println("surprise");
      if (isActive == false) {
        startTime = millis();
        isActive = true;
        currentFrame = 0;
      }
      if (millis() > startTime + 800) {
        currentFrame = 1 - currentFrame;
        startTime = millis();
      }
      if (currentFrame == 0) {
        strip.setPixelColor(42, 150, 150, 150);
        strip.setPixelColor(53, 150, 150, 150);
        strip.setPixelColor(51, 150, 150, 150);
        strip.setPixelColor(52, 150, 150, 150);
        strip.setPixelColor(33, 150, 150, 150);
        strip.setPixelColor(25, 150, 150, 150);
        strip.setPixelColor(17, 150, 150, 150);
        strip.setPixelColor(46, 150, 150, 150);
        strip.setPixelColor(39, 150, 150, 150);
        strip.setPixelColor(31, 150, 150, 150);
        strip.setPixelColor(23, 150, 150, 150);
        strip.setPixelColor(14, 150, 150, 150);
        strip.setPixelColor(10, 150, 150, 150);
        strip.setPixelColor(5, 150, 150, 150);
        strip.setPixelColor(4, 150, 150, 150);
        strip.setPixelColor(3, 50, 50, 50);
        //eyes
        for (int i = 65; i < 100; i++) {
          strip.setPixelColor(i, 250, 250, 250);
        }

        strip.show();
        strip.clear();
      } else {
        strip.setPixelColor(42, 250, 250, 250);
        strip.setPixelColor(53, 250, 250, 250);
        strip.setPixelColor(51, 250, 250, 250);
        strip.setPixelColor(52, 250, 250, 250);
        strip.setPixelColor(33, 250, 250, 250);
        strip.setPixelColor(25, 250, 250, 250);
        strip.setPixelColor(17, 250, 250, 250);
        strip.setPixelColor(46, 250, 250, 250);
        strip.setPixelColor(39, 250, 250, 250);
        strip.setPixelColor(31, 250, 250, 250);
        strip.setPixelColor(23, 250, 250, 250);
        strip.setPixelColor(14, 250, 250, 250);
        strip.setPixelColor(10, 250, 250, 250);
        strip.setPixelColor(5, 250, 250, 250);
        strip.setPixelColor(4, 250, 250, 250);
        strip.setPixelColor(3, 250, 250, 250);

        //eyes
        for (int i = 64; i < 89; i++) {
          strip.setPixelColor(i, 250, 250, 250);
        }

        strip.show();
        strip.clear();
      }
      break;
  }
}
