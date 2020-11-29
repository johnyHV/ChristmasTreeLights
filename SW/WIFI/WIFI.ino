#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "MCU_cfg.h"
#include "Variable.h"
#include "WebPage.h"
#include "Communication.h"

void setup(void) {
  Serial.begin(SERIAL_BAUD_RATE);

#if (DEBUG_CONSOLE == true)
  Serial.println("WIFI MCU START!");
#endif

  /* nastavenie WI-FI modu a pripojenie k WI-FI sieti */
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#if (DEBUG_CONSOLE == true)
    Serial.print(".");
#endif
  }

#if (DEBUG_CONSOLE == true)
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif
  WiFi.localIP();

  /* Start MDNS servera */
  if (MDNS.begin("esp8266")) {
#if (DEBUG_CONSOLE == true)
    Serial.println("MDNS responder started");
#endif
  }

  /* asocia podstranok k funkciam */
  server.on("/", WebPage_root);
  server.on("/effect", WebPage_setEffect);
  server.on("/setTime", WebPage_setTime);
  server.on("/json_input", WebPage_jsonInput);
  server.on("/autoOn", WebPage_setAutoOn);
  server.on("/autoOnEffect", WebPage_setAutoOnEffect);
  server.on("/autoOnTimeOn", WebPage_setAutoOnTimeOn);
  server.on("/autoOnTimeOff", WebPage_setAutoOnTimeOff);
  server.on("/setEffectSpeed", WebPage_setEffectSpeed);
  server.on("/setRandomTime", WebPage_setRandomTime);

  /* asociacia notfound stranky */
  server.onNotFound(WebPage_NotFound);

  /* start WEB servera */
  server.begin();
#if (DEBUG_CONSOLE == true)
  Serial.println("HTTP server started");
#endif
}

void loop(void) {
  /* hendlovanie WEB clienta */
  server.handleClient();

  /* aktualizacia MDNS */
  MDNS.update();

  /* aktualizacia komunikacie s MCU */
  CommunicationMain();

  /* main LOOP refresh time */
  delay(LOOP_REFRES_TIME);
}
