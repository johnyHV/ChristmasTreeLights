/**
   @file WebPage.cpp

   @brief funkcie pre spracovanie prikazov z WEB stranky
   
   @author Miroslav Pivovarsky
   Contact: miroslav.pivovarsky@gmail.com

   @bug: no know bug

*/

#include "WebPage.h"

struct JsonDataStruct WebPage_jsonData = { {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};
struct ComDataCommandStruct WebPage_SettingsMessage = {'\0', {'\0'}, 0};

void WebPage_root() {
  server.send(200, "text/html", htmlPageRoot);
#if (DEBUG_CONSOLE == true)
  Serial.println("CLIENT!");
#endif
}

void WebPage_setEffect() {

  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_CURRENT_EFFECT;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_setTime() {

  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_TIME;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_jsonInput() {
#if (DEBUG_CONSOLE == true)
  Serial.println("JSON");
#endif
  WebRequestForData = true;
  /*
    server.send(200, F("text/plain"), "{  \"time\" : \"13:31:55\", \
                                        \"effect\" : \"Color\", \
                                        \"autoOn\" : \"false\", \
                                        \"autoOnTimeOn\" : \"18:00:00\", \
                                        \"autoOnTimeOff\" : \"23:00:00\", \
                                        \"autoOnEffect\" : \"Random\", \
                                        \"firmware\" : \"1.0.0\" }");
  */
}

void WebPage_NotFound() {
#if (DEBUG_CONSOLE == true)
  Serial.println("error");
#endif

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void WebPage_setAutoOn() {

  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_AUTO_ON;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_setAutoOnEffect() {
  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_AUTO_ON_EFFECT;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_setAutoOnTimeOn() {
  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_AUTO_ON_TIME_ON;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_setAutoOnTimeOff() {
  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_AUTO_ON_TIME_OFF;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_setEffectSpeed() {
  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_EFFECT_SPEED;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_setRandomTime() {
  String incommingValue = "";
  WebPage_DebugIncommingData();

  incommingValue = server.arg(0);
  WebPage_SettingsMessage.command = COMMUNICATION_SET_RANDOM_TIME;
  incommingValue.toCharArray(WebPage_SettingsMessage.variable, COMMUNICATION_COMMAND_LEN);
  WebPage_SettingsMessage.variable_len = incommingValue.length();

  CommunicationSetConfigData(&WebPage_SettingsMessage);
}

void WebPage_DebugIncommingData() {
#if (DEBUG_CONSOLE == true)
  String message;
  Serial.println("SET AUTO ON!");
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  Serial.println(message);
#endif
}

void WebPage_SendJsonData() {
  String data = {""};
  data = "{  \"time\" : \"";
  data += WebPage_jsonData.time;
  data += "\", ";
  data += "\"effect\" : \"";
  data += WebPage_jsonData.effect;
  data += "\", ";
  data += "\"autoOn\" : \"";
  data += WebPage_jsonData.autoOn;
  data += "\", ";
  data += "\"autoOnTimeOn\" : \"";
  data += WebPage_jsonData.autoOnTimeOn;
  data += "\", ";
  data += "\"autoOnTimeOff\" : \"";
  data += WebPage_jsonData.autoOnTimeOff;
  data += "\", ";
  data += "\"autoOnEffect\" : \"";
  data += WebPage_jsonData.autoOnEffect;
  data += "\", ";
  data += "\"FirmwareMcu\" : \"";
  data += WebPage_jsonData.Firmware;
  data += "\", ";
  data += "\"EffectSpeed\" : \"";
  data += WebPage_jsonData.EffectSpeed;
  data += "\", ";
  data += "\"RandomTime\" : \"";
  data += WebPage_jsonData.RandomTime;
  data += "\", ";
  data += "\"FirmwareWifi\" : \"";
  data += SOFTWARE_VERSION;
  data += "\" }";

  //#if (DEBUG_CONSOLE == true)
  Serial.print("Sending: ");
  Serial.println(data);
  //#endif
  server.send(200, F("text/plain"), data);
}

void WebPage_ClearJsonData() {
  WebPage_jsonData.time = "";
  WebPage_jsonData.effect = "";
  WebPage_jsonData.autoOn = "";
  WebPage_jsonData.autoOnEffect = "";
  WebPage_jsonData.autoOnTimeOn = "";
  WebPage_jsonData.autoOnTimeOff = "";
  WebPage_jsonData.Firmware = "";
  WebPage_jsonData.EffectSpeed = "";
  WebPage_jsonData.RandomTime = "";
}

void WebPage_SendResponse(bool stat) {
  if (stat == true)
    server.send(200, F("text/html"), "<meta http-equiv=\"refresh\" content=\"1; url=/\" /> Settings OK");
  else
    server.send(200, F("text/html"), "<meta http-equiv=\"refresh\" content=\"3; url=/\" /> Settings problem. MCU not responding");
}
