#include <Servo.h>


Servo servo1;

const int in1Pin = 4;
const int in2Pin = 5; //PWM
const int in3Pin = 6; //PWM
const int in4Pin = 7;

const int button = 11;
const int buttonLED = 12;

void setup() {
  servo1.attach(9);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(button, INPUT);
  pinMode(buttonLED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int position;
  int  buttonState = digitalRead(button);
  Serial.println(buttonState);


  
if (buttonState == 1 ){
  digitalWrite(buttonLED, HIGH);
  servo1.write(0);
  delay(4000);

  
  digitalWrite(in1Pin, HIGH); //forward
  digitalWrite(in3Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(2400);
  digitalWrite(in3Pin, HIGH); //stop
  digitalWrite(in4Pin, HIGH);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in1Pin, HIGH);
  delay(1000);
  digitalWrite(in1Pin, LOW); //backward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(300);
  digitalWrite(in1Pin, HIGH); //turn RIGHT
  digitalWrite(in3Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(1200);
  digitalWrite(in1Pin, LOW); //backward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(500);
  digitalWrite(in1Pin, LOW); //stop
  digitalWrite(in3Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(1000);
  servo1.write(90); // drop load
  delay(2000);
  digitalWrite(in1Pin, HIGH); 
  digitalWrite(in3Pin, LOW); // forward
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(500);
  servo1.write(0);
  digitalWrite(in1Pin, LOW); //turn LEFT
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(500);
  digitalWrite(in1Pin, LOW); //backward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(1700);
  
  
} else { 
  servo1.write(0);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);

  digitalWrite(in2Pin, LOW);
  digitalWrite(in1Pin, LOW);
  digitalWrite(buttonLED, LOW);
}
  // put your main code here, to run repeatedly:

}
