/**
   @file CommunicationConversion.h

   @brief konverzia prichadzajucich prikazov do zrozumitelnych textov

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/


#ifndef _COMMUNICATION_CONVERSION_H_
#define _COMMUNICATION_CONVERSION_H_

#include "Variable.h"
#include "LedEffect_command.h"
#include "Communication.h"

void CommunicationConversion_BoolTranslate(struct ComDataCommandStruct*);     ///< konverzia bool hodnoty na text
void CommunicationConversion_Effect(struct ComDataCommandStruct*);            ///< konverzia hodnoty efektu na  text

#endif
