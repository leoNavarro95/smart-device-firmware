#include "DB_Manager.h"
#include <Arduino.h>

void DB_Manager_::begin() {
  pinMode(LED_BUILTIN, OUTPUT);

  // blink the led a few times
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void DB_Manager_::doStuff() {
  // blink the LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(800);
}

DB_Manager_ &DB_Manager_::getInstance() {
  static DB_Manager_ instance;
  return instance;
}

DB_Manager_ &DB = DB.getInstance();