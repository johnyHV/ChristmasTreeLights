/**
   @file LedEffect.cpp

   @brief rozne efekty blikania s LED pasom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "LedEffect.h"

uint16_t LedEffectLoopCount = 0;

void LedEffect_main() {
  LedEffectLoopCount++;

  if (LedEffectLoopCount > McuStatusCurrentlyEffect.RefreshTime) {
    time_now = RTC_readTime();
    LedEffect();
    LedEffectLoopCount = 0;
  }
}

void LedEffect() {

  /* kontrola automaticke zapnutia / vypnutia */
  if (McuStatusAutoOn.EnableAutoOn == true) {

    /* ON TIME */
    if ((RTC_CheckTimeLessThat(McuStatusAutoOn.AutoOn_TimeOn) == true) && (McuStatusCurrentlyEffect.Effect == LED_EFFECT_OFF) && (McuStatusAutoOn.EnableAutoOnFlag == false)) {
      McuStatusCurrentlyEffect.Effect = McuStatusAutoOn.Effect;

      if (McuStatusAutoOn.Effect == LED_EFFECT_RANDOM) {
        McuStatusCurrentlyEffect.RandomEnable = true;
      } else {
        McuStatusCurrentlyEffect.RandomEnable = false;
      }

      McuStatusAutoOn.EnableAutoOnFlag = true;
    } else {
      McuStatusAutoOn.EnableAutoOnFlag = false;
    }

    /* OFF time */
    if (RTC_CheckTimeLessThat(McuStatusAutoOn.AutoOn_TimeOff) == true) {
      McuStatusCurrentlyEffect.Effect = LED_EFFECT_OFF;
    }
  }

  /* kontrola a zapnutie RANDOM efektu */
  if (McuStatusCurrentlyEffect.RandomEnable) {
    if ((RTC_CheckEqualTimeSecond(McuStatusCurrentlyEffect.RandomTimeRtc) == true) && (McuStatusCurrentlyEffect.RandomChange == false)) {
      LedEffectGetRandom();
      McuStatusCurrentlyEffect.RandomChange = true;
      RTC_IncrementTimeAt(McuStatusCurrentlyEffect.RandomTimeInc, &McuStatusCurrentlyEffect.RandomTimeRtc);
      Serial.print(F("Change effect: "));
      Serial.println(McuStatusCurrentlyEffect.Effect);
      RTC_printTime(time_now);
      RTC_printTime(McuStatusCurrentlyEffect.RandomTimeRtc);
    } else {
      McuStatusCurrentlyEffect.RandomChange = false;
    }
  }

  /* nastavenie fektu */ /* HeatColors_p */
  switch (McuStatusCurrentlyEffect.Effect) {
    case LED_EFFECT_OFF:
      LedSetStripCollor(CRGB::Black);
      break;
    case LED_EFFECT_RED:
      LedSetStripCollor(CRGB::Green);
      break;
    case LED_EFFECT_GREEN:
      LedSetStripCollor(CRGB::Red);
      break;
    case LED_EFFECT_BLUE:
      LedSetStripCollor(CRGB::Blue);
      break;
    case LED_EFFECT_WHITE:
      LedSetStripCollor(CRGB::White);
      break;
    case LED_EFFECT_YELLOW:
      LedSetStripCollor(CRGB::Yellow);
      break;
    case LED_EFFECT_COLLOR_SPECTRUM:
      currentPalette = RainbowColors_p;
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_COLOR_SNAKE:
      currentPalette = RainbowStripeColors_p;
      currentBlending = NOBLEND;
      break;
    case LED_EFFECT_COLOR_SNAKE_FULL:
      currentPalette = RainbowStripeColors_p;
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_RED_BLUE_SNAKE:
      LedEffectSetupPurpleAndGreenPalette();
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_5:
      LedEffectSetupTotallyRandomPalette();
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_WHITE_SNAKE:
      LedEffectSetupBlackAndWhiteStripedPalette();
      currentBlending = NOBLEND;
      break;
    case LED_EFFECT_7:
      LedEffectSetupBlackAndWhiteStripedPalette();
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_8:
      currentPalette = CloudColors_p;
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_9:
      currentPalette = PartyColors_p;
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_10:
      currentPalette = myRedWhiteBluePalette_p;
      currentBlending = NOBLEND;
      break;
    case LED_EFFECT_11:
      currentPalette = myRedWhiteBluePalette_p;
      currentBlending = LINEARBLEND;
      break;
    case LED_EFFECT_LAVA:
      currentPalette = LavaColors_p;
      currentBlending = NOBLEND;
      break;
    case LED_EFFECT_OCEAN:
      currentPalette = OceanColors_p;
      currentBlending = NOBLEND;
      break;
    case LED_EFFECT_FOREST:
      currentPalette = ForestColors_p;
      currentBlending = NOBLEND;
      break;
  }

  static uint8_t startIndex = 10;
  startIndex = startIndex + 1; /* motion speed */
  LedEffectFillLEDsFromPaletteColors(startIndex);
  FastLED.show();
}

void LedSetStripCollor(CRGB::HTMLColorCode input) {
  fill_solid( currentPalette, 16, input);
}

void LedEffectGetRandom() {
  if (random(0, 1)) {
    McuStatusCurrentlyEffect.Effect = random(LED_EFFECT_OFF, LED_EFFECT_RED_BLUE_SNAKE);
  } else {
    McuStatusCurrentlyEffect.Effect = random(LED_EFFECT_5, LED_EFFECT_FOREST);
  }
}

void LedEffectIncrement() {
  if (McuStatusCurrentlyEffect.Effect <= LED_EFFECT_RED_BLUE_SNAKE) {
    McuStatusCurrentlyEffect.Effect++;
  } else {
    if (McuStatusCurrentlyEffect.Effect <= LED_EFFECT_RANDOM) {
      McuStatusCurrentlyEffect.Effect++;
    } else {
      McuStatusCurrentlyEffect.Effect = LED_EFFECT_OFF;
    }
  }

  if (McuStatusCurrentlyEffect.RandomEnable == true) {

    McuStatusCurrentlyEffect.Effect = LED_EFFECT_OFF;
    McuStatusCurrentlyEffect.RandomEnable = false;
  } else {
    if (McuStatusCurrentlyEffect.Effect == LED_EFFECT_RANDOM) {
      McuStatusCurrentlyEffect.RandomEnable = true;
      McuStatusCurrentlyEffect.RandomTimeRtc = time_now;
      RTC_IncrementTimeAt(McuStatusCurrentlyEffect.RandomTimeInc, &McuStatusCurrentlyEffect.RandomTimeRtc);
    } else {
      McuStatusCurrentlyEffect.RandomEnable = false;
    }
  }
  
  EEPROM.write(EEPROM_CURRENT_EFFECT, McuStatusCurrentlyEffect.Effect);
}

void LedEffectFillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

// This function fills the palette with totally random colors.
void LedEffectSetupTotallyRandomPalette()
{
  for ( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void LedEffectSetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void LedEffectSetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};



// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.
