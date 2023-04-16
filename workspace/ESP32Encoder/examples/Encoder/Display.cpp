#include "esp32-hal.h"
#include "Display.h"


Display::Display() {
  tft.init();
  tft.setRotation(1);


  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextFont(4);
}

bool Display::needRedraw() {
  if (millsToRedraw > millis())
    return false;

  millsToRedraw = millis() + REDROW_LIMIT;

  if (changed) {
    changed = false;
    return true;
  }

  return false;
}

void Display::draw() {
  tft.setCursor(0, 0);
  tft.println("Rotation " + String(encoder_rotation) + "          ");
  tft.println("Mode "+mode+"           ");
}

void Display::process() {
  if (needRedraw())
    draw();
}