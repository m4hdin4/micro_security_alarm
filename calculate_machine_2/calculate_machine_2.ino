#include <LiquidCrystal.h>
const int rs = 32, en = 34, d4 = 40, d5 = 41, d6 = 42, d7 = 43;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int buzzerPin = 22;
const int ledPin = 2;
boolean buzzer_mode = false;
int ledState = LOW;
long previousMillis = 0; 
long interval = 100;


int fibonachi (int n){
  if (n == 1 || n == 2){
    return 1;
  }
  return fibonachi(n - 1) + fibonachi(n - 2);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16 , 2);
  lcd.clear();
  lcd.setCursor(0 , 0);
  lcd.print(" please enter a ");
  lcd.setCursor(0 , 1);
  lcd.print("     number     ");


  pinMode(21 , INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(21) , error , FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  if (Serial.available()){
    char instruction = Serial.read();
      if (instruction == 'S'){
        lcd.clear();
        lcd.setCursor(0 , 1);
        lcd.print("* CONFIRM # EXIT");
        lcd.setCursor(0 , 0);
        char inp;
        while(!Serial.available());
        inp = Serial.read();
        
        while (inp != 'S' && inp != 'C'){
          lcd.print(inp);
          while(!Serial.available());
          inp = Serial.read();
        }
        if (inp == 'S'){
          lcd.clear();
          lcd.setCursor(0 , 0);
          lcd.print(" please wait a  ");
          lcd.setCursor(0 , 1);
          lcd.print("     moment     ");
        }
        else{
          lcd.clear();
          lcd.setCursor(0 , 0);
          lcd.print(" please enter a ");
          lcd.setCursor(0 , 1);
          lcd.print("     number     ");
        }
      }
      else if (instruction == 'I'){
        while (!Serial.available());
        int n = Serial.read();
        int calc = fibonachi(n);
        Serial.write(calc);
        while (!Serial.available());
        int ans = Serial.read();
        lcd.clear();
        lcd.setCursor(0 , 0);
        lcd.print(" The answer is  ");
        lcd.setCursor(7 , 1);
        lcd.print(ans);
        delay(1000);
        lcd.clear();
        lcd.setCursor(0 , 0);
        lcd.print(" please enter a ");
        lcd.setCursor(0 , 1);
        lcd.print("     number     ");
      }
      else if (instruction == 'D'){
        lcd.clear();
        lcd.setCursor(0 , 0);
        lcd.print(" the answer is  ");
        lcd.setCursor(7 , 1);
        lcd.print("1");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0 , 0);
        lcd.print(" please enter a ");
        lcd.setCursor(0 , 1);
        lcd.print("     number     ");
      }
      else if (instruction == 'E'){
        lcd.clear();
        lcd.setCursor(0 , 0);
        lcd.print("  Wrong Input   ");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0 , 0);
        lcd.print(" please enter a ");
        lcd.setCursor(0 , 1);
        lcd.print("     number     ");
      }
    }
}

void error(){
  buzzer_mode = true;

  while(buzzer_mode){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) {
      lcd.clear();
      lcd.setCursor(0 , 0);
      lcd.print("   WARNING!!!");
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
    buzzer_mode = (digitalRead(21) == LOW);
  }
  digitalWrite(buzzerPin , LOW);
  digitalWrite(ledPin, LOW);

  lcd.clear();
  lcd.setCursor(0 , 0);
  lcd.print(" please enter a ");
  lcd.setCursor(0 , 1);
  lcd.print("     number     ");
}
