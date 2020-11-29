/**
   @file Variable.h

   @brief Globalne premenne
   
   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "MCU_cfg.h"
#include "Communication.h"

extern ESP8266WebServer server;                 ///< globalny objekt pre WEB server

extern bool WebRequestForData;                  ///< 
extern uint8_t WebRequestForDataStateMachine;   ///< 


#endif

/* EOF */
