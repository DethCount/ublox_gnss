#include "GNSS.h"

GNSSMonitoring::GNSSMonitoring(UBXClient *c) {
  client = c;
}

MonitoringHardware* GNSSMonitoring::getHardware() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_Hardware;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting hardware monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_Hardware
  );
}

MonitoringHardwareExtended* GNSSMonitoring::getHardwareExtended() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_HardwareExtended;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting hardware extended monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_HardwareExtended
  );
}

MonitoringIO* GNSSMonitoring::getIO() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_IO;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting IO monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_IO
  );
}

MonitoringMsgParseProcess* GNSSMonitoring::getMsgParseProcess() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_MsgParseProcess;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting msg parse and process monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_MsgParseProcess
  );
}

MonitoringReceiver* GNSSMonitoring::getReceiver() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_Receiver;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting receiver status monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_Receiver
  );
}

MonitoringReceiverBuffer* GNSSMonitoring::getReceiverBuffer() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_ReceiverBuffer;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting receiver buffer monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_ReceiverBuffer
  );
}

MonitoringTransmitterBuffer* GNSSMonitoring::getTransmitterBuffer() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_TransmitterBuffer;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting transmitter buffer monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_TransmitterBuffer
  );
}

MonitoringVersion* GNSSMonitoring::getVersion() {
  UBXMessage* cmd = new UBXMessage();
  cmd->msgId = MessageId::Monitoring_Version;
  cmd->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting version monitoring... ");
  #endif

  return client->trySend(
    cmd,
    MessageId::Monitoring_Version
  );
}
