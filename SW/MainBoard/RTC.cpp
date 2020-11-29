/**
   @file RTC.cpp

   @brief praca s RTC cipom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "RTC.h"

/**

   @info Nastavi cas na RTC
   @param time - struktura naplnena casom pre zapis
   @return void
*/
void RTC_setTimeUart(time_date *tmp, char *data) {
  bool read_tmp = true;
  int a[13] = {0};

  int i = 0;
  while (read_tmp) {

    if (Serial.available() > 0) {
      a[i] = Serial.read() - 48;
      i++;
      Serial.println(a[i]);
      Serial.println(i);
    }
    if (i == 13)
      read_tmp = false;
  }
  
  tmp->hour = a[0];
  tmp->min = a[2];
  tmp->sec = a[4];
  Serial.print(tmp->hour);
  Serial.print(":");
  Serial.print(tmp->min);
  Serial.print(":");
  Serial.println(tmp->sec);

  
}

/**

   @info Nastavi cas na RTC
   @param time - struktura naplnena casom pre zapis
   @return void
*/
void RTC_setTime(time_date times) {
  Wire.begin();
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(RTC_decToBcd(times.sec));
  Wire.write(RTC_decToBcd(times.min));
  Wire.write(RTC_decToBcd(times.hour));
  Wire.write(RTC_decToBcd(times.week_day));
  Wire.write(RTC_decToBcd(times.month_day));
  Wire.write(RTC_decToBcd(times.month));
  Wire.write(RTC_decToBcd(times.year));
  Wire.write(byte(0));
  Wire.endTransmission();
}

/**

   @info Vycita cas z RTC
   @param
   @return void
*/
time_date RTC_readTime() {
  Wire.begin();
  time_date times = {0, 0, 0, 0, 0, 0, 0};
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  times.sec = RTC_bcdToDec(Wire.read());
  times.min = RTC_bcdToDec(Wire.read());
  times.hour = RTC_bcdToDec(Wire.read());
  times.week_day = RTC_bcdToDec(Wire.read());
  times.month_day = RTC_bcdToDec(Wire.read());
  times.month = RTC_bcdToDec(Wire.read());
  times.year = RTC_bcdToDec(Wire.read());
  return times;
}

/**

   @info Vypise cas na konzolu
   @param none
   @return void
*/
void RTC_printTime(time_date times) {
  Serial.print(F("Date & time: "));
  Serial.print(times.month_day);
  Serial.print(" ");
  Serial.print(times.month_day);
  Serial.print(".");
  Serial.print(times.month);
  Serial.print(".");
  Serial.print(times.year);
  Serial.print(" ");
  Serial.print(times.hour);
  Serial.print(":");
  Serial.print(times.min);
  Serial.print(":");
  Serial.print(times.sec);
  Serial.println();
}

void RTC_SaveTimeToEEPROM(time_date input) {
  EEPROM.write(input.E_hour, input.hour);
  EEPROM.write(input.E_min, input.min);
}

void RTC_LoadTimeFromEEPROM(time_date *input) {
  input->hour = EEPROM.read(input->E_hour);
  input->min = EEPROM.read(input->E_min);
}

bool RTC_CheckEqualTime(time_date last_time) {
  time_date now_time = RTC_readTime();

  if ((last_time.hour == now_time.hour) && (last_time.min == now_time.min)) {
    return true;
  } else {
    return false;
  }
}

bool RTC_CheckEqualTimeSecond(time_date last_time) {
  time_date now_time = RTC_readTime();

  if ((last_time.hour == now_time.hour) && (last_time.min == now_time.min) && (last_time.sec == now_time.sec)) {
    return true;
  } else {
    return false;
  }
}

bool RTC_CheckTimeMoreThat(time_date last_time) {
  time_date now_time = RTC_readTime();

  if ((last_time.hour >= now_time.hour) && (last_time.min >= now_time.min) && (last_time.sec >= now_time.sec)) {
    return true;
  } else {
    return false;
  }
}

bool RTC_CheckTimeLessThat(time_date last_time) {
  time_date now_time = RTC_readTime();

  if ((last_time.hour <= now_time.hour) && (last_time.min <= now_time.min) && (last_time.sec <= now_time.sec)) {
    return true;
  } else {
    return false;
  }
}

void RTC_IncrementTimeAt(time_date increment, time_date *out) {
  /* second */
  if (( out->sec + increment.sec) > 59) {

    out->sec = increment.sec - (59 - out->sec ) - 1;
    /* min */
    if ((out->min + 1) > 59) {

      out->min = increment.min - (59 - out->min) - 1;
      /* hour */
      if ((out->hour + 1) > 23) {
        out->hour = 0;
      } else {
        out->hour += 1;
      }
    } else {
      out->min += 1;
    }
  } else {
    out->sec += increment.sec;
  }

  /* min */
  if ((out->min + increment.min) > 59) {

    out->min = increment.min - (59 - out->min) - 1;
    /* hour */
    if ((out->hour + 1) > 23) {
      out->hour = 0;
    } else {
      out->hour += 1;
    }
  } else {
    out->min += increment.min;
  }

  /* hour */
  if ((out->hour + increment.hour) > 23) {
    out->hour = 0;
  } else {
    out->hour += increment.hour;
  }
}

void RTC_ConvertSecondToTime(uint16_t second, time_date *times) {
  times->hour = second / 3600;
  times->min = (second - (times->hour * 3600)) / 60;
  times->sec = (second - (times->hour * 3600) - (times->min * 60)) / 1;
}

/**

   @info Dec to Bcd
   @param hodnota
   @return byte
*/
byte RTC_decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

/**

   @info Bcd to Dec
   @param hodnota
   @return byte
*/
byte RTC_bcdToDec(byte val) {
  return ((val / 16 * 10) + (val % 16));
}
