/**
   @file RTC.h

   @brief praca s RTC cipom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef __RTC_H_
#define __RTC_H_

#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>

/* struktura pre cas z RTC */
struct time_date {
    uint8_t hour;                                       ///< hodiny
    uint8_t min;                                        ///< minuty
    uint8_t sec;                                        ///< sekundy

    uint8_t week_day;                                   ///< den v tyzdni
    uint8_t month_day;                                  ///< den v mesiaci
    uint8_t month;                                      ///< mesiac
    uint8_t year;                                       ///< rok
    
    uint8_t E_hour;                                     ///< adresa ulozenia v EEPROM
    uint8_t E_min;                                      ///< adresa ulozenia v EEPROM
};

const int DS1307 = 0x68;                                ///< Address of DS1307 see data sheets

// const char* days[] ={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// const char* months[] ={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


void RTC_setTime(time_date);                            ///< nastavenie casu v RTC cipe
void RTC_setTimeUart(time_date *tmp, char *data);       ///< nastavenie casu z UART rozhrania
time_date RTC_readTime();                               ///< vycitanie casu z RTC cipu
void RTC_printTime(time_date);                          ///< vypisanie casu do UART rozhrania

void RTC_SaveTimeToEEPROM(time_date);                   ///< ulozenie casu do EEPROM pamete
void RTC_LoadTimeFromEEPROM(time_date*);                ///< vycitanie casu z EEPROM pamete

bool RTC_CheckEqualTime(time_date);                     ///< kontrola, ci vstupny cas je rovnaky s aktualnym casom. HH,MM
bool RTC_CheckEqualTimeSecond(time_date);               ///< kontrola, ci vstupny cas je rovnaky s aktualnym casom. HH,MM,SS
bool RTC_CheckTimeMoreThat(time_date);                  ///< kontrola, ci vstupny cas je vecsi ako aktualny cas
bool RTC_CheckTimeLessThat(time_date);                  ///< kontrola, ci vstupny cas je mensi ako aktualny cas
void RTC_IncrementTimeAt(time_date, time_date*);        ///< inkrementovanie druheho casu, o hodnotu z prveho casu
void RTC_ConvertSecondToTime(uint16_t, time_date*);     ///< konverzia sekund do hodin, minut, sekund

byte RTC_decToBcd(byte val);                            ///< konverzia DEC na BCD
byte RTC_bcdToDec(byte val);                            ///< konverzia BCD na DEC

#endif
