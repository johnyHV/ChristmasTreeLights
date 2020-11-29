/**
   @file Button.h

   @brief praca s tlacidlom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Variable.h"
#include "MCU_cfg.h"
#include "Communication_command.h"
#include "LedEffect.h"
#include "Mcu_status.h"

#define BUTTON_DELAY    50          ///< time pre ochranu proti zakmitu
#define BUTTON_EVENT    false       ///< poloha tlacidla pre aktivaciu

struct ButtonState_struct {
  int buttonState;                  ///< aktualny stav tlacidla
  int lastButtonState;              ///< posledny stav tlacidla
  
  unsigned long lastDebounceTime;   ///< debounce time
};

extern struct ButtonState_struct ButtonState;

void ButtonInit();                  ///< inicializacia tlacidla a STATUS LED diody
void ButtonMain();                  ///< main funkcia pre obsluhu tlacidla
bool ButtonCheckChange();           ///< kontrola zmeny tlacidla

#endif
