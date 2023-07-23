/*
  Matrix Keypad Demo
  keypad-demo.ino
  Demonstrates use of 4x4 matrix membrane keypad with Arduino
  Results on serial monitor

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Include the Keypad library
#include <Keypad.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Servo.h>

Servo myservo;
#define servoPin 12
int angle = 0;





LiquidCrystal_I2C lcd(0x27, 16, 2);

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


char enteredPass[5];
int inputs = 0;

void setup() {
  // Setup serial monitor
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  delay(2000);
  lcd.setCursor(0, 1);


  myservo.attach(servoPin);
  myservo.write(0);

}

void loop() {
  // Get key value if pressed
  char customKey = customKeypad.getKey();

  if (customKey) {
    // Print key value to serial monitor
    lcd.print(customKey);
    enteredPass[inputs++] = customKey;

    if (strcmp(enteredPass, "1234") == 0){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Correct!!");
      delay(1000);
      lcd.clear();
      lcd.print("Welcome !!");
      for (angle = 0; angle <= 90; angle += 1) {
        myservo.write(angle);
        delay(10);
      }
      delay(3000);
      for (angle = 90; angle >= 0; angle -= 1) {
        myservo.write(angle);
        delay(10);
      }
      delay(2000);
      lcd.setCursor(0, 1);
      memset(enteredPass, '\0', sizeof(enteredPass));
      lcd.clear();
      inputs = 0;
    }
    else{
      if(strlen(enteredPass) == 4){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incorrect !!");
        delay(1000);
        lcd.clear();
        lcd.print("Enter Password");
        lcd.setCursor(0, 1);
        // delay(1000);
        memset(enteredPass, '\0', sizeof(enteredPass));
        inputs = 0;
      }
    }
  }
}