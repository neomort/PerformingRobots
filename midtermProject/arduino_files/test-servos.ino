#include <Servo.h>
   Servo servo1;
   Servo servo2;
   Servo servo3;// create servo object to control a servo
    Servo servo4;

   int val; // variable to read the value from the analog pin
    const int in1Pin = 3;
    const int in2Pin = 4; //PWM
    const int in3Pin = 5; //PWM
    const int in4Pin = 6;
    const int button = 14;

    const int leftEye = 22;
    const int rightEye = 21;
    

void setup() {
  Serial.begin(115200);
  
   servo1.attach(2); // attaches the servo on pin 9 to the servo object
   servo2.attach(7);
    servo3.attach(8);
    servo4.attach(23);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(button, INPUT);

   pinMode(leftEye, OUTPUT);
  pinMode(rightEye, OUTPUT);
}

void loop() {
   int position;

 int  buttonState = digitalRead(button);
  
if (buttonState == 1 ){

  Serial.println("move jaw");
  servo4.write(150);
  digitalWrite(leftEye, HIGH);
  digitalWrite(rightEye, HIGH);
  delay(2000);
  servo1.write(100);    // Tell servo to go to 90 degrees

  delay(1000);         // Pause to get it time to move

  servo1.write(0);   // Tell servo to go to 180 degrees

  delay(1000);  

    servo2.write(180);    // Tell servo to go to 90 degrees

  delay(1000);         // Pause to get it time to move

  servo2.write(0);   // Tell servo to go to 180 degrees

  delay(1000); 

    servo3.write(180);    // Tell servo to go to 90 degrees

  delay(1000);         // Pause to get it time to move

  servo3.write(0);   // Tell servo to go to 180 degrees

  delay(1000); 

    servo1.write(100);    // Tell servo to go to 90 degrees
    servo2.write(180); 
    servo3.write(180); 
  delay(1000);         // Pause to get it time to move

  servo1.write(0);   // Tell servo to go to 180 degrees
  servo2.write(0);
  servo3.write(0);

  delay(1000); 

  servo1.write(100);   // Tell servo to go to 180 degrees
  servo2.write(90);
  servo3.write(90);

  delay(1000); 
  
  digitalWrite(in1Pin, LOW); //Backwward
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(500);

  digitalWrite(in1Pin, LOW); //stop
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(500);
  digitalWrite(in1Pin, HIGH); //Forward
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(500);
  digitalWrite(in1Pin, HIGH); //turn
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  delay(500);
  servo4.write(95);
  digitalWrite(in1Pin, LOW); //stop
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  delay(200);
  servo4.write(150);
  digitalWrite(in1Pin, LOW); //turn
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  servo1.write(0);   
  servo2.write(0);
  servo3.write(0);
  delay(1000);
  digitalWrite(in1Pin, HIGH); //turn
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  servo1.write(100);   // Tell servo to go to 180 degrees
  servo2.write(90);
  servo3.write(90);
  delay(1000);

}else { 
  servo1.write(100);   // Tell servo to go to 180 degrees
  servo2.write(90);
  servo3.write(80);
  servo4.write(95);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);

  digitalWrite(in2Pin, LOW);
  digitalWrite(in1Pin, LOW);

  digitalWrite(leftEye, LOW);
  digitalWrite(rightEye, LOW);

}
  
}
