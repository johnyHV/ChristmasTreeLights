/**
   @file CommunicationWebStateMachine.h

   @brief stavy stavovej masiny pre vycitanie dat potrebnych pre JSON odpoved na WEB stranke

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/


#ifndef _COMMUNICATION_WEB_STATE_MACHINE_H_
#define _COMMUNICATION_WEB_STATE_MACHINE_H_

#include "Variable.h"
#include "MCU_cfg.h"

#define COM_STATE_CLEAR_BUFFER              0
#define COM_STATE_REQUEST_TIME              1
#define COM_STATE_RESPONSE_TIME             2
#define COM_STATE_REQUEST_EFFECT            3
#define COM_STATE_RESPONSE_EFFECT           4
#define COM_STATE_REQUEST_AUTO_ON           5
#define COM_STATE_RESPONSE_AUTO_ON          6
#define COM_STATE_REQUEST_AUTO_ON_EFFECT    7
#define COM_STATE_RESPONSE_AUTO_ON_EFFECT   8
#define COM_STATE_REQUEST_AUTO_ON_TIME_ON   9
#define COM_STATE_RESPONSE_AUTO_ON_TIME_ON  10
#define COM_STATE_REQUEST_AUTO_ON_TIME_OFF  11
#define COM_STATE_RESPONSE_AUTO_ON_TIME_OFF 12
#define COM_STATE_REQUEST_FIRMWARE          13
#define COM_STATE_RESPONSE_FIRMWARE         14
#define COM_STATE_REQUEST_EFFECT_SPEED      15
#define COM_STATE_RESPONSE_EFFECT_SPEED     16
#define COM_STATE_REQUEST_RANDOM_TIME       17
#define COM_STATE_RESPONSE_RANDOM_TIME      18
#define COM_STATE_SEND_DATA                 19

#define COM_FIST_STATUS_MCU_END             55

#endif
