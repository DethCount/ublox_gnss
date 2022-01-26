#include "GNSS.h"

GNSSLog::GNSSLog(UBXClient *c) {
  client = c;
}

UBXRequestStatus GNSSLog::create(
  uint8_t version,
  byte logCfg,
  GNSSLogSize logSize,
  uint32_t userDefinedSize
) {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Log_Create;
  cmd->payloadLength = 7;
  cmd->payload[0] = version;
  cmd->payload[1] = logCfg;
  cmd->payload[2] = (uint8_t) logSize;
  cmd->payload[3] = userDefinedSize & 0xFF;
  cmd->payload[4] = userDefinedSize >> 8;
  cmd->payload[5] = userDefinedSize >> 16;
  cmd->payload[6] = userDefinedSize >> 24;

  #ifdef GNSS_DEBUG
    Serial.print("Sending log create command... ");
  #endif

  return client->trySendWithACK(cmd);
}

UBXRequestStatus GNSSLog::erase() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Log_Erase;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Sending log erase command... ");
  #endif

  return client->trySendWithACK(cmd);
}

LogFindTime* GNSSLog::findTime(
  uint16_t year,
  uint8_t month,
  uint8_t day,
  uint8_t hour,
  uint8_t minute,
  uint8_t second,
  uint8_t version = 0
) {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Log_FindTime;
  cmd->payloadLength = 12;
  cmd->payload[0] = version;
  cmd->payload[1] = 0x00; // request type
  cmd->payload[2] = 0x00; // reserved1
  cmd->payload[3] = 0x00; // reserved1
  cmd->payload[4] = lowByte(year);
  cmd->payload[5] = highByte(year);
  cmd->payload[6] = month;
  cmd->payload[7] = day;
  cmd->payload[8] = hour;
  cmd->payload[9] = minute;
  cmd->payload[10] = second;
  cmd->payload[11] = 0x00; // reserved2

  #ifdef GNSS_DEBUG
    Serial.print("Searching log by time... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Log_FindTime
  );
}

LogInfo* GNSSLog::getInfo() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Log_Info;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting log info... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Log_Info
  );
}

uint32_t GNSSLog::retrieve(
  UBXMessage *logEntries,
  uint32_t startNumber,
  uint32_t entryCount,
  uint8_t version,
  uint8_t numTries
) {
  uint32_t nbMsg = 0;
  uint8_t tries = 0;

  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Log_Retrieve;
  cmd->payloadLength = 12;
  cmd->payload[0] = startNumber & 0xFF;
  cmd->payload[1] = startNumber >> 8;
  cmd->payload[2] = startNumber >> 16;
  cmd->payload[3] = startNumber >> 24;
  cmd->payload[4] = entryCount & 0xFF;
  cmd->payload[5] = entryCount >> 8;
  cmd->payload[6] = entryCount >> 16;
  cmd->payload[7] = entryCount >> 24;
  cmd->payload[8] = version;
  cmd->payload[9] = 0x00; // reserved
  cmd->payload[10] = 0x00; // reserved
  cmd->payload[11] = 0x00; // reserved

  #ifdef GNSS_DEBUG
    Serial.print("Getting log entries... ");
  #endif

  client->send(cmd);
  UBXMessage *msg;
  while (nbMsg < entryCount && tries < numTries) {
    msg = client->next();
    if (msg->msgId != MessageId::Log_RetrieveString
      && msg->msgId != MessageId::Log_RetrievePosition
    ) {
      tries++;
      continue;
    }

    tries = 0;

    if (!msg->isValid) {
      break;
    }

    logEntries[nbMsg] = *msg;
    nbMsg++;
  }

  return nbMsg;
}

void GNSSLog::log(char* str, uint8_t length) {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Log_String;
  cmd->payloadLength = length;

  for (uint8_t i = 0; i < length; i++) {
    cmd->payload[i] = (uint8_t) str[i];
  }

  #ifdef GNSS_DEBUG
    Serial.print("Logging string... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Log_String
  );
}

