/**
   @file Communication.h

   @brief Kniznica pre komunikaciu s MCU

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
#include "LedEffect_command.h"
#include "WebPage.h"
#include "CommunicationWebStateMachine.h"
#include "CommunicationConversion.h"

extern bool CommunicationWifiFirstStartEnable;
extern uint8_t CommunicationWifiFirstStart;

struct ComTimeoutStruct {
  bool EnableTimeout;                                                           ///< enable/disable timeout timer
  uint16_t Time;                                                                ///< timeout time
};

struct ComBufferStruct {
  uint8_t Position;                                                             ///< frame buffer position
  char Buffer[COMMUNICATION_BUFFER_SIZE];                                       ///< frame buffer
  bool EndFrameSymbol;                                                          ///< end of frame symbol
};

struct ComDataCommandStruct {
  char command;                                                                 ///< command
  char variable[COMMUNICATION_COMMAND_LEN];                                     ///< variable
  uint8_t variable_len;                                                         ///< variable len
};

extern ComBufferStruct Com;                                                     ///< communication frame buffer
extern ComDataCommandStruct WebRequestResponseCommand;                          ///< Web request response command
extern ComTimeoutStruct ComTimeout;                                             ///< message timeout timer
extern ComTimeoutStruct AckTimeout;                                             ///< ACK timeout timer

void CommunicationMain();                                                       ///< Main function for lib
void CommunicationCheckCommand(ComDataCommandStruct*);                          ///< check input command
void CommunicationGetCommandAndValue(ComBufferStruct*, ComDataCommandStruct*);  ///< get command and value from frame
void CommunicationGetDataFromFrame(ComBufferStruct*);                           ///< get data from frame
bool CommunicationCheckBcc(ComBufferStruct*);                                   ///< check BCC from incomming message
uint8_t CommunicationCalculateBcc(char*, uint8_t);                              ///< block check character

void CommunicationClearComBuffer(ComBufferStruct*);                             ///< clear communication buffer
void CommunicationClearCommandBuffer(ComDataCommandStruct*);                    ///< clear command buffer

void CommunicationSendRequestWifi(ComDataCommandStruct*);                       ///< Request message
void CommunicationCreateRequestFrame(ComDataCommandStruct*, ComBufferStruct*);  ///< create frame with requestet data
void CommunicationGetDataForWeb();                                              ///< Function for getting data from MCU for WEB interface
void CommunicationCheckTimeoutMessage();                                        ///< Function for check timeout for message

void CommunicationWebSendRequest(char);                                         ///< Function for send request message
void ComunicationWebParsingResponse(String*, ComDataCommandStruct* );           ///< Function for parsing response from request message

void CommunicationSetConfigData(ComDataCommandStruct*);                         ///< Function for sending configuration data, and waitng to response
void CommunicationCheckAckResponse();                                           ///< Functior for check ACK response after configure
void CommunicationSendAckResponse();                                            ///< Function for send ACK response
void CommunicationCheckAckTimeout();                                            ///< Function for check ACK timeout

void CommunicationWifiFirstStartFunc();                                         ///< First start, and send SSID + IP Address
void CommunicationWifiSendIp();                                                 ///< send IP to MCU
void CommunicationWifiSendSsid();                                               ///< Send WI-FI SSID to MCU
#endif
