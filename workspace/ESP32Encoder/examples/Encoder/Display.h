#pragma once
#include <TFT_eSPI.h>  // Graphics and font library for ST7735 driver chip

#define REDROW_LIMIT 200

class Display {
private:
  int millsToRedraw = 0;
  int encoder_rotation = 0;
  String mode = "";
  bool changed = true;
  TFT_eSPI tft = TFT_eSPI();

  void draw();
  bool needRedraw();

public:
  Display();
  void process();
  void setEncoderRotation(int encoderRotation) {
    if (encoderRotation != encoder_rotation) {
      encoder_rotation = encoderRotation;
      changed = true;
    }
  };

  void setMode(String modestring) {
    mode = modestring;
    changed = true;
  };

 
};