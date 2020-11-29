/**
   @file Communication_command.h

   @brief komunikacne prikazy, a nastavenie komunikacie

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/


#ifndef _COMMUNICATION_COMMAND_H_
#define _COMMUNICATION_COMMAND_H_

#include "Variable.h"
#include "MCU_cfg.h"

#define DEBUG_COMMUNICATION                       false

#define COMMUNICATION_BUFFER_SIZE                 50
#define COMMUNICATION_COMMAND_LEN                 30

#define COMMUNICATIONT_TIMMEOUT                   300
#define COMMUNICATIONT_ACK_TIMMEOUT               300

#define COMMUNICATION_SET_WIFI_IP                 'I'
#define COMMUNICATION_GET_WIFI_IP                 'i'
#define COMMUNICATION_SET_WIFI_SSID               'S'
#define COMMUNICATION_GET_WIFI_SSID               's'
#define COMMUNICATION_SET_WIFI_PASSWORD           'P'
#define COMMUNICATION_GET_WIFI_PASSWORD           'p'
#define COMMUNICATION_SET_WIFI_STATUS             'W'
#define COMMUNICATION_GET_WIFI_STATUS             'w'
#define COMMUNICATION_SET_CURRENT_EFFECT          'E'
#define COMMUNICATION_GET_CURRENT_EFFECT          'e'
#define COMMUNICATION_SET_TIME                    'T'
#define COMMUNICATION_GET_TIME                    't'
#define COMMUNICATION_SET_AUTO_ON                 'A'
#define COMMUNICATION_GET_AUTO_ON                 'a'
#define COMMUNICATION_SET_AUTO_ON_EFFECT          'F'
#define COMMUNICATION_GET_AUTO_ON_EFFECT          'f'
#define COMMUNICATION_SET_AUTO_ON_TIME_ON         'O'
#define COMMUNICATION_GET_AUTO_ON_TIME_ON         'o'
#define COMMUNICATION_SET_AUTO_ON_TIME_OFF        'N'
#define COMMUNICATION_GET_AUTO_ON_TIME_OFF        'n'
#define COMMUNICATION_SET_FIRMWARE_VERSION        'V'
#define COMMUNICATION_GET_FIRMWARE_VERSION        'v'
#define COMMUNICATION_SET_EFFECT_SPEED            'Z'
#define COMMUNICATION_GET_EFFECT_SPEED            'z'
#define COMMUNICATION_SET_RANDOM_TIME             'X'
#define COMMUNICATION_GET_RANDOM_TIME             'x'

#define COMMUNICATION_START_FRAME_SYMBOL          '$'
#define COMMUNICATION_NEXT_IS_BCC                 '/'
#define COMMUNICATION_END_FRAME_SYMBOL            ';'
#define COMMUNICATION_DATA_SEPARATE_SYMBOL        '!'
#define COMMUNICATION_ACK_AFTER_SET               '@'

#endif
