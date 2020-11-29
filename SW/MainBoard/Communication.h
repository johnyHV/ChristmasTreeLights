/**
   @file Communication.h

   @brief komunikacny protokol pre komunikaciu s WI-FI modulom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <SoftwareSerial.h>
#include "Variable.h"
#include "MCU_cfg.h"
#include "Communication_command.h"
#include "LedEffect.h"
#include "Mcu_status.h"

/* timeout structure */
struct ComTimeoutStruct {
  bool EnableTimeout;
  uint16_t Time;
};

/* buffer for frame */
struct ComBufferStruct {
  uint8_t Position;
  char Buffer[COMMUNICATION_BUFFER_SIZE];
  bool EndFrameSymbol;
};

/* buffer for message */
struct ComDataCommandStruct {
  char command;
  char variable[COMMUNICATION_COMMAND_LEN];
  uint8_t variable_len;
};

extern ComBufferStruct Com;                                                     ///< buffer pre pracu s USB rozhranim 

#if (BLUETOOTH_ENABLE == true)
extern ComBufferStruct ComBluetooth;                                            ///< buffer pre pracu s bluetooth rozhranim
#endif
#if (WIFI_ENABLE == true)
extern ComBufferStruct ComWifi;                                                 ///< buffer pre pracu s WI-FI rozhranim
#endif

extern ComTimeoutStruct ComTimeout;                                             ///< timeout pre spravy
extern ComTimeoutStruct AckTimeout;                                             ///< Timeout pre ACK spravy

void CommunicationMain();                                                       ///< Main function for lib
void CommunicationCheckCommand(ComDataCommandStruct*);                          ///< check input command
void CommunicationGetCommandAndValue(ComBufferStruct*, ComDataCommandStruct*);  ///< get command and value from frame
void CommunicationGetDataFromFrame(ComBufferStruct*);                           ///< get data from frame
bool CommunicationCheckBcc(ComBufferStruct*);                                   ///< check BCC from incomming message
uint8_t CommunicationCalculateBcc(char*, uint8_t);                              ///< block check character
void CommunicationClearComBuffer(ComBufferStruct*);                             ///< clear communication buffer
void CommunicationClearCommandBuffer(ComDataCommandStruct*);                    ///< clear command buffer
void CommunicationSendRequestWifi(ComDataCommandStruct*);                       ///< Request message
void CommunicationCreateRequestFrame(ComDataCommandStruct*, ComBufferStruct*);  ///< create frame with request data

void CommunicationSetConfigData(ComDataCommandStruct*);                         ///< Function for sending configuration data, and waitng to response
void CommunicationCheckAckResponse();                                           ///< Functior for check ACK response after configure
void CommunicationSendAckResponse();                                            ///< Function for send ACK response
void CommunicationCheckAckTimeout();                                            ///< Function for check ACK timeout
void CommunicationCheckTimeoutMessage();                                        ///< Function for check message timeout

#endif
