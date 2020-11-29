/**
   @file CommunicationConversion.cpp

   @brief konverzia prichadzajucich prikazov do zrozumitelnych textov

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "CommunicationConversion.h"

void CommunicationConversion_BoolTranslate(struct ComDataCommandStruct *input) {
  char tmp[10];
  switch (input->variable[0]) {
    case 'E':
      input->variable_len = sprintf(input->variable, "%s", "Zapnute");
      break;
    case 'D':
      input->variable_len = sprintf(input->variable, "%s", "Vypnute");
      break;
    default:
      input->variable_len = sprintf(input->variable, "%s", "ERROR");
      break;
  }
}

void CommunicationConversion_Effect(struct ComDataCommandStruct *input) {
  switch (input->variable[0]) {
    case LED_EFFECT_OFF:
      input->variable_len = sprintf(input->variable, "%s", "OFF");
      break;
    case LED_EFFECT_RED:
      input->variable_len = sprintf(input->variable, "%s", "Cervena");
      break;
    case LED_EFFECT_GREEN:
      input->variable_len = sprintf(input->variable, "%s", "Zelena");
      break;
    case LED_EFFECT_BLUE:
      input->variable_len = sprintf(input->variable, "%s", "Modra");
      break;
    case LED_EFFECT_WHITE:
      input->variable_len = sprintf(input->variable, "%s", "Biela");
      break;
    case LED_EFFECT_YELLOW:
      input->variable_len = sprintf(input->variable, "%s", "Zlta");
      break;
    case LED_EFFECT_COLLOR_SPECTRUM:
      input->variable_len = sprintf(input->variable, "%s", "Farebne spektrum");
      break;
    case LED_EFFECT_COLOR_SNAKE:
      input->variable_len = sprintf(input->variable, "%s", "Farebny hadik");
      break;
    case LED_EFFECT_COLOR_SNAKE_FULL:
      input->variable_len = sprintf(input->variable, "%s", "Farebny hadik 2");
      break;
    case LED_EFFECT_RED_BLUE_SNAKE:
      input->variable_len = sprintf(input->variable, "%s", "Cerveno modry hadik");
      break;
    case LED_EFFECT_5:
      input->variable_len = sprintf(input->variable, "%s", "Party");
      break;
    case LED_EFFECT_WHITE_SNAKE:
      input->variable_len = sprintf(input->variable, "%s", "Biely hadik");
      break;
    case LED_EFFECT_7:
      input->variable_len = sprintf(input->variable, "%s", "Biely hadik 2");
      break;
    case LED_EFFECT_8:
      input->variable_len = sprintf(input->variable, "%s", "Efekt 8");
      break;
    case LED_EFFECT_9:
      input->variable_len = sprintf(input->variable, "%s", "Efekt 9");
      break;
    case LED_EFFECT_10:
      input->variable_len = sprintf(input->variable, "%s", "Efekt 10");
      break;
    case LED_EFFECT_11:
      input->variable_len = sprintf(input->variable, "%s", "Efekt 11");
      break;
    case LED_EFFECT_LAVA:
      input->variable_len = sprintf(input->variable, "%s", "Lava");
      break;
    case LED_EFFECT_OCEAN:
      input->variable_len = sprintf(input->variable, "%s", "Ocean");
      break;
    case LED_EFFECT_FOREST:
      input->variable_len = sprintf(input->variable, "%s", "Forest");
      break;
    case LED_EFFECT_RANDOM:
      input->variable_len = sprintf(input->variable, "%s", "Nahodny efekt");
      break;
    default:
      input->variable_len = sprintf(input->variable, "%s - %s", "ERROR", input->variable);
      break;
  }
}
