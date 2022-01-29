#include "GNSS.h"

GNSSMonitoring::GNSSMonitoring(UBXClient *c) {
  client = c;
}

MonitoringHardware* GNSSMonitoring::getHardware() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_Hardware;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting hardware monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_Hardware
  );
}

MonitoringHardwareExtended* GNSSMonitoring::getHardwareExtended() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_HardwareExtended;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting hardware extended monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_HardwareExtended
  );
}

MonitoringIO* GNSSMonitoring::getIO() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_IO;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting IO monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_IO
  );
}

MonitoringMsgParseProcess* GNSSMonitoring::getMsgParseProcess() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_MsgParseProcess;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting msg parse and process monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_MsgParseProcess
  );
}

MonitoringReceiver* GNSSMonitoring::getReceiver() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_Receiver;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting receiver status monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_Receiver
  );
}

MonitoringReceiverBuffer* GNSSMonitoring::getReceiverBuffer() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_ReceiverBuffer;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting receiver buffer monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_ReceiverBuffer
  );
}

MonitoringTransmitterBuffer* GNSSMonitoring::getTransmitterBuffer() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_TransmitterBuffer;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting transmitter buffer monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_TransmitterBuffer
  );
}

MonitoringVersion* GNSSMonitoring::getVersion() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_Version;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting version monitoring... ");
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_Version
  );
}
