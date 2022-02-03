#include "GNSS.h"

GNSSReceiverManager::GNSSReceiverManager(UBXClient *c) {
  client = c;
}

ReceiverManagerAlmanach* GNSSReceiverManager::getAlmanach() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Almanach;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting alamanach from receiver menager... "));
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_Almanach
  );
}

ReceiverManagerAlmanach* GNSSReceiverManager::getAlmanach(uint8_t svid) {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Almanach;
  packet->payloadLength = 1;
  packet->payload[0] = svid;

  #ifdef GNSS_LOG_INFO
    Serial.print(
      F("Getting alamanach from receiver menager for hoven svid... ")
    );
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_Almanach
  );
}

ReceiverManagerEphemeris* GNSSReceiverManager::getEphemeris() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Ephemeris;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting ephemeris from receiver manager... "));
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_Ephemeris
  );
}

ReceiverManagerEphemeris* GNSSReceiverManager::getEphemeris(uint8_t svid) {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Ephemeris;
  packet->payloadLength = 1;
  packet->payload[0] = svid;

  #ifdef GNSS_LOG_INFO
    Serial.print(
      F("Getting ephemeris from receiver manager for given svid... ")
    );
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_Ephemeris
  );
}

void GNSSReceiverManager::powerRequest(uint32_t duration, uint32_t flags) {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_PowerReq;
  packet->payloadLength = 8;
  packet->payload[0] = duration & 0xFF;
  packet->payload[1] = (uint8_t)(duration >> 8);
  packet->payload[2] = (uint8_t)(duration >> 16);
  packet->payload[3] = (uint8_t)(duration >> 24);
  packet->payload[4] = flags & 0xFF;
  packet->payload[5] = (uint8_t)(flags >> 8);
  packet->payload[6] = (uint8_t)(flags >> 16);
  packet->payload[7] = (uint8_t)(flags >> 24);

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Sending power request to receiver manager... "));
  #endif

  client->send(packet);
}

ReceiverManagerRaw* GNSSReceiverManager::getRaw() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Raw;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting raw measurement data from receiver manager... "));
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_Raw
  );
}

ReceiverManagerSpaceVehiculeInfo* GNSSReceiverManager::getSpaceVehiculeInfo() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_SVStatus;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(
      F("Getting space vehicules statuses from receiver manager... ")
    );
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_SVStatus
  );
}

void GNSSReceiverManager::print(Stream* stream) {
  FREERAM_PRINT;

  printAlmanach(stream);
  printEphemeris(stream);
  printRaw(stream);
  printSpaceVehiculeInfo(stream);

  FREERAM_PRINT;
}

void GNSSReceiverManager::printAlmanach(Stream* stream) {
  getAlmanach()
    ->print(stream);
}

void GNSSReceiverManager::printAlmanach(Stream* stream, uint8_t svid) {
  getAlmanach(svid)
    ->print(stream);
}

void GNSSReceiverManager::printEphemeris(Stream* stream) {
  getEphemeris()
    ->print(stream);
}

void GNSSReceiverManager::printEphemeris(Stream* stream, uint8_t svid) {
  getEphemeris(svid)
    ->print(stream);
}

void GNSSReceiverManager::printRaw(Stream* stream) {
  getRaw()
    ->print(stream);
}

void GNSSReceiverManager::printSpaceVehiculeInfo(Stream* stream) {
  getSpaceVehiculeInfo()
    ->print(stream);
}
