#include "GNSS.h"

GNSSNavigation::GNSSNavigation(UBXClient *c) {
  client = c;
}

NavigationAOPStatus* GNSSNavigation::getAOPStatus() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_AOPStatus;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation AOP status... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_AOPStatus
  );
}

NavigationClock* GNSSNavigation::getClock() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_Clock;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation clock... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_Clock
  );
}

NavigationDGPS* GNSSNavigation::getDGPS() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_DGPS;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation DGPS... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_DGPS
  );
}

NavigationDOP* GNSSNavigation::getDOP() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_DillutionOfPrecision;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation DOP... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_DillutionOfPrecision
  );
}

NavigationPosECEF* GNSSNavigation::getPosECEF() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_PosECEF;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation ECEF position... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_PosECEF
  );
}

NavigationPosLLH* GNSSNavigation::getPosLLH() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_PosLLH;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation LLH position... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_PosLLH
  );
}

NavigationPosVT* GNSSNavigation::getPosVT() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_PosVT;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation position velocity and time... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_PosVT
  );
}

NavigationSBAS* GNSSNavigation::getSBAS() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_SBAS;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation SBAS... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_SBAS
  );
}

NavigationSOL* GNSSNavigation::getSOL() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_SOL;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation SOL... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_SOL
  );
}

NavigationStatus* GNSSNavigation::getStatus() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_Status;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation status... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_Status
  );
}

NavigationSpaceVehiculeInfo* GNSSNavigation::getSpaceVehiculeInfo() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_SpaceVehiculeInfo;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation space vehicule information... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_SpaceVehiculeInfo
  );
}

NavigationTimeGPS* GNSSNavigation::getTimeGPS() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_TimeGPS;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation GPS time... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_TimeGPS
  );
}

NavigationTimeUTC* GNSSNavigation::getTimeUTC() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_TimeUTC;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation UTC time... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_TimeUTC
  );
}

NavigationVelECEF* GNSSNavigation::getVelECEF() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_VelECEF;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation ECEF velocity... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_VelECEF
  );
}

NavigationVelNED* GNSSNavigation::getVelNED() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_VelNED;
  packet->payloadLength = 0;

  #ifdef GNSS_LOG_INFO
    Serial.print(F("Getting navigation NED velocity... "));
  #endif

  return client->trySend(
    packet,
    MessageId::Navigation_VelNED
  );
}

void GNSSNavigation::print(Stream* stream) {
  FREERAM_PRINT;

  printAOPStatus(stream);
  printClock(stream);
  printDGPS(stream);
  printDOP(stream);
  printPosECEF(stream);
  printPosLLH(stream);
  printPosVT(stream);
  printSBAS(stream);
  printSOL(stream);
  printStatus(stream);
  printSpaceVehiculeInfo(stream);
  printTimeGPS(stream);
  printTimeUTC(stream);
  printVelECEF(stream);
  printVelNED(stream);

  FREERAM_PRINT;
}

void GNSSNavigation::printAOPStatus(Stream* stream) {
  getAOPStatus()
    ->print(stream);
}

void GNSSNavigation::printClock(Stream* stream) {
  getClock()
    ->print(stream);
}

void GNSSNavigation::printDGPS(Stream* stream) {
  getDGPS()
    ->print(stream);
}

void GNSSNavigation::printDOP(Stream* stream) {
  getDOP()
    ->print(stream);
}

void GNSSNavigation::printPosECEF(Stream* stream) {
  getPosECEF()
    ->print(stream);
}

void GNSSNavigation::printPosLLH(Stream* stream) {
  getPosLLH()
    ->print(stream);
}

void GNSSNavigation::printPosVT(Stream* stream) {
  getPosVT()
    ->print(stream);
}

void GNSSNavigation::printSBAS(Stream* stream) {
  getSBAS()
    ->print(stream);
}

void GNSSNavigation::printSOL(Stream* stream) {
  getSOL()
    ->print(stream);
}

void GNSSNavigation::printStatus(Stream* stream) {
  getStatus()
    ->print(stream);
}

void GNSSNavigation::printSpaceVehiculeInfo(Stream* stream) {
  getSpaceVehiculeInfo()
    ->print(stream);
}

void GNSSNavigation::printTimeGPS(Stream* stream) {
  getTimeGPS()
    ->print(stream);
}

void GNSSNavigation::printTimeUTC(Stream* stream) {
  getTimeUTC()
    ->print(stream);
}

void GNSSNavigation::printVelECEF(Stream* stream) {
  getVelECEF()
    ->print(stream);
}

void GNSSNavigation::printVelNED(Stream* stream) {
  getVelNED()
    ->print(stream);
}

