/**
   @file Button.cpp

   @brief praca s tlacidlom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "Button.h"

struct ButtonState_struct ButtonState;

void ButtonInit() {
  pinMode(BUTTON_MODE, INPUT);
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);

  ButtonState.lastButtonState = !BUTTON_EVENT;
  ButtonState.lastDebounceTime = 0;
}

void ButtonMain() {
  if (ButtonCheckChange() == true) {

    Serial.println(F("BUTTON"));
    LedEffectIncrement();
  }
}

bool ButtonCheckChange() {
  bool ret = false;
  int reading = digitalRead(BUTTON_MODE);

  if (reading != ButtonState.lastButtonState) {
    ButtonState.lastDebounceTime = millis();
  }

  if ((millis() - ButtonState.lastDebounceTime) > BUTTON_DELAY) {

    if (reading != ButtonState.buttonState) {
      ButtonState.buttonState = reading;

      if (ButtonState.buttonState == BUTTON_EVENT) {
        digitalWrite(STATUS_LED, HIGH);
        ret = true;
      } else {
        digitalWrite(STATUS_LED, LOW);
      }
    }
  }

  ButtonState.lastButtonState = reading;
  return ret;
}
