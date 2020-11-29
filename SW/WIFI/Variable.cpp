/**
   @file Variable.cpp

   @brief Globalne premenne
   
   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/


#include "Variable.h"

ESP8266WebServer server(WEB_SERVER_PORT);

bool WebRequestForData = false;
uint8_t WebRequestForDataStateMachine = 0;
