#include "GNSS.h"

GNSSTiming::GNSSTiming(UBXClient *c) {
  client = c;
}

TimingMark* GNSSTiming::getMark() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Timing_Mark;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting time mark data... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Timing_Mark
  );
}

TimingPulse* GNSSTiming::getPulse() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Timing_Pulse;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting time pulse... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Timing_Pulse
  );
}

TimingVerification* GNSSTiming::getVerification() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Timing_Verification;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting time verification... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Timing_Verification
  );
}

void GNSSTiming::print(Stream* stream) {
  FREERAM_PRINT;

  printMark(stream);
  printPulse(stream);
  printVerification(stream);

  FREERAM_PRINT;
}

void GNSSTiming::printMark(Stream* stream) {
  getMark()
    ->print(stream);
}

void GNSSTiming::printPulse(Stream* stream) {
  getPulse()
    ->print(stream);
}

void GNSSTiming::printVerification(Stream* stream) {
  getVerification()
    ->print(stream);
}
