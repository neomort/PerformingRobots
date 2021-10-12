//#include <Servo.h>
//
//
//Servo servo1;
//Servo servo2;

const int in1Pin = 3;
const int in2Pin = 4; //PWM
const int in3Pin = 5; //PWM
const int in4Pin = 6;


//const int in1Pin2 = 20;
//const int in2Pin2 = 21; //PWM
//const int in3Pin2 = 22; //PWM
//con;
const int buttonLED = LED_BUILTIN;

void setup() {
//  servo1.attach(9);
//  servo2.attach(19);
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
//  servo1.write(180);
  delay(2000);
  
  digitalWrite(in1Pin, LOW); //Backwward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(500);
//  servo1.write(120);
  digitalWrite(in1Pin, LOW); //stop
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
//  digitalWrite(in1Pin2, HIGH); //SHOOT
//  digitalWrite(in3Pin2, LOW);
//  digitalWrite(in2Pin2, LOW);
//  digitalWrite(in4Pin2, HIGH);
  delay(500);
  
  digitalWrite(in1Pin, HIGH); //Forward
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(500);
  servo1.write(180);
  digitalWrite(in1Pin, LOW); //stop
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(500);
  servo2.write(0);
  delay(200);
  digitalWrite(in1Pin, HIGH); //turn
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(500);
  servo1.write(120);
  digitalWrite(in1Pin, LOW); //stop
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(500);
  servo1.write(180);
  digitalWrite(in1Pin, LOW); //turn
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(500);

  
  
} else { 
//  servo1.write(180);
//  servo2.write(160);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);

  digitalWrite(in2Pin, LOW);
  digitalWrite(in1Pin, LOW);
  digitalWrite(buttonLED, LOW);
}
  // put your main code here, to run repeatedly:

}
