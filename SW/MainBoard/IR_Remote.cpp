/**
   @file IR_Remote.cpp

   @brief praca s IR dialkovym ovladanim

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "IR_Remote.h"

/**

   @info Kniznica kontrolujuca stav IR prijimaca
   @param uint8_t - jas
   @return none
*/
uint8_t IR_Scan() {
#if (IR_REMOTE_ENABLE == true)
  decode_results results;

  if (IR_rx.decode(&results)) {
    IR_rx.printResultShort(&Serial);
    Serial.println();
    
    Serial.print(F("IR button HEX code: "));
    Serial.println(results.value, HEX);
    IR_rx.resume();
    IR_CheckButton(&results);
  }
#endif
}

/**

   @info Funkcia spracuvajuca prichadzajuci prikaz
   @param decode_results - prijaty prikaz
   @return none
*/
#if (IR_REMOTE_ENABLE == true)
void IR_CheckButton(decode_results *results) {
  switch (results->value) {
    case IR_REMOTE_BUTTON_0:
      Serial.println(F("Cislo 0, OFF"));
      
      break;
    case IR_REMOTE_BUTTON_1:
      Serial.println(F("Cislo 1, RED"));

      break;
    case IR_REMOTE_BUTTON_2:
      Serial.println(F("Cislo 2, GREEN"));

      break;
    case IR_REMOTE_BUTTON_3:
      Serial.println(F("Cislo 3, BLUE"));

      break;
    case IR_REMOTE_BUTTON_4:
      Serial.println(F("Cislo 4, WHITE"));

      break;
    case IR_REMOTE_BUTTON_5:
      Serial.println(F("Cislo 5, RGB"));

      break;
    case IR_REMOTE_BUTTON_6:
      Serial.println(F("Cislo 6, RGBW"));

      break;
    case IR_REMOTE_BUTTON_7:
      Serial.println(F("Cislo 7, YELLOW"));
 
      break;
    case IR_REMOTE_BUTTON_8:
      Serial.println(F("Cislo 8, PRESENT"));

      break;
    case IR_REMOTE_BUTTON_9:
      Serial.println(F("Cislo 9"));
      break;
    case IR_REMOTE_BUTTON_HASHTAG:
      Serial.println(F("Enable PIR!"));

      break;
    case IR_REMOTE_BUTTON_STAR:
      Serial.println(F("Disable PIR!"));

      break;
  }
}

#endif

/* EOF */
