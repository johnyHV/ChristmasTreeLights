/**
   @file Communication.cpp

   @brief komunikacny protokol pre komunikaciu s WI-FI modulom

   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "Communication.h"

ComBufferStruct Com = {0, {'\0'}, false};
ComTimeoutStruct ComTimeout = {false, 0};
ComTimeoutStruct AckTimeout = {false, 0};

#if (BLUETOOTH_ENABLE == true)
ComBufferStruct ComBluetooth = {0, {'\0'}, false};;
#endif
#if (WIFI_ENABLE == true)
ComBufferStruct ComWifi = {0, {'\0'}, false};;
#endif

void CommunicationMain() {
  if (Serial.available()) {
    Com.Position++;
    Com.Buffer[Com.Position] =  Serial.read();

    if (Com.Buffer[Com.Position] == COMMUNICATION_END_FRAME_SYMBOL) {
      /* get value and command */
      ComDataCommandStruct ComDataCommand = {'\0', {'\0'}};
      CommunicationGetCommandAndValue(&Com, &ComDataCommand);

      CommunicationCheckCommand(&ComDataCommand);

      /* clear buffer */
      CommunicationClearComBuffer(&Com);
    }
  }

#if (BLUETOOTH_ENABLE == true)
  if ( bluetooth.available()) {
    ComBluetooth.Position++;
    ComBluetooth.Buffer[ComBluetooth.Position] = bluetooth.read();

    if (ComBluetooth.Buffer[ComBluetooth.Position] == COMMUNICATION_END_FRAME_SYMBOL) {

      /* get value and command */
      ComDataCommandStruct ComDataCommand = {'\0', {'\0'}};
      CommunicationGetCommandAndValue(&ComBluetooth, &ComDataCommand);

      CommunicationCheckCommand(&ComDataCommand);

      /* clear buffer */
      CommunicationClearComBuffer(&ComBluetooth);
    }
  }
#endif

#if (WIFI_ENABLE == true)
  if (wifi.available()) {

    if (COMMUNICATION_BUFFER_SIZE > ComWifi.Position) {
      ComWifi.Position++;
    } else {
      ComWifi.Position = 0;
    }
    ComWifi.Buffer[ComWifi.Position] = wifi.read();
    Serial.print(ComWifi.Buffer[ComWifi.Position]);

    if (ComWifi.Buffer[ComWifi.Position] == COMMUNICATION_END_FRAME_SYMBOL) {
      /* get RAW frame from data */
      CommunicationGetDataFromFrame(&ComWifi);
      if (CommunicationCheckBcc(&ComWifi) == true) {
#if (DEBUG_COMMUNICATION == true)
        Serial.println(F("Message valid!"));
#endif
        /* get value and command */
        ComDataCommandStruct ComDataCommand = {'\0', {'\0'}, 0};
        CommunicationGetCommandAndValue(&ComWifi, &ComDataCommand);

        /* processing value and command */
        CommunicationCheckCommand(&ComDataCommand);

        /* disable timeout timer */
        ComTimeout.EnableTimeout = false;
        ComTimeout.Time = 0;
      } else {
#if (DEBUG_COMMUNICATION == true)
        Serial.println(F("Message invalid!"));
#endif
      }

      /* clear buffer */
      CommunicationClearComBuffer(&ComWifi);
    }
  }

  /* check message timeout */
  CommunicationCheckTimeoutMessage();

  /* check ACK message timeout */
  CommunicationCheckAckTimeout();
#endif


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
    case COMMUNICATION_SET_WIFI_IP:
      McuStatusSetWifiIp(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_WIFI_IP:
      break;
    case COMMUNICATION_SET_WIFI_SSID:
      McuStatusSetWifiSsid(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_WIFI_SSID:
      break;
    case COMMUNICATION_SET_WIFI_PASSWORD:
      break;
    case COMMUNICATION_GET_WIFI_PASSWORD:
      break;
    case COMMUNICATION_SET_WIFI_STATUS:
      McuStatusSetWifiStatus(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_WIFI_STATUS:
      break;
    case COMMUNICATION_SET_CURRENT_EFFECT:
      McuStatusSetEffect(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_CURRENT_EFFECT:
      McuStatusSendCurrentEffect();
      break;
    case COMMUNICATION_SET_TIME:
      McuStatusSetTime(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_TIME:
      McuStatusSendCurrentTime();
      break;
    case COMMUNICATION_SET_AUTO_ON:
      McuStatusSetAutoOn(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON:
      McuStatusSendAutoOnStatus();
      break;
    case COMMUNICATION_SET_AUTO_ON_EFFECT:
      McuStatusSetAutoOnEffect(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON_EFFECT:
      McuStatusSendAutoOnEffect();
      break;
    case COMMUNICATION_SET_AUTO_ON_TIME_ON:
      McuStatusSetAutoOnTimeOn(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON_TIME_ON:
      McuStatusSendAutoOnTimeOn();
      break;
    case COMMUNICATION_SET_AUTO_ON_TIME_OFF:
      McuStatusSetAutoOnTimeOff(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_AUTO_ON_TIME_OFF:
      McuStatusSendAutoOnTimeOff();
      break;
    case COMMUNICATION_SET_FIRMWARE_VERSION:
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_FIRMWARE_VERSION:
      McuStatusSendFirmware();
      break;
    case COMMUNICATION_SET_EFFECT_SPEED:
      McuStatusSetEffectSpeed(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_EFFECT_SPEED:
      McuStatusSendEffectSpeed();
      break;
    case COMMUNICATION_SET_RANDOM_TIME:
      McuStatusSetRandomTime(data);
      CommunicationSendAckResponse();
      break;
    case COMMUNICATION_GET_RANDOM_TIME:
      McuStatusSendRandomTime();
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
    bcc ^= data[i];
  }
  return bcc;
}

void CommunicationClearComBuffer(ComBufferStruct *data) {
  data->Position = 0;
  memset(data->Buffer, '\0', sizeof(data->Buffer));
}

void CommunicationClearCommandBuffer(ComDataCommandStruct *data) {
  data->command = '\0';
  memset(data->variable, '\0', sizeof(data->variable));
}

void CommunicationSendRequestWifi(ComDataCommandStruct *data) {
#if (WIFI_ENABLE == true)
  ComBufferStruct frame = {0, {'\0'}, false};

  CommunicationCreateRequestFrame(data, &frame);

  for (uint8_t i = 0; i <= frame.Position; i++) {
    wifi.print(frame.Buffer[i]);
  }

  ComTimeout.EnableTimeout = true;
  ComTimeout.Time = 0;
#endif
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

void CommunicationSetConfigData(ComDataCommandStruct *data) {
#if (DEBUG_COMMUNICATION == true)
  Serial.print(F("Command: "));
  Serial.println(data->command);
  Serial.print(F("Variable len: "));
  Serial.println(data->variable_len);
  Serial.print(F("Variable: "));

  for (uint8_t i = 0; i < data->variable_len; i++) {
    Serial.print(data->variable[i]);
  }
  Serial.println("");
#endif

  ComBufferStruct frame = {0, {'\0'}, false};
  CommunicationCreateRequestFrame(data, &frame);
  for (uint8_t i = 0; i < frame.Position; i++) {
    wifi.print(frame.Buffer[i]);
  }

  AckTimeout.EnableTimeout = true;

}

void CommunicationCheckAckResponse() {
  /* disable timeout */
  AckTimeout.EnableTimeout = false;
  AckTimeout.Time = 0;

  /* clear structure with data for sending */
  CommunicationClearCommandBuffer(&ComDataCommandTx);
}

void CommunicationSendAckResponse() {
  ComDataCommandStruct data = { '\0', {'\0'}, 0};
  ComBufferStruct frame = {0, {'\0'}, false};
  data.command = COMMUNICATION_ACK_AFTER_SET;

  CommunicationCreateRequestFrame(&data, &frame);

  for (uint8_t i = 0; i <= frame.Position; i++) {
    wifi.print(frame.Buffer[i]);
  }

}

void CommunicationCheckAckTimeout() {
  if (AckTimeout.EnableTimeout == true) {
    if (AckTimeout.Time >= COMMUNICATIONT_ACK_TIMMEOUT) {
      AckTimeout.Time = 0;
      CommunicationSetConfigData(&ComDataCommandTx);
    } else {
      AckTimeout.Time += LOOP_REFRESH_TIME;
    }
  }
}

void CommunicationCheckTimeoutMessage() {
  if (ComTimeout.EnableTimeout == true) {
    if (ComTimeout.Time >= COMMUNICATIONT_TIMMEOUT) {
    } else {
      ComTimeout.Time += LOOP_REFRESH_TIME;
    }
  }
}
