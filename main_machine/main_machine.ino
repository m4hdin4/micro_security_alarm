#include <Servo.h>

const int servoCount = 10;
Servo machineServos[servoCount];

const int buzzerPin = 22;
const int ledPin = 2;
boolean buzzer_mode = false;
int ledState = LOW;
long previousMillis = 0; 
long interval = 100;

int value;
void setup() {
  // put your setup code here, to run once:
  pinMode(2 , OUTPUT);
  pinMode(53 , OUTPUT);
  pinMode(13 , OUTPUT);
  digitalWrite(53 , HIGH);
  digitalWrite(13 , HIGH);

  pinMode(ledPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  value = 2000 - (4 * analogRead(A0));

  for (int i = 0 ; i < servoCount ; i++) {
    machineServos[i].attach(12 - i);
    machineServos[i].writeMicroseconds(value);
  }
  if(value < 1000){
    digitalWrite(53 , LOW);
    digitalWrite(13 , LOW);
    
    while(value < 1000){
      unsigned long currentMillis = millis();
      if(currentMillis - previousMillis > interval) {
        previousMillis = currentMillis;   
        if (ledState == LOW){
          ledState = HIGH;
          digitalWrite(buzzerPin , HIGH);
        }
        else{
          ledState = LOW;
          digitalWrite(buzzerPin , LOW);
        }
      // Switch the LED
      digitalWrite(ledPin, ledState);
      }
      value = 2000 - (4 * analogRead(A0));
    }
    digitalWrite(53 , HIGH);
    digitalWrite(13 , HIGH);
    digitalWrite(buzzerPin , LOW);
    digitalWrite(ledPin, LOW);
  }
}
