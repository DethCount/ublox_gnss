#include "GNSS.h"

GNSSReceiverManager::GNSSReceiverManager(UBXClient *c) {
  client = c;
}

ReceiverManagerAlmanach* GNSSReceiverManager::getAlmanach() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Almanach;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting alamanach from receiver menager... ");
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

  #ifdef GNSS_DEBUG
    Serial.print("Getting alamanach from receiver menager for hoven svid... ");
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

  #ifdef GNSS_DEBUG
    Serial.print("Getting ephemeris from receiver manager... ");
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

  #ifdef GNSS_DEBUG
    Serial.print("Getting ephemeris from receiver manager for given svid... ");
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

  #ifdef GNSS_DEBUG
    Serial.print("Sending power request to receiver manager... ");
  #endif

  client->send(packet);
}

ReceiverManagerRaw* GNSSReceiverManager::getRaw() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::ReceiverManager_Raw;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting raw measurement data from receiver manager... ");
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

  #ifdef GNSS_DEBUG
    Serial.print("Getting space vehicules statuses from receiver manager... ");
  #endif

  return client->trySend(
    packet,
    MessageId::ReceiverManager_SVStatus
  );
}
