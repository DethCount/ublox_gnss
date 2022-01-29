#include "GNSS.h"

GNSSNavigation::GNSSNavigation(UBXClient *c) {
  client = c;
}

NavigationAOPStatus* GNSSNavigation::getAOPStatus() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_AOPStatus;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation AOP status... ");
  #endif

  return static_cast<NavigationAOPStatus*>(client->trySend(
    packet,
    MessageId::Navigation_AOPStatus
  ));
}

NavigationClock* GNSSNavigation::getClock() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_Clock;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation clock... ");
  #endif

  return static_cast<NavigationClock*>(client->trySend(
    packet,
    MessageId::Navigation_Clock
  ));
}

NavigationDGPS* GNSSNavigation::getDGPS() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_DGPS;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation DGPS... ");
  #endif

  return static_cast<NavigationDGPS*>(client->trySend(
    packet,
    MessageId::Navigation_DGPS
  ));
}

NavigationDOP* GNSSNavigation::getDOP() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_DillutionOfPrecision;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation DOP... ");
  #endif

  return static_cast<NavigationDOP*>(client->trySend(
    packet,
    MessageId::Navigation_DillutionOfPrecision
  ));
}

NavigationPosECEF* GNSSNavigation::getPosECEF() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_PosECEF;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation ECEF position... ");
  #endif

  return static_cast<NavigationPosECEF*>(client->trySend(
    packet,
    MessageId::Navigation_PosECEF
  ));
}

NavigationPosLLH* GNSSNavigation::getPosLLH() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_PosLLH;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation LLH position... ");
  #endif

  return static_cast<NavigationPosLLH*>(client->trySend(
    packet,
    MessageId::Navigation_PosLLH
  ));
}

NavigationPosVT* GNSSNavigation::getPosVT() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_PosVT;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation position velocity and time... ");
  #endif

  return static_cast<NavigationPosVT*>(client->trySend(
    packet,
    MessageId::Navigation_PosVT
  ));
}

NavigationSBAS* GNSSNavigation::getSBAS() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_SBAS;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation SBAS... ");
  #endif

  return static_cast<NavigationSBAS*>(client->trySend(
    packet,
    MessageId::Navigation_SBAS
  ));
}

NavigationSOL* GNSSNavigation::getSOL() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_SOL;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation SOL... ");
  #endif

  return static_cast<NavigationSOL*>(client->trySend(
    packet,
    MessageId::Navigation_SOL
  ));
}

NavigationStatus* GNSSNavigation::getStatus() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_Status;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation status... ");
  #endif

  return static_cast<NavigationStatus*>(client->trySend(
    packet,
    MessageId::Navigation_Status
  ));
}

NavigationSpaceVehiculeInfo* GNSSNavigation::getSpaceVehiculeInfo() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_SpaceVehiculeInfo;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation space vehicule information... ");
  #endif

  return static_cast<NavigationSpaceVehiculeInfo*>(client->trySend(
    packet,
    MessageId::Navigation_SpaceVehiculeInfo
  ));
}

NavigationTimeGPS* GNSSNavigation::getTimeGPS() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_TimeGPS;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation GPS time... ");
  #endif

  return static_cast<NavigationTimeGPS*>(client->trySend(
    packet,
    MessageId::Navigation_TimeGPS
  ));
}

NavigationTimeUTC* GNSSNavigation::getTimeUTC() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_TimeUTC;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation UTC time... ");
  #endif

  return static_cast<NavigationTimeUTC*>(client->trySend(
    packet,
    MessageId::Navigation_TimeUTC
  ));
}

NavigationVelECEF* GNSSNavigation::getVelECEF() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_VelECEF;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation ECEF velocity... ");
  #endif

  return static_cast<NavigationVelECEF*>(client->trySend(
    packet,
    MessageId::Navigation_VelECEF
  ));
}

NavigationVelNED* GNSSNavigation::getVelNED() {
  UBXPacket* packet = new UBXPacket();
  packet->msgId = MessageId::Navigation_VelNED;
  packet->payloadLength = 0;

  #ifdef GNSS_DEBUG
    Serial.print("Getting navigation NED velocity... ");
  #endif

  return static_cast<NavigationVelNED*>(client->trySend(
    packet,
    MessageId::Navigation_VelNED
  ));
}
