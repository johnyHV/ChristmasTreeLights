/**
   @file IR_Remote.h

   @brief praca s IR dialkovym ovladanim

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _REMOTE_H_
#define _REMOTE_H_

#include "IR_Remote_cfg.h"

#if (IR_REMOTE_ENABLE == true)
#include <IRremote.h>
#endif

#include "MCU_cfg.h"
#include "Variable.h"

uint8_t IR_Scan();                                  ///< Kniznica kontrolujuca stav IR prijimaca

#if (IR_REMOTE_ENABLE == true)
void IR_CheckButton(decode_results *results);       ///< Funkcia spracuvajuca prichadzajuci prikaz
#endif

#endif

/* EOF */
