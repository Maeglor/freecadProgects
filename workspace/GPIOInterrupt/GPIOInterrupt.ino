#include <Arduino.h>
#include "GPIOInput.h"

// struct Button {
//   const uint8_t PIN;
//   uint32_t numberKeyPresses;
//   bool pressed;
// };

// Button button1 = { 35, 0, false };
// Button button2 = { 0, 0, false };

// void IRAM_ATTR isr(void* arg) {
//   Button* s = static_cast<Button*>(arg);
//   if (s->pressed)
//     return;

//   if (digitalRead(s->PIN) + digitalRead(s->PIN) + digitalRead(s->PIN) != 0)
//     return;

//   s->numberKeyPresses += 1;
//   s->pressed = true;
// }

// struct Encoder {
//   const uint8_t PIN_CLC;
//   const uint8_t PIN_DIR;
//   int number;
// };

// Encoder encoder1 = { 39, 38, 0 };

// int prev_clc = 0;
// void IRAM_ATTR isencoder(void* arg) {
//   Encoder* s = static_cast<Encoder*>(arg);

//   int clc = digitalRead(s->PIN_CLC);
//   if (prev_clc == clc)
//     return;

//   prev_clc = clc;

//   int dir = digitalRead(s->PIN_DIR);

//   if (clc == dir)
//     s->number -= 1;
//   else
//     s->number += 1;

//   Serial.printf("Encoder %d \n", s->number);
// }

void onButton0Click(){
     Serial.printf("onButton0Click level = %d \n", digitalRead(37));
}

Button button = {37, &onButton0Click};


void setup() {
  Serial.begin(115200);

  registerButton(&button);

  // pinMode(button1.PIN, INPUT_PULLUP);
  // attachInterruptArg(button1.PIN, isr, &button1, FALLING);

  // pinMode(button2.PIN, INPUT_PULLUP);
  // attachInterruptArg(button2.PIN, isr, &button2, FALLING);

  // pinMode(encoder1.PIN_CLC, INPUT_PULLUP);
  // pinMode(encoder1.PIN_DIR, INPUT);
  // attachInterruptArg(encoder1.PIN_CLC, isencoder, &encoder1, CHANGE);

  Serial.printf("init!!!");
}

void loop() {
  // if (button1.pressed) {
  //   Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
  //   button1.pressed = false;
  // }
  // if (button2.pressed) {
  //   Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
  //   button2.pressed = false;
  // }
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    // detachInterrupt(button1.PIN);
  }
}