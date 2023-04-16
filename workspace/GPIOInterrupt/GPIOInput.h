#include <Arduino.h>

// typedef void (*intFuncPtr)(int*);
// typedef void (*voidFuncDef)(void);

typedef struct  {
  const uint8_t PIN;
  void (*onClick)(void);  
} Button ;

// extern void registerButton(Button* button);



void IRAM_ATTR onGPIOButtonClick(void* arg) {
  Button* button = (Button*)arg;
  if (digitalRead(button->PIN) + digitalRead(button->PIN) + digitalRead(button->PIN) != 0)
    return;

  button->onClick();
}


extern void registerButton(Button* button){

 pinMode(button->PIN, INPUT_PULLUP);
 attachInterruptArg(button->PIN, onGPIOButtonClick, button, CHANGE);

  
}


typedef struct {
  const uint8_t PIN_CLC;
  const uint8_t PIN_DIR;
  int maxNumber;
  int minNumber;
  int currentNumber;
  void (*onValueChanged)(int);
  int previousLevel; // set to 0
} Encoder;


void IRAM_ATTR onGPIOEncoderStep(void* arg) {
  Encoder* encoder = (Encoder*)arg;

  int clc = digitalRead(encoder->PIN_CLC);
  if (encoder->previousLevel == clc)
    return;

  encoder->previousLevel = clc;

  int dir = digitalRead(encoder->PIN_DIR);

  if (clc == dir)
    if(encoder->currentNumber > encoder->minNumber){
      encoder->currentNumber -= 1;
      encoder->onValueChanged(encoder->currentNumber);
    }
  else
    if(encoder->currentNumber < encoder->maxNumber){
        encoder->currentNumber += 1;
        encoder->onValueChanged(encoder->currentNumber);
    }
}

extern void registerEncoder(Encoder* encoder){


  pinMode(encoder->PIN_CLC, INPUT_PULLUP);
  pinMode(encoder->PIN_DIR, INPUT);
  attachInterruptArg(encoder1.PIN_CLC, onGPIOEncoderStep, encoder, CHANGE);

}


