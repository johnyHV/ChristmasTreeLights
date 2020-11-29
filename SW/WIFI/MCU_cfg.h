/**
   @file MCU_cfg.h

   @brief konfiguracia MCU

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/


#ifndef _MCU_CFG_H_
#define _MCU_CFG_H_

#define SOFTWARE_VERSION      "1.0.0"                 ///< FW version

#define DEBUG_CONSOLE         false                   ///< zapnutie/vypnutie DEBUG modu

#define SERIAL_BAUD_RATE      9600                    ///< komunikacna rychlost

#define WIFI_SSID             "Stuart-24"             ///< WI-FI SSID nazov
#define WIFI_PASSWORD         "novaoptika"            ///< WI-FI heslo

#define WEB_SERVER_PORT       80                      ///< WEB server port

#define LOOP_REFRES_TIME      10                      ///< LOOP refres time

#endif

/* EOF */
