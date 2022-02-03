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
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Log_Create;
  packet->payloadLength = 7;
  packet->payload[0] = version;
  packet->payload[1] = logCfg;
  packet->payload[2] = (uint8_t) logSize;
  packet->payload[3] = userDefinedSize & 0xFF;
  packet->payload[4] = (uint8_t)(userDefinedSize >> 8);
  packet->payload[5] = (uint8_t)(userDefinedSize >> 16);
  packet->payload[6] = (uint8_t)(userDefinedSize >> 24);

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Sending log create command... "));
  #endif

  return client->trySendWithACK(packet);
}

UBXRequestStatus GNSSLog::erase() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Log_Erase;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Sending log erase command... "));
  #endif

  return client->trySendWithACK(packet);
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
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Log_FindTime;
  packet->payloadLength = 12;
  packet->payload[0] = version;
  packet->payload[1] = 0x00; // request type
  packet->payload[2] = 0x00; // reserved1
  packet->payload[3] = 0x00; // reserved1
  packet->payload[4] = lowByte(year);
  packet->payload[5] = highByte(year);
  packet->payload[6] = month;
  packet->payload[7] = day;
  packet->payload[8] = hour;
  packet->payload[9] = minute;
  packet->payload[10] = second;
  packet->payload[11] = 0x00; // reserved2

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Searching log by time... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Log_FindTime
  );
}

LogInfo* GNSSLog::getInfo() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Log_Info;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting log info... "));
  #endif

  return client->trySend(
    packet,
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

  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Log_Retrieve;
  packet->payloadLength = 12;
  packet->payload[0] = startNumber & 0xFF;
  packet->payload[1] = (uint8_t)(startNumber >> 8);
  packet->payload[2] = (uint8_t)(startNumber >> 16);
  packet->payload[3] = (uint8_t)(startNumber >> 24);
  packet->payload[4] = entryCount & 0xFF;
  packet->payload[5] = (uint8_t)(entryCount >> 8);
  packet->payload[6] = (uint8_t)(entryCount >> 16);
  packet->payload[7] = (uint8_t)(entryCount >> 24);
  packet->payload[8] = version;
  packet->payload[9] = 0x00; // reserved
  packet->payload[10] = 0x00; // reserved
  packet->payload[11] = 0x00; // reserved

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting log entries... "));
  #endif

  client->send(packet);
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
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Log_String;
  packet->payloadLength = length;

  for (uint8_t i = 0; i < length; i++) {
    packet->payload[i] = (uint8_t) str[i];
  }

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Logging string... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Log_String
  );
}

void GNSSLog::print(Stream* stream) {
  FREERAM_PRINT;

  printInfo(stream);

  FREERAM_PRINT;
}

void GNSSLog::printFindTime(
  Stream* stream,
  uint16_t year,
  uint8_t month,
  uint8_t day,
  uint8_t hour,
  uint8_t minute,
  uint8_t second,
  uint8_t version = 0
) {
  findTime(
    year,
    month,
    day,
    hour,
    minute,
    second,
    version
  )
    ->print(stream);
}

void GNSSLog::printInfo(Stream* stream) {
  getInfo()
    ->print(stream);
}
