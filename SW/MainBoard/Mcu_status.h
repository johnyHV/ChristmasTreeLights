/**
   @file McuStatus.h

   @brief nastavenie MCU podla prikazov z WI-FI, a vycitanie aktualneho nastavenia MCU pre odoslanie do WI-FI modulu

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef __MCU_status_h_
#define __MCU_status_h_

#include "Variable.h"
#include "MCU_cfg.h"
#include "RTC.h"
#include "LedEffect_command.h"
#include "Communication.h"

/* struktura s aktualnym nastavenim efektov */
struct McuStatus_CurrentlyEffect_Struct {
  uint8_t Effect;                                               ///< cislo efektu
  
  uint16_t RefreshTime;                                         ///< Ako rychlo maju blikat LED-ky
  
  uint16_t RandomTime;                                          ///< ako dlho ma fungovat jeden random efekt
  bool RandomEnable;                                            ///< zapnutie/vypnutie RANDOM vyberu efektu
  struct time_date RandomTimeInc;                               ///< Cas o ktory sa zmeni dalsi efekt
  struct time_date RandomTimeRtc;                               ///< Cas kedy sa zmeni dalsi efekt
  bool RandomChange;                                            ///< potvrdenie, ze efekt uz bol zmeneny.
};

/* struktura s nastavenim automatickeho zapinania */
struct McuStatus_AutoOn_Struct {
  bool EnableAutoOn;                                            ///< Automaticke zapinanie efektov
  bool EnableAutoOnFlag;                                        ///< Flag o tom, ze uz bol stromcek zapnuty
  uint8_t Effect;                                               ///< Efekt pri automatickom zapnuti
  struct time_date AutoOn_TimeOn;                               ///< Cas automatickeho zapnutia
  struct time_date AutoOn_TimeOff;                              ///< Cas automatickeho vypnutia
};

extern struct McuStatus_CurrentlyEffect_Struct McuStatusCurrentlyEffect;
extern struct McuStatus_AutoOn_Struct McuStatusAutoOn;

void McuStatusAutoOnInit();                                     ///< Inicializacia struktury automaticke zapinania
void McuStatusCurrentlyEfectInit();                             ///< Inicializacia struktury pre nastavenie aktualneho efektu

void McuStatusSendCurrentTime();                                ///< Odoslanie aktualneho casu
void McuStatusCopyTimeToCharArray(char*, time_date*);           ///< Kopirovanie casu do char pola
void McuStatusSendCurrentEffect();                              ///< Odoslanie aktualneho efektu
void McuStatusSendAutoOnStatus();                               ///< odoslanie stavu automatickeho zapnutia
void McuStatusSendOneByteResponse(char, char);                  ///< Odoslanie jedneho bajtu ako odpovede
void McuStatusSendAutoOnEffect();                               ///< odoslanie efektu pri auto ON funkcii
void McuStatusSendAutoOnTimeOn();                               ///< odoslanie casu aktivacie auto ON funkcie
void McuStatusSendAutoOnTimeOff();                              ///< odoslanie casu deaktivacie auto ON funkcie
void McuStatusSendFirmware();                                   ///< odoslanie FW verzie v MCU
void McuStatusSendEffectSpeed();                                ///< odoslanie rychlosti zmeny efektu
void McuStatusSendRandomTime();                                 ///< odoslanie casu ako casto sa ma menit random efekt

void McuStatusSetWifiIp(struct ComDataCommandStruct *);         ///< nastavenie aktualnej WI-FI IP
void McuStatusSetWifiSsid(struct ComDataCommandStruct *);       ///< nastavenie SSID WI-FI siete
void McuStatusSetWifiStatus(struct ComDataCommandStruct *);     ///< nastavenie WI-FI statusu
void McuStatusSetTime(struct ComDataCommandStruct *);           ///< nastavenie casu
void McuStatusSetEffect(struct ComDataCommandStruct *);         ///< nastavenie efektu
void McuStatusSetAutoOn(struct ComDataCommandStruct *);         ///< nastavenie automatickeho zapinania
void McuStatusSetAutoOnEffect(struct ComDataCommandStruct *);   ///< nastavenie efektu pri automatickom zapnuti
void McuStatusSetAutoOnTimeOn(struct ComDataCommandStruct *);   ///< nastavenie casu automatickeho zapnutia
void McuStatusSetAutoOnTimeOff(struct ComDataCommandStruct *);  ///< nastavenie casu automatickeho vypnutia
void McuStatusSetEffectSpeed(struct ComDataCommandStruct *);    ///< nastavenie rychlosti efektov
void McuStatusSetRandomTime(struct ComDataCommandStruct *);     ///< nastavenie casu ako casto sa ma menit RANDOM efekt

void McuStatusParseTimeFromCharArray(struct ComDataCommandStruct *, time_date*);  ///< vyparsovanie casu z prijateho ramca

void McuStatusWriteUint16ToEeprom(uint8_t, uint8_t, uint16_t);  ///< zapis 16bit premennej do EEPROM pamete
uint16_t McuStatusReadUint16ToEeprom(uint8_t, uint8_t);         ///< vycitanie 16bit premennej z EEPROM pamete

#endif
