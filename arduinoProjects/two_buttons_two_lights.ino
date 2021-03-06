

// digital pin 2 has a pushbutton attached to it. Give it a name:
const int pushButton = 2;
const int pushButton2 = 3;
const int LEDpin = 4;
const int LEDpin2 = 5;

bool bool1;
bool bool2;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  int buttonState2 = digitalRead(pushButton2);

  
  
  if (buttonState == 1 && buttonState2 == 0){
    digitalWrite(LEDpin, HIGH);
  } else if (buttonState == 0 && buttonState2 == 1){
    digitalWrite(LEDpin2, HIGH);
  } else if (buttonState == 1 && buttonState2 == 1){
    digitalWrite(LEDpin2, HIGH);
  } else {
    digitalWrite(LEDpin, LOW);
    digitalWrite(LEDpin2, LOW);
  }
  
  // print out the state of the button:
  Serial.println(buttonState);
  delay(1);        // delay in between reads for stability
}

]
