/**
   @file Variable.cpp

   @brief Globalne premenne

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "Variable.h"

/* IR */
#if (IR_REMOTE_ENABLE == true)
IRrecv IR_rx(IR_RX_INPUT);
#endif

/* LEDS */
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
CRGBPalette16 myRedWhiteBluePalette;

/* RTC */
time_date time_now;

/* Software serial */
#if (BLUETOOTH_ENABLE == true)
SoftwareSerial bluetooth(BLE_RX, BLE_TX);
#elif (WIFI_ENABLE == true)
SoftwareSerial wifi(ESP_RX, ESP_TX);
#endif

struct ComDataCommandStruct ComDataCommandRx = {'\0', {'\0'}, 0};
struct ComDataCommandStruct ComDataCommandTx = {'\0', {'\0'}, 0};
