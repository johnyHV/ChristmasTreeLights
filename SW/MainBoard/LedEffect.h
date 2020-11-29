/**
   @file LedEffect.h

   @brief rozne efekty blikania s LED pasom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _LED_EFFECT_H_
#define _LED_EFFECT_H_

#include <FastLED.h>
#include "Variable.h"
#include "MCU_cfg.h"
#include "LedEffect_command.h"
#include "RTC.h"

extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

extern uint16_t LedEffectLoopCount;                             ///< premenna vdaka ktorej sa refreshuje main funkcia v pravidelnych intervaloch

void LedEffect_main();                                          ///< main funkcia pre obluhu efektov
void LedEffect();                                               ///< nastavenie efektu
void LedSetStripCollor(CRGB::HTMLColorCode);                    ///< nastavenie celeho pasu na jednu farbu
void LedEffectGetRandom();                                      ///< nahodne vygenerovanie efektu
void LedEffectIncrement();                                      ///< increment efektu pri stlaceni tlacidla

void LedEffectFillLEDsFromPaletteColors( uint8_t colorIndex);   ///< naplnenie LED pasu z palety
void LedEffectSetupTotallyRandomPalette();                      ///< vytvorenie uplne nahodnej palety
void LedEffectSetupBlackAndWhiteStripedPalette();               ///< nastavenie cierno bielej palety
void LedEffectSetupPurpleAndGreenPalette();                     ///< nastavenie ruzovo zelenej palety

#endif
