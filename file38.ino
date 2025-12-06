#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String password = "1346";
String input = "";
int led = 13;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  Serial.println("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print(key);
    if (key == '*') {
      input = "";
      Serial.println("\nCleared");
      return;
    }
    if (key == '#') {
      if (input == password) {
        Serial.println("\nCorrect!");
        digitalWrite(led, HIGH);
      } else {
        Serial.println("\nWrong!");
        digitalWrite(led, LOW);
      }
      input = "";
      return;
    }
    input += key;
  }
}

