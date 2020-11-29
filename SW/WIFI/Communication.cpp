/**
   @file Communication.h

   @brief Kniznica pre komunikaciu s MCU

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "Communication.h"

ComBufferStruct Com = {0, {'\0'}, false};
ComDataCommandStruct WebRequestResponseCommand = {'\0', {'\0'}, 0};
ComTimeoutStruct ComTimeout = {false, 0};
ComTimeoutStruct AckTimeout = {false, 0};

uint8_t CommunicationWifiFirstStart = 0;
bool CommunicationWifiFirstStartEnable = true;

void CommunicationMain() {
  if (Serial.available()) {
    Com.Position++;
    Com.Buffer[Com.Position] =  Serial.read();

    if (Com.Buffer[Com.Position] == COMMUNICATION_END_FRAME_SYMBOL) {
      /* get RAW frame from data */
      CommunicationGetDataFromFrame(&Com);
      if (CommunicationCheckBcc(&Com) == true) {
#if (DEBUG_COMMUNICATION == true)
        Serial.println(F("Message valid!"));
#endif

        /* get value and command */
        ComDataCommandStruct ComDataCommand = {'\0', {'\0'}};
        CommunicationGetCommandAndValue(&Com, &ComDataCommand);

        /* check incomming commnad */
        CommunicationCheckCommand(&ComDataCommand);

        /* clear buffer */
        CommunicationClearComBuffer(&Com);

        /* disable timeout timer */
        ComTimeout.EnableTimeout = false;
        ComTimeout.Time = 0;
      } else {
#if (DEBUG_COMMUNICATION == true)
        Serial.println(F("Message invalid!"));
#endif
      }
    }
  }

  /* check message timeout */
  CommunicationCheckTimeoutMessage();

  /* check ACK message timeout */
  CommunicationCheckAckTimeout();

  /* get data from MCU for web interface */
  CommunicationGetDataForWeb();

  /* First start MCU. send SSID and IP address */
  CommunicationWifiFirstStartFunc();
}

void CommunicationGetCommandAndValue(ComBufferStruct *input_frame, ComDataCommandStruct *output_command) {
  output_command->command = input_frame->Buffer[0];
  output_command->variable_len = 0;

#if (DEBUG_COMMUNICATION == true)
  Serial.print(F("Command: "));
  Serial.println(output_command->command);
  Serial.print(F("Variable: "));
#endif

  for (uint8_t i = 2; i < input_frame->Position; i++) {
    if (input_frame->Buffer[i] != COMMUNICATION_NEXT_IS_BCC) {
      output_command->variable[output_command->variable_len] = input_frame->Buffer[i];
#if (DEBUG_COMMUNICATION == true)
      Serial.print(output_command->variable[output_command->variable_len]);
#endif
      output_command->variable_len++;
    } else {
      break;
    }
  }
#if (DEBUG_COMMUNICATION == true)
  Serial.println("");
#endif
}

void CommunicationCheckCommand(ComDataCommandStruct *data) {

  switch (data->command) {
    case COMMUNICATION_GET_WIFI_SSID:
      break;
    case COMMUNICATION_GET_WIFI_PASSWORD:
      break;
    case COMMUNICATION_GET_WIFI_STATUS:
      break;
    case COMMUNICATION_GET_CURRENT_EFFECT:
      break;
    case COMMUNICATION_SET_CURRENT_EFFECT:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_EFFECT");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_EFFECT;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_TIME:
      break;
    case COMMUNICATION_SET_TIME:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_TIME");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_TIME;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON:
      break;
    case COMMUNICATION_SET_AUTO_ON:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_AUTO_ON");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_AUTO_ON;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON_EFFECT:
      break;
    case COMMUNICATION_SET_AUTO_ON_EFFECT:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_AUTO_ON_EFFECT");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_AUTO_ON_EFFECT;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON_TIME_ON:
      break;
    case COMMUNICATION_SET_AUTO_ON_TIME_ON:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_AUTO_ON_TIME");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_AUTO_ON_TIME_ON;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON_TIME_OFF:
      break;
    case COMMUNICATION_SET_AUTO_ON_TIME_OFF:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_AUTO_OFF_TIME");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_AUTO_ON_TIME_OFF;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_FIRMWARE_VERSION:
      break;
    case COMMUNICATION_SET_FIRMWARE_VERSION:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_AUTO_FIRMWARE");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_FIRMWARE;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_EFFECT_SPEED:
      break;
    case COMMUNICATION_SET_EFFECT_SPEED:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_EFFECT_SPEED");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_EFFECT_SPEED;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_RANDOM_TIME:
      break;
    case COMMUNICATION_SET_RANDOM_TIME:
#if (DEBUG_COMMUNICATION == true)
      Serial.println("SET_RANDOM_TIME");
#endif
      WebRequestResponseCommand = *data;
      WebRequestForData = true;
      WebRequestForDataStateMachine = COM_STATE_RESPONSE_RANDOM_TIME;
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_ACK_AFTER_SET:
      CommunicationCheckAckResponse();
      break;
  }
}

void CommunicationGetDataFromFrame(ComBufferStruct *data) {
  uint8_t inputLen = 0;
  bool startFrame = false;

  for (uint8_t i = 0; i < data->Position; i++) {

    /* copy data from frame */
    if (startFrame) {
      data->Buffer[inputLen] = data->Buffer[i];
      inputLen++;
    }

    /* FIND START FRAME */
    if ((startFrame == false) && (data->Buffer[i] == COMMUNICATION_START_FRAME_SYMBOL)) {
      startFrame = true;
    }

    /* find end frame */
    if (data->Buffer[i] == COMMUNICATION_END_FRAME_SYMBOL) {
      break;
    }
  }

  data->Position = inputLen;
}

bool CommunicationCheckBcc(ComBufferStruct *input) {
  char BccData[200] = {'\0'};
  uint8_t BccLen = 0;
  uint8_t IncommingBcc = 0;

  /* no incomming validate data */
  if (input->Position == 0)
    return false;

  for ( ; BccLen < input->Position; BccLen++) {
    BccData[BccLen] = input->Buffer[BccLen];

    if (BccData[BccLen] == COMMUNICATION_NEXT_IS_BCC ) {
      IncommingBcc = input->Buffer[BccLen + 1];
      break;
    }
  }

#if (DEBUG_COMMUNICATION == true)
  Serial.println("");
  Serial.print(F("CheckBcc from: "));
  for ( uint8_t i = 0; i < BccLen; i++)
    Serial.print(BccData[i]);
  Serial.print(F(" ->"));
  Serial.print(F("Len: "));
  Serial.print(BccLen);
  Serial.print(F(" -> "));
#endif

  uint8_t BccResult = CommunicationCalculateBcc(&BccData[0], BccLen);
#if (DEBUG_COMMUNICATION == true)
  Serial.print(F("Inc: "));
  Serial.print(IncommingBcc, HEX);
  Serial.print(F(", Calc: "));
  Serial.println(BccResult, HEX);
#endif

  if (IncommingBcc == BccResult)
    return true;
  else
    return false;
}

uint8_t CommunicationCalculateBcc(char *data, uint8_t len) {
  uint8_t bcc = 0;

  for (uint8_t i = 0; i < len; i++) {
#if (DEBUG_COMMUNICATION == true)
    Serial.print(data[i]);
#endif
    bcc ^= data[i];
  }
#if (DEBUG_COMMUNICATION == true)
  Serial.println();
#endif
  return bcc;
}

void CommunicationClearComBuffer(ComBufferStruct *data) {
  data->Position = 0;
  memset(data->Buffer, '\0', COMMUNICATION_BUFFER_SIZE);
  for (uint8_t i = 0; i < COMMUNICATION_BUFFER_SIZE; i++) {
    data->Buffer[i] = '\0';
  }
}

void CommunicationClearCommandBuffer(ComDataCommandStruct *data) {
  data->command = '\0';
  memset(data->variable, '\0', COMMUNICATION_COMMAND_LEN);
}

void CommunicationSendRequestWifi(ComDataCommandStruct *data) {
  ComBufferStruct frame = {0, {'\0'}, false};

  CommunicationCreateRequestFrame(data, &frame);

  for (uint8_t i = 0; i <= frame.Position; i++) {
    Serial.print(frame.Buffer[i]);
  }

  ComTimeout.EnableTimeout = true;
  ComTimeout.Time = 0;
}

void CommunicationCreateRequestFrame(ComDataCommandStruct *data, ComBufferStruct *frame) {
  frame->Buffer[frame->Position] = COMMUNICATION_START_FRAME_SYMBOL;
  frame->Position++;
  frame->Buffer[frame->Position] = data->command;
  frame->Position++;
  frame->Buffer[frame->Position] = COMMUNICATION_DATA_SEPARATE_SYMBOL;
  frame->Position++;
  for (uint8_t i = 0; i < data->variable_len ; i++, frame->Position++) {
    frame->Buffer[frame->Position] = data->variable[i];
  }
  frame->Buffer[frame->Position] = COMMUNICATION_NEXT_IS_BCC;
  frame->Position++;
  frame->Buffer[frame->Position] = CommunicationCalculateBcc(&frame->Buffer[1], frame->Position - 2);
  frame->Position++;
  frame->Buffer[frame->Position] = COMMUNICATION_END_FRAME_SYMBOL;
  frame->Position++;
}

void CommunicationGetDataForWeb() {

  if (WebRequestForData == true) {

    switch (WebRequestForDataStateMachine) {

      /* get time from MCU --------------------------------------------------------*/
      case COM_STATE_CLEAR_BUFFER:
        WebPage_ClearJsonData();
        WebRequestForDataStateMachine = COM_STATE_REQUEST_TIME;
        break;
      case COM_STATE_REQUEST_TIME:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 1 - get time from MCU");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_TIME);
        break;

      /* response with time from MCU --------------------------------------------------------*/
      case COM_STATE_RESPONSE_TIME:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 2 - response with time from MCU");
#endif
        ComunicationWebParsingResponse(&WebPage_jsonData.time, &WebRequestResponseCommand);

        /* update state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_EFFECT;
        break;

      /* get currently effect --------------------------------------------------------*/
      case COM_STATE_REQUEST_EFFECT:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 3 - get currently effect");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_CURRENT_EFFECT);
        break;

      /* reposnse from MCU with effect --------------------------------------------------------*/
      case COM_STATE_RESPONSE_EFFECT:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 4 - reposnse from MCU with effect");
#endif
        CommunicationConversion_Effect(&WebRequestResponseCommand);
        ComunicationWebParsingResponse(&WebPage_jsonData.effect, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_AUTO_ON;
        break;

      /* GET AUTO ON STATUS -------------------------------------------------------- */
      case COM_STATE_REQUEST_AUTO_ON:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 5 - get auto on status");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_AUTO_ON);
        break;

      /* RESPONSE AUTO ON status -------------------------------------------------------- */
      case COM_STATE_RESPONSE_AUTO_ON:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 6 - reposnse auto on");
#endif
        CommunicationConversion_BoolTranslate(&WebRequestResponseCommand);
        ComunicationWebParsingResponse(&WebPage_jsonData.autoOn, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_AUTO_ON_EFFECT;
        break;

      /* GET AUTO ON EFFECT -------------------------------------------------------- */
      case COM_STATE_REQUEST_AUTO_ON_EFFECT:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 7 - get auto on status");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_AUTO_ON_EFFECT);
        break;

      /* RESPONSE AUTO ON effect -------------------------------------------------------- */
      case COM_STATE_RESPONSE_AUTO_ON_EFFECT:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 8 - reposnse auto on");
#endif
        CommunicationConversion_Effect(&WebRequestResponseCommand);
        ComunicationWebParsingResponse(&WebPage_jsonData.autoOnEffect, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_AUTO_ON_TIME_ON;
        break;

      /* GET AUTO ON TIME ON -------------------------------------------------------- */
      case COM_STATE_REQUEST_AUTO_ON_TIME_ON:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 9 - get auto on time ON");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_AUTO_ON_TIME_ON);
        break;

      /* RESPONSE AUTO ON TIME ON -------------------------------------------------------- */
      case COM_STATE_RESPONSE_AUTO_ON_TIME_ON:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 10 - reposnse auto on time ON");
#endif
        ComunicationWebParsingResponse(&WebPage_jsonData.autoOnTimeOn, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_AUTO_ON_TIME_OFF;
        break;

      /* GET AUTO ON TIME OFF -------------------------------------------------------- */
      case COM_STATE_REQUEST_AUTO_ON_TIME_OFF:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 11 - get auto on time OFF");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_AUTO_ON_TIME_OFF);
        break;

      /* RESPONSE AUTO ON TIME OFF -------------------------------------------------------- */
      case COM_STATE_RESPONSE_AUTO_ON_TIME_OFF:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 12 - reposnse auto on time OFF");
#endif
        ComunicationWebParsingResponse(&WebPage_jsonData.autoOnTimeOff, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_FIRMWARE;
        break;

      /* GET FIRMWARE -------------------------------------------------------- */
      case COM_STATE_REQUEST_FIRMWARE:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 13 - get firmware");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_FIRMWARE_VERSION);
        break;

      /* RESPONSE FIRMWARE -------------------------------------------------------- */
      case COM_STATE_RESPONSE_FIRMWARE:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 14 - response firmware");
#endif
        ComunicationWebParsingResponse(&WebPage_jsonData.Firmware, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_EFFECT_SPEED;
        break;

      /* GET effect speed -------------------------------------------------------- */
      case COM_STATE_REQUEST_EFFECT_SPEED:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 15 - get effect speed");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_EFFECT_SPEED);
        break;

      /* RESPONSE effect speed -------------------------------------------------------- */
      case COM_STATE_RESPONSE_EFFECT_SPEED:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 16 - response effectspeed");
#endif
        ComunicationWebParsingResponse(&WebPage_jsonData.EffectSpeed, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_REQUEST_RANDOM_TIME;
        break;

      /* GET random time -------------------------------------------------------- */
      case COM_STATE_REQUEST_RANDOM_TIME:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 17 - get random time");
#endif
        CommunicationWebSendRequest(COMMUNICATION_GET_RANDOM_TIME);
        break;

      /* RESPONSE random time -------------------------------------------------------- */
      case COM_STATE_RESPONSE_RANDOM_TIME:
#if (DEBUG_COMMUNICATION == true)
        Serial.println("Case 16 - response random time");
#endif
        ComunicationWebParsingResponse(&WebPage_jsonData.RandomTime, &WebRequestResponseCommand);
        /* udpate state machine */
        WebRequestForDataStateMachine = COM_STATE_SEND_DATA;
        break;

      /* send data -------------------------------------------------------- */
      case COM_STATE_SEND_DATA:
        WebPage_SendJsonData();
        WebRequestForDataStateMachine = COM_STATE_CLEAR_BUFFER;
        WebRequestForData = false;
        break;
    }
  }
}

void CommunicationCheckTimeoutMessage() {
  if (ComTimeout.EnableTimeout == true) {
    if (ComTimeout.Time >= COMMUNICATIONT_TIMMEOUT) {
      if (CommunicationWifiFirstStart == COM_FIST_STATUS_MCU_END)
        WebRequestForData = true;
      else
        CommunicationWifiFirstStartEnable = true;
    } else {
      ComTimeout.Time += LOOP_REFRES_TIME;
    }
  }
}

void CommunicationWebSendRequest(char request) {
  ComDataCommandStruct tmp = { '\0', {'\0'}, 0};

  /* send request */
  tmp.command = request;
  CommunicationSendRequestWifi(&tmp);
  WebRequestForData = false;
}

void ComunicationWebParsingResponse(String *outputData, ComDataCommandStruct *inputData) {
  for (uint8_t i = 0; i < inputData->variable_len; i++) {
    *outputData += inputData->variable[i];
  }

  /* clear buffer with incomming command */
  CommunicationClearCommandBuffer(inputData);
}

void CommunicationSetConfigData(ComDataCommandStruct *data) {
#if (DEBUG_COMMUNICATION == true)
  Serial.print("Command: ");
  Serial.println(data->command);
  Serial.print("Variable len: ");
  Serial.println(data->variable_len);
  Serial.print("Variable: ");
  for (uint8_t i = 0; i < data->variable_len; i++) {
    Serial.print(data->variable[i]);
  }
  Serial.println("");
#endif

  ComBufferStruct frame = {0, {'\0'}, false};
  CommunicationCreateRequestFrame(data, &frame);
  for (uint8_t i = 0; i <= frame.Position; i++) {
    Serial.print(frame.Buffer[i]);
  }

  AckTimeout.EnableTimeout = true;
}

void CommunicationCheckAckResponse() {
  /* disable timeout */
  AckTimeout.EnableTimeout = false;

  if (CommunicationWifiFirstStart == COM_FIST_STATUS_MCU_END) {
    /* send ACK response to browser. Last message, send firmware version is sended, and here is reponse to message */
    WebPage_SendResponse(true);
  } else {
    CommunicationWifiFirstStart++;
    CommunicationWifiFirstStartEnable = true;
  }

  /* clear structure with data for sending */
  CommunicationClearCommandBuffer(&WebPage_SettingsMessage);
}

void CommunicationSendAckResponse() {
  ComDataCommandStruct data = { '\0', {'\0'}, 0};
  ComBufferStruct frame = {0, {'\0'}, false};
  data.command = COMMUNICATION_ACK_AFTER_SET;

  CommunicationCreateRequestFrame(&data, &frame);

  for (uint8_t i = 0; i <= frame.Position; i++) {
    Serial.print(frame.Buffer[i]);
  }

}

void CommunicationCheckAckTimeout() {
  if (AckTimeout.EnableTimeout == true) {
    if (AckTimeout.Time >= COMMUNICATIONT_ACK_TIMMEOUT) {
      AckTimeout.Time = 0;
      CommunicationSendRequestWifi(&WebPage_SettingsMessage);
    } else {
      AckTimeout.Time += LOOP_REFRES_TIME;
    }
  }
}

void CommunicationWifiFirstStartFunc() {
  if (CommunicationWifiFirstStartEnable == true) {
    switch (CommunicationWifiFirstStart) {
      /* send IP */
      case 0:
        CommunicationWifiSendIp();
        break;
      /* send IP */
      case 1:
        CommunicationWifiSendSsid();
        break;
      case 2:
        CommunicationWifiFirstStart = COM_FIST_STATUS_MCU_END;
        break;
    }
    CommunicationWifiFirstStartEnable = false;
  }
}

void CommunicationWifiSendIp() {
  IPAddress IP = WiFi.localIP();
  sprintf(WebPage_SettingsMessage.variable, "%s", IP.toString().c_str());
  WebPage_SettingsMessage.variable_len = IP.toString().length();

  /* send request */
  WebPage_SettingsMessage.command = COMMUNICATION_SET_WIFI_IP;
  CommunicationSendRequestWifi(&WebPage_SettingsMessage);
}

void CommunicationWifiSendSsid() {

  sprintf(WebPage_SettingsMessage.variable, "%s", WIFI_SSID);

  /* send request */
  WebPage_SettingsMessage.command = COMMUNICATION_SET_WIFI_SSID;
  CommunicationSendRequestWifi(&WebPage_SettingsMessage);
}
