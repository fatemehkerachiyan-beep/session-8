#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

long num1 = 0;
long num2 = 0;
char op = 0;
bool secondNum = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Simple Calculator");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == 'C') {
      num1 = num2 = 0;
      op = 0;
      secondNum = false;
      Serial.println("Cleared");
      return;
    }
    if (key >= '0' && key <= '9') {
      Serial.print(key);

      if (!secondNum)
        num1 = num1 * 10 + (key - '0');
      else
        num2 = num2 * 10 + (key - '0');
    }
    if (key == '+' or  key == '-' or  key == '*' or  key == '/'){
      op = key;
      secondNum = true;
      Serial.print(" ");
      Serial.print(op);
      Serial.print(" ");
    }
    if (key == '=') {
      long result = 0;

      if (op == '+') result = num1 + num2;
      if (op == '-') result = num1 - num2;
      if (op == '*') result = num1 * num2;
      if (op == '/') {
        if (num2 == 0) {
          Serial.println(" ERROR (Divide by 0)");
          return;
        }
        result = num1 / num2;
      }

      Serial.print(" = ");
      Serial.println(result);
      num1 = result;
      num2 = 0;
      secondNum = false;
    }
  }
}

