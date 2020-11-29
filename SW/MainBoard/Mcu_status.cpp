/**
   @file McuStatus.cpp

   @brief nastavenie MCU podla prikazov z WI-FI, a vycitanie aktualneho nastavenia MCU pre odoslanie do WI-FI modulu

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "Mcu_status.h"

struct McuStatus_CurrentlyEffect_Struct McuStatusCurrentlyEffect = {0, 0, 0};
struct McuStatus_AutoOn_Struct McuStatusAutoOn;

void McuStatusAutoOnInit() {
  McuStatusAutoOn.AutoOn_TimeOn.E_hour = EEPROM_AUTO_ON_TIME_ON_HOUR;
  McuStatusAutoOn.AutoOn_TimeOn.E_min = EEPROM_AUTO_ON_TIME_ON_MIN;
  McuStatusAutoOn.AutoOn_TimeOff.E_hour = EEPROM_AUTO_ON_TIME_OFF_HOUR;
  McuStatusAutoOn.AutoOn_TimeOff.E_min = EEPROM_AUTO_ON_TIME_OFF_MIN;

  RTC_LoadTimeFromEEPROM(&McuStatusAutoOn.AutoOn_TimeOn);
  RTC_LoadTimeFromEEPROM(&McuStatusAutoOn.AutoOn_TimeOff);
  McuStatusAutoOn.EnableAutoOn = EEPROM.read(EEPROM_AUTO_ON_STATUS);
  McuStatusAutoOn.Effect = EEPROM.read(EEPROM_AUTO_ON_EFFECT);

  McuStatusAutoOn.EnableAutoOnFlag = false;
}

void McuStatusCurrentlyEfectInit() {
  McuStatusCurrentlyEffect.Effect = EEPROM.read(EEPROM_CURRENT_EFFECT);
  McuStatusCurrentlyEffect.RefreshTime = McuStatusReadUint16ToEeprom(EEPROM_EFFECT_SPEED_HI, EEPROM_EFFECT_SPEED_LOW);
  McuStatusCurrentlyEffect.RandomTime = McuStatusReadUint16ToEeprom(EEPROM_RANDOM_TIME_HI, EEPROM_RANDOM_TIME_LOW);

  if (McuStatusCurrentlyEffect.Effect == LED_EFFECT_RANDOM) {
    McuStatusCurrentlyEffect.RandomEnable = true;
  } else {
    McuStatusCurrentlyEffect.RandomEnable = false;
  }

  RTC_ConvertSecondToTime(McuStatusCurrentlyEffect.RandomTime, &McuStatusCurrentlyEffect.RandomTimeInc);
  RTC_printTime(McuStatusCurrentlyEffect.RandomTimeInc);

  McuStatusCurrentlyEffect.RandomTimeRtc = time_now;
  RTC_IncrementTimeAt(McuStatusCurrentlyEffect.RandomTimeInc, &McuStatusCurrentlyEffect.RandomTimeRtc);
  Serial.print(F("Change effect: "));
  Serial.println(McuStatusCurrentlyEffect.Effect);
  RTC_printTime(time_now);
  RTC_printTime(McuStatusCurrentlyEffect.RandomTimeRtc);
}

void McuStatusSendCurrentTime() {
  RTC_printTime(time_now);
  ComDataCommandTx.command = COMMUNICATION_SET_TIME;
  McuStatusCopyTimeToCharArray(&ComDataCommandTx.variable[0], &time_now);

  ComDataCommandTx.variable_len = 8;

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusCopyTimeToCharArray(char *data, time_date *time) {
  sprintf(data, "%02d:%02d:%02d", time->hour, time->min, time->sec);
}

void McuStatusSendCurrentEffect() {
  McuStatusSendOneByteResponse(COMMUNICATION_SET_CURRENT_EFFECT, McuStatusCurrentlyEffect.Effect);
}

void McuStatusSendAutoOnStatus() {
  McuStatusSendOneByteResponse(COMMUNICATION_SET_AUTO_ON, (McuStatusAutoOn.EnableAutoOn == true) ? 'E' : 'D');
}

void McuStatusSendOneByteResponse(char command, char value) {
  ComDataCommandTx.command = command;
  ComDataCommandTx.variable[0] = value;
  ComDataCommandTx.variable_len = 1;

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusSendAutoOnEffect() {
  McuStatusSendOneByteResponse(COMMUNICATION_SET_AUTO_ON_EFFECT, McuStatusAutoOn.Effect);
}

void McuStatusSendAutoOnTimeOn() {

  ComDataCommandTx.command = COMMUNICATION_SET_AUTO_ON_TIME_ON;
  McuStatusCopyTimeToCharArray(&ComDataCommandTx.variable[0], &McuStatusAutoOn.AutoOn_TimeOn);
  ComDataCommandTx.variable_len = 8;

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusSendAutoOnTimeOff() {
  ComDataCommandTx.command = COMMUNICATION_SET_AUTO_ON_TIME_OFF;
  McuStatusCopyTimeToCharArray(&ComDataCommandTx.variable[0], &McuStatusAutoOn.AutoOn_TimeOff);
  ComDataCommandTx.variable_len = 8;

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusSendFirmware() {
  ComDataCommandTx.command = COMMUNICATION_SET_FIRMWARE_VERSION;
  strcpy(ComDataCommandTx.variable, SOFTWARE_VERSION);
  ComDataCommandTx.variable_len = strlen(SOFTWARE_VERSION);

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusSendEffectSpeed() {
  ComDataCommandTx.command = COMMUNICATION_SET_EFFECT_SPEED;
  ComDataCommandTx.variable_len = sprintf(ComDataCommandTx.variable, "%d", McuStatusCurrentlyEffect.RefreshTime);

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusSendRandomTime() {
  ComDataCommandTx.command = COMMUNICATION_SET_RANDOM_TIME;
  ComDataCommandTx.variable_len = sprintf(ComDataCommandTx.variable, "%d", McuStatusCurrentlyEffect.RandomTime);

  CommunicationSetConfigData(&ComDataCommandTx);
}

void McuStatusSetWifiIp(struct ComDataCommandStruct *data) {
  Serial.println("");
  Serial.print(F("IP: "));
  for (uint8_t i = 0; i < data->variable_len; i++) {
    Serial.print(data->variable[i]);
  }
  Serial.println("");
}

void McuStatusSetWifiSsid(struct ComDataCommandStruct *data) {
  Serial.println("");
  Serial.print(F("SSID: "));
  for (uint8_t i = 0; i < data->variable_len; i++) {
    Serial.print(data->variable[i]);
  }
  Serial.println("");
}

void McuStatusSetWifiStatus(struct ComDataCommandStruct *data) {
  Serial.print(F("Status: "));
  for (uint8_t i = 0; i < data->variable_len; i++) {
    Serial.print(data->variable[i]);
  }
  Serial.println("");
}

void McuStatusSetTime(struct ComDataCommandStruct *data) {
  Serial.println(F("SET TIME"));

  McuStatusParseTimeFromCharArray(data, &time_now);
  RTC_setTime(time_now);
  RTC_printTime(time_now);
}

void McuStatusSetEffect(struct ComDataCommandStruct *data) {
  Serial.print(F("SET effect: "));
  McuStatusCurrentlyEffect.Effect = data->variable[0];
  Serial.println(McuStatusCurrentlyEffect.Effect);

  if (McuStatusCurrentlyEffect.Effect == LED_EFFECT_RANDOM) {
    McuStatusCurrentlyEffect.RandomEnable = true;
  } else {
    McuStatusCurrentlyEffect.RandomEnable = false;
  }
  LedEffect();
  EEPROM.write(EEPROM_CURRENT_EFFECT, McuStatusCurrentlyEffect.Effect);
}

void McuStatusSetAutoOn(struct ComDataCommandStruct *data) {
  if (data->variable[0] == 'E') {
    McuStatusAutoOn.EnableAutoOn = true;
  } else {
    McuStatusAutoOn.EnableAutoOn = false;
  }
  Serial.print(F("Status autoOn: "));
  Serial.println(McuStatusAutoOn.EnableAutoOn);
  EEPROM.write(EEPROM_AUTO_ON_STATUS, McuStatusAutoOn.EnableAutoOn);
}

void McuStatusSetAutoOnEffect(struct ComDataCommandStruct *data) {
  McuStatusAutoOn.Effect = data->variable[0];
  Serial.print(F("Effect autoOn: "));
  Serial.println(McuStatusAutoOn.Effect);
  EEPROM.write(EEPROM_AUTO_ON_EFFECT, McuStatusAutoOn.Effect);
}

void McuStatusSetAutoOnTimeOn(struct ComDataCommandStruct *data) {
  Serial.println(F("SET TIME AUTO ON TIME ON"));

  McuStatusParseTimeFromCharArray(data, &McuStatusAutoOn.AutoOn_TimeOn);
  RTC_printTime(McuStatusAutoOn.AutoOn_TimeOn);
  RTC_SaveTimeToEEPROM(McuStatusAutoOn.AutoOn_TimeOn);
}

void McuStatusSetAutoOnTimeOff(struct ComDataCommandStruct *data) {
  Serial.println(F("SET TIME AUTO ON TIME OFF"));

  McuStatusParseTimeFromCharArray(data, &McuStatusAutoOn.AutoOn_TimeOff);
  RTC_printTime(McuStatusAutoOn.AutoOn_TimeOff);
  RTC_SaveTimeToEEPROM(McuStatusAutoOn.AutoOn_TimeOff);
}

void McuStatusSetEffectSpeed(struct ComDataCommandStruct *data) {
  Serial.println(F("SET EFFECT SPEED"));
  McuStatusCurrentlyEffect.RefreshTime = atoi(data->variable);

  if (McuStatusCurrentlyEffect.RefreshTime < 7) {
    McuStatusCurrentlyEffect.RefreshTime = 7;
  }

  McuStatusWriteUint16ToEeprom(EEPROM_EFFECT_SPEED_HI, EEPROM_EFFECT_SPEED_LOW, McuStatusCurrentlyEffect.RefreshTime);
}

void McuStatusSetRandomTime(struct ComDataCommandStruct *data) {
  Serial.println(F("SET RANDOM TIME"));
  McuStatusCurrentlyEffect.RandomTime = atoi(data->variable);

  if (McuStatusCurrentlyEffect.RandomTime < 1) {
    McuStatusCurrentlyEffect.RandomTime = 1;
  }

  McuStatusWriteUint16ToEeprom(EEPROM_RANDOM_TIME_HI, EEPROM_RANDOM_TIME_LOW, McuStatusCurrentlyEffect.RandomTime);

  RTC_ConvertSecondToTime(McuStatusCurrentlyEffect.RandomTime, &McuStatusCurrentlyEffect.RandomTimeInc);
  RTC_printTime(McuStatusCurrentlyEffect.RandomTimeInc);

  McuStatusCurrentlyEffect.RandomTimeRtc = time_now;
  RTC_IncrementTimeAt(McuStatusCurrentlyEffect.RandomTimeInc, &McuStatusCurrentlyEffect.RandomTimeRtc);
  Serial.print(F("Change effect: "));
  Serial.println(McuStatusCurrentlyEffect.Effect);
  RTC_printTime(time_now);
  RTC_printTime(McuStatusCurrentlyEffect.RandomTimeRtc);
}


void McuStatusParseTimeFromCharArray(struct ComDataCommandStruct *data, time_date *tmp) {
  uint8_t hours = 0;
  uint8_t mins = 0;
  uint8_t secs = 0;

  /* arduino BUG ? */
  sscanf(data->variable, "%02d", &hours);
  tmp->hour = hours;
  sscanf(data->variable, "%02d:%02d", &hours, &mins);
  tmp->min = mins;
  sscanf(data->variable, "%02d:%02d:%02d", &hours, &mins, &secs);
  tmp->sec = secs;

  Serial.print(F("Parse: "));
  Serial.print(tmp->hour);
  Serial.print(":");
  Serial.print(tmp->min);
  Serial.print(":");
  Serial.println(tmp->sec);
}

void McuStatusWriteUint16ToEeprom(uint8_t Address_HI, uint8_t Address_LO, uint16_t value) {
  uint8_t LO = value & 0x00FF;
  uint8_t HI = (value & 0xFF00) >> 8;

  EEPROM.write(Address_HI, HI);
  EEPROM.write(Address_LO, LO);

  Serial.print(F("EEPROM write uint16_t: "));
  Serial.print(HI);
  Serial.print(F(" - "));
  Serial.println(LO);
}

uint16_t McuStatusReadUint16ToEeprom(uint8_t Address_HI, uint8_t Address_LO) {
  uint8_t HI = EEPROM.read(Address_HI);
  uint8_t LO = EEPROM.read(Address_LO);

  uint16_t vystup = LO | (HI << 8);

  Serial.print(F("EEPROM read uint16_t: "));
  Serial.print(HI);
  Serial.print(F(" - "));
  Serial.print(LO);
  Serial.print(F(" -> "));
  Serial.println(vystup);

  return vystup;
}
