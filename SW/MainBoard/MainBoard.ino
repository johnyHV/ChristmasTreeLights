#include "IR_Remote.h"
#include "Variable.h"
#include "MCU_cfg.h"
#include "RTC.h"
#include "LedEffect.h"
#include "Communication.h"
#include "Mcu_status.h"
#include "Button.h"

void setup() {
  Serial.begin(COM_PORT_BAUD_RATE);
  Serial.println(F("Start MCU"));

/* Software serial */
#if (BLUETOOTH_ENABLE == true)
  bluetooth.begin(BLUETOOTH_BAUD_RATE);
#elif (WIFI_ENABLE == true)
  wifi.begin(WIFI_BAUD_RATE);
  wifi.println(F("Start!"));
#endif

  /* initial I2C */
  Wire.begin();

  /* init LED strip */
  FastLED.addLeds<LED_TYPE, LED_STRIP_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  LED_BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;

  /* Init IR prijimaca */
#if (IR_REMOTE_ENABLE == true)
  IR_rx.enableIRIn();
#endif

  /* read RTC time */
  //RTC_printTime(RTC_readTime());
  time_now = RTC_readTime();
  RTC_printTime(time_now);

  /* init nastavenia Automatickeho zapinania */
  McuStatusAutoOnInit();

  /* init nastavenia efektov */
  McuStatusCurrentlyEfectInit();

  /* init tlacidla */
  ButtonInit();

  /* end configuration */
  Serial.println(F("MCU configuration done"));
}

void loop()
{
  /* obsluha IR prijimaca */
  IR_Scan();

  /* obsluha tlacidla */
  ButtonMain();

  /* obsluha komunikacie */
  CommunicationMain();

  /* obsluha LED pasu */
  LedEffect_main();

  /* refresh time */
  delay(LOOP_REFRESH_TIME);
}
