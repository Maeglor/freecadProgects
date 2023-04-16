#include "ESP32Encoder.h"
#include "Display.h"
#include "StepperMotor.h"
#include "Mode.h"

Display display = Display();

StepperMotor  stepperMotor = StepperMotor(32,33,37);

ESP32Encoder encoder;
ESP32Encoder encoder2;

// timer and flag for example, not needed for encoders
unsigned long encoder2lastToggled;
bool encoder2Paused = false;

void resetMotor();

Mode mode = Mode(&resetMotor);


void resetMotor(){
  stepperMotor.reset();
  encoder.clearCount();
  display.setMode(mode.getModeString());
};


void setup() {

  Serial.begin(115200);
  // Enable the weak pull down resistors
  ESP32Encoder::useInternalWeakPullResistors = true;


  // set starting count value
  encoder.clearCount();

  // clear the encoder's raw count and set the tracked count to zero
  encoder2.clearCount();


  Serial.println("Encoder Start = " + String((int32_t)encoder.getCount()));

  // Attache pins for use as encoder pins
  encoder.attachHalfQuad(21, 22);
  // Attache pins for use as encoder pins
  encoder2.attachHalfQuad(38, 39);

  // set the lastToggle
  encoder2lastToggled = millis();
}
int32_t encoder1Count = -1;
int32_t encoder2Count = -1;

#define TO_DEG 1200 / 360

void loop() {
  // Loop and read the count
  int32_t encoder1Val = encoder.getCount();
  mode.setMode(encoder2.getCount());
  display.setEncoderRotation(abs((int)(((double)encoder1Val / 1200.0) * 360) % 360) - 180);


  stepperMotor.setTargetPosition((encoder1Val/3)/mode.getModeDivider());
  stepperMotor.process();

  display.process();
}

