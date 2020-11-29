/**
   @file WebPage.h

   @brief funkcie pre spracovanie prikazov z WEB stranky
   
   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _WEB_PAGE_H_
#define _WEB_PAGE_H_

#include "MCU_cfg.h"
#include "Variable.h"
#include "WebPage_root.h"
#include "Communication.h"

/* struktura s datami pre JSON */
struct JsonDataStruct {
  String time;                                                ///< aktualny cas
  String effect;                                              ///< aktualny efekt
  String autoOn;                                              ///< zapnute/vypnute automaticke zapinanie
  String autoOnEffect;                                        ///< efekt pri automatickom zapnut
  String autoOnTimeOn;                                        ///< cas automatickeho zapnutia
  String autoOnTimeOff;                                       ///< cas automatickeho vypnutia
  String Firmware;                                            ///< verzia firmware MCU
  String EffectSpeed;                                         ///< rychlost efektov
  String RandomTime;                                          ///< rychlost obnovy efektu pri RANDOM efektoch
  String FirmwareWifi;                                        ///< verzia firmware v WI-FI
};

extern struct JsonDataStruct WebPage_jsonData;                ///< struktura s nastavenim vsetkych udajov pre JSON spravu
extern struct ComDataCommandStruct WebPage_SettingsMessage;   ///< struktura s prichadzajucim/odchadzajucim prikazom a hodnotou pren

void WebPage_root();                                          ///< home page
void WebPage_setEffect();                                     ///< nastavenie aktualneho efektua odoslanie do MCU
void WebPage_setTime();                                       ///< nastavenie aktualneho casu a odoslanie do MCU
void WebPage_jsonInput();                                     ///< request o JSON data
void WebPage_NotFound();                                      ///< nenajdena stranka
void WebPage_setAutoOn();                                     ///< nastavenie automatickeho zapinania a odoslanie do MCU
void WebPage_setAutoOnEffect();                               ///< nastavenie fektu pri automatickom zapinani a odoslanie do MCU
void WebPage_setAutoOnTimeOn();                               ///< nastavenie casu automatickeho zapinania a odoslanie do MCU
void WebPage_setAutoOnTimeOff();                              ///< nastavenie casu automatickeho vypinania a odoslanie do MCU
void WebPage_setEffectSpeed();                                ///< nastavenie rychlosti efektov a odoslanie do MCU
void WebPage_setRandomTime();                                 ///< nastavenie rychlosti zmeny efektu pri RANDOM efektoch a odoslanie do MCU

void WebPage_DebugIncommingData();                            ///< debug pre prichazajuce data z WEB rozhrania

void WebPage_SendJsonData();                                  ///< funkcia pre odoslanie JSON dat WEB stranke
void WebPage_ClearJsonData();                                 ///< funkcia pre vycistenie JSON dat

void WebPage_SendResponse(bool);                              ///< odoslanie potvrdenia prijatej spravy naspet WEB stranke + informacia o uspesnosti nastavenia

#endif

/* EOF */
