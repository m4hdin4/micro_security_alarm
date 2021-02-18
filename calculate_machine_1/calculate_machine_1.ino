#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 3;
byte rowPins[ROWS] = {35 , 39 , 43 , 47};
byte colPins[COLS] = {31 , 27 , 23};
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char key;

int fibonachi (int n){
  if (n == 1 || n == 2){
    return 1;
  }
  return fibonachi(n - 1) + fibonachi(n - 2);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  key = keypad.getKey();
  if (isDigit(key)){
   String input = "";
   Serial.write('S');
   while (isDigit(key)){
    Serial.write(key);
    input += key;
    key = keypad.waitForKey();
   }
   if (key == '*'){
    Serial.write('S');
    int n = input.toInt();
    if (n > 2){
      Serial.write('I');
      Serial.write(n - 1);
      int x = fibonachi(n - 2);
      while (!Serial.available());
      int y = Serial.read();
      Serial.write(x + y);
    }
    else if (n > 0){
      Serial.write('D');
    }
    else{
      Serial.write('E');
    }
   }
   else{
    Serial.write('C');
   }
   //Serial.write(key);
  }
}
