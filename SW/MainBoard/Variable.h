/**
   @file Variable.h

   @brief Globalne premenne

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef __VARIABLE_h_
#define __VARIABLE_h_

#include <FastLED.h>
#include <SoftwareSerial.h>
#include "IR_Remote_cfg.h"
#include "MCU_cfg.h"
#include "RTC.h"
#include "Communication.h"

/* IR */
# if (IR_REMOTE_ENABLE == true)
#include <IRremote.h>
extern IRrecv IR_rx;                                  ///< Objekt pre pracu s IR receiverom
#endif

/* LEDS */
extern CRGB leds[NUM_LEDS];                           ///< globalne pole s nastavenim farieb na celom LED pase
extern CRGBPalette16 currentPalette;                  ///< globalna paleta
extern TBlendType    currentBlending;                 ///< globalny blending
extern CRGBPalette16 myRedWhiteBluePalette;           ///< globalna vlastna paleta

/* TIME */
extern time_date time_now;                            ///< globalna strutura s aktualnym casom

/* Software serial */
#if (BLUETOOTH_ENABLE == true)
extern SoftwareSerial bluetooth;                      ///< SW serial interface pre komunikaciu s BLE modulom
#elif (WIFI_ENABLE == true)
extern SoftwareSerial wifi;                           ///< SW serial interface pre komunikaciu s WI-FI modulom
#endif

extern struct ComDataCommandStruct ComDataCommandRx;  ///< globalna struktura s 
extern struct ComDataCommandStruct ComDataCommandTx;

#endif
