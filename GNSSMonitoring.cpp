#include "GNSS.h"

GNSSMonitoring::GNSSMonitoring(UBXClient *c) {
  client = c;
}

MonitoringHardware* GNSSMonitoring::getHardware() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Monitoring_Hardware;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting hardware monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting hardware extended monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting IO monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting msg parse and process monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting receiver status monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting receiver buffer monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting transmitter buffer monitoring... "));
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

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting version monitoring... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Monitoring_Version
  );
}

void GNSSMonitoring::print(Stream* stream) {
  FREERAM_PRINT;

  printHardware(stream);
  printHardwareExtended(stream);
  printIO(stream);
  printMsgParseProcess(stream);
  printReceiver(stream);
  printReceiverBuffer(stream);
  printTransmitterBuffer(stream);
  printVersion(stream);

  FREERAM_PRINT;
}

void GNSSMonitoring::printHardware(Stream* stream) {
  getHardware()
    ->print(stream);
}

void GNSSMonitoring::printHardwareExtended(Stream* stream) {
  getHardwareExtended()
    ->print(stream);
}

void GNSSMonitoring::printIO(Stream* stream) {
  getIO()
    ->print(stream);
}

void GNSSMonitoring::printMsgParseProcess(Stream* stream) {
  getMsgParseProcess()
    ->print(stream);
}

void GNSSMonitoring::printReceiver(Stream* stream) {
  getReceiver()
    ->print(stream);
}

void GNSSMonitoring::printReceiverBuffer(Stream* stream) {
  getReceiverBuffer()
    ->print(stream);
}

void GNSSMonitoring::printTransmitterBuffer(Stream* stream) {
  getTransmitterBuffer()
    ->print(stream);
}

void GNSSMonitoring::printVersion(Stream* stream) {
  getVersion()
    ->print(stream);
}
