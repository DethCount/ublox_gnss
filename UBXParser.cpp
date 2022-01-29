#include "GNSS.h"

UBXMessage* UBXParser::parse(UBXPacket* packet)
{
  bool successfull_parsing = false;

  switch (highByte(packet->msgId))
  {
    case MessageClass::ACK:
      return parseACK(packet);
    case MessageClass::Aiding:
      return parseAiding(packet);
    case MessageClass::Navigation:
      return parseNavigation(packet);
    case MessageClass::Configuration:
      return parseConfiguration(packet);
    case MessageClass::Information:
      return parseInformation(packet);
    case MessageClass::Log:
      return parseLog(packet);
    case MessageClass::Monitoring:
      return parseMonitoring(packet);
    case MessageClass::ReceiverManager:
      return parseReceiverManager(packet);
    case MessageClass::Timing:
      return parseTiming(packet);
    default:
      break;
  }

  #ifdef GNSS_DEBUG
    Serial.println("--- MSG ---");
    Serial.println(packet->msgId, HEX);

    for (int i = 0; i < packet->payloadLength; i++) {
      if (i > 0) {
        Serial.print(' ');
      }

      Serial.print(packet->payload[i] >> 4, HEX);
      Serial.print(packet->payload[i] & 0x0F, HEX);
    }

    Serial.println();
    Serial.println("!!!");
  #endif

  return packet;
}

UBXAck* UBXParser::parseACK(UBXPacket* packet)
{
  UBXAck *msg = new UBXAck(packet);
  msg->isValid &= packet->payloadLength == 2;

  if (msg->isValid) {
    msg->incomingMsgId = (MessageId) (
      extractU1(0, packet->payload) << 8
      | extractU1(1, packet->payload)
    );
  }

  #ifdef GNSS_DEBUG
    Serial.println("ACK ok");
    Serial.println(msg->msgId, HEX);
    Serial.println(msg->incomingMsgId, HEX);
  #endif

  return msg;
}

UBXMessage* UBXParser::parseAiding(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Aiding_Almanach:
      return parseAidingAlmanach(packet);
    case MessageId::Aiding_AlmanachPlus:
      return parseAidingAlmanachPlus(packet);
    case MessageId::Aiding_AOP:
      return parseAidingAOP(packet);
    case MessageId::Aiding_Ephemeris:
      return parseAidingEphemeris(packet);
    case MessageId::Aiding_HealthUTCIonosphere:
      return parseAidingHealthUTCIonosphere(packet);
    case MessageId::Aiding_Init:
      return parseAidingInit(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseNavigation(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Navigation_AOPStatus:
      return parseNavigationAOPStatus(packet);
    case MessageId::Navigation_Clock:
      return parseNavigationClock(packet);
    case MessageId::Navigation_DGPS:
      return parseNavigationDGPS(packet);
    case MessageId::Navigation_DillutionOfPrecision:
      return parseNavigationDOP(packet);
    case MessageId::Navigation_PosECEF:
      return parseNavigationPosECEF(packet);
    case MessageId::Navigation_PosLLH:
      return parseNavigationPosLLH(packet);
    case MessageId::Navigation_PosVT:
      return parseNavigationPosVT(packet);
    case MessageId::Navigation_SBAS:
      return parseNavigationSBAS(packet);
    case MessageId::Navigation_SOL:
      return parseNavigationSOL(packet);
    case MessageId::Navigation_Status:
      return parseNavigationStatus(packet);
    case MessageId::Navigation_SpaceVehiculeInfo:
      return parseNavigationSpaceVehiculeInfo(packet);
    case MessageId::Navigation_TimeGPS:
      return parseNavigationTimeGPS(packet);
    case MessageId::Navigation_TimeUTC:
      return parseNavigationTimeUTC(packet);
    case MessageId::Navigation_VelECEF:
      return parseNavigationVelECEF(packet);
    case MessageId::Navigation_VelNED:
      return parseNavigationVelNED(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseConfiguration(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Configuration_Antenna:
      return parseConfigurationAntenna(packet);
    case MessageId::Configuration_Datum:
      return parseConfigurationDatum(packet);
    case MessageId::Configuration_GlobalNavigationSatelliteSystem:
      return parseConfigurationGNSS(packet);
    case MessageId::Configuration_Information:
      return parseConfigurationInformation(packet);
    case MessageId::Configuration_InterferenceMonitor:
      return parseConfigurationInterferenceMonitor(packet);
    case MessageId::Configuration_LogFilter:
      return parseConfigurationLogFilter(packet);
    case MessageId::Configuration_Messaging:
      return parseConfigurationMessaging(packet);
    case MessageId::Configuration_Navigation:
      return parseConfigurationNavigation(packet);
    case MessageId::Configuration_NavigationExpert:
      return parseConfigurationNavigationExpert(packet);
    case MessageId::Configuration_NationalMarineElectronicsAssociation:
      return parseConfigurationNMEA(packet);
    case MessageId::Configuration_Port:
      return parseConfigurationPort(packet);
    case MessageId::Configuration_Power:
      return parseConfigurationPower(packet);
    case MessageId::Configuration_Rate:
      return parseConfigurationRate(packet);
    case MessageId::Configuration_RemoteInventory:
      return parseConfigurationRemoteInventory(packet);
    case MessageId::Configuration_Receiver:
      return parseConfigurationReceiver(packet);
    case MessageId::Configuration_SatelliteBasedAugmentationSystems:
      return parseConfigurationSBAS(packet);
    case MessageId::Configuration_TimePulse:
      return parseConfigurationTimePulse(packet);
    case MessageId::Configuration_USB:
      return parseConfigurationUSB(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseInformation(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Information_Debug:
      return parseInformationDebug(packet);
    case MessageId::Information_Error:
      return parseInformationError(packet);
    case MessageId::Information_Notice:
      return parseInformationNotice(packet);
    case MessageId::Information_Test:
      return parseInformationTest(packet);
    case MessageId::Information_Warning:
      return parseInformationWarning(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseLog(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Log_FindTime:
      return parseLogFindTime(packet);
    case MessageId::Log_Info:
      return parseLogInfo(packet);
    case MessageId::Log_RetrievePosition:
      return parseLogRetrievePosition(packet);
    case MessageId::Log_RetrieveString:
      return parseLogRetrieveString(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseMonitoring(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Monitoring_Hardware:
      return parseMonitoringHardware(packet);
    case MessageId::Monitoring_HardwareExtended:
      return parseMonitoringHardwareExtended(packet);
    case MessageId::Monitoring_IO:
      return parseMonitoringIO(packet);
    case MessageId::Monitoring_MsgParseProcess:
      return parseMonitoringMsgParseProcess(packet);
    case MessageId::Monitoring_Receiver:
      return parseMonitoringReceiver(packet);
    case MessageId::Monitoring_ReceiverBuffer:
      return parseMonitoringReceiverBuffer(packet);
    case MessageId::Monitoring_TransmitterBuffer:
      return parseMonitoringTransmitterBuffer(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseReceiverManager(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::ReceiverManager_Almanach:
      return parseReceiverManagerAlmanach(packet);
    case MessageId::ReceiverManager_Ephemeris:
      return parseReceiverManagerEphemeris(packet);
    case MessageId::ReceiverManager_Raw:
      return parseReceiverManagerRaw(packet);
    case MessageId::ReceiverManager_SVStatus:
      return parseReceiverManagerSpaceVehiculeInfo(packet);
    default:
      break;
  }

  return packet;
}

UBXMessage* UBXParser::parseTiming(UBXPacket* packet)
{
  switch (packet->msgId)
  {
    case MessageId::Timing_Mark:
      return parseTimingMark(packet);
    case MessageId::Timing_Pulse:
      return parseTimingPulse(packet);
    case MessageId::Timing_Verification:
      return parseTimingVerification(packet);
    default:
      break;
  }

  return packet;
}

AidingAlmanach* UBXParser::parseAidingAlmanach(UBXPacket* packet)
{
  AidingAlmanach *msg = new AidingAlmanach(packet);
  msg->isValid &= packet->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU4(0, packet->payload);
  msg->week = extractU4(4, packet->payload);

  msg->isValid &= (msg->week == 0 && packet->payloadLength == 8)
    || (msg->week != 0 && packet->payloadLength == 40);

  if (!msg->isValid || packet->payloadLength <= 8) {
    return msg;
  }

  for (short i = 0; i < AidingAlmanach::MAX_NB_DWORD; i++) {
    msg->dword[i] = extractU4(8 + i * 4, packet->payload);
  }

  return msg;
}

AidingAlmanachPlus* UBXParser::parseAidingAlmanachPlus(UBXPacket* packet)
{
  AidingAlmanachPlus *msg = new AidingAlmanachPlus(packet);
  msg->isValid &= packet->payloadLength >= 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->idSize = extractU1(0, packet->payload);
  msg->type = extractU1(1, packet->payload);
  msg->ofs = extractU2(2, packet->payload);
  msg->size = extractU2(4, packet->payload);
  msg->fileId = extractU2(6, packet->payload);
  msg->dataSize = extractU2(8, packet->payload);
  msg->id1 = extractU1(10, packet->payload);
  msg->id2 = extractU1(11, packet->payload);
  msg->id3 = extractU4(12, packet->payload);

  msg->isValid &= packet->payloadLength == 16 + msg->dataSize;
  if (!msg->isValid) {
    return msg;
  }

  for (int i = 0; i < msg->dataSize; i++) {
    msg->data[i] = packet->payload[16 + i];
  }

  return msg;
}

AidingAOP* UBXParser::parseAidingAOP(UBXPacket* packet)
{
  AidingAOP *msg = new AidingAOP(packet);
  msg->isValid &= packet->payloadLength == 60
    || packet->payloadLength == 204;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU1(0, packet->payload);
  msg->dataSize = packet->payloadLength - 1;

  msg->isValid &= packet->payloadLength == 1 + msg->dataSize;

  if (!msg->isValid) {
    return msg;
  }

  for (int i = 0; i < msg->dataSize; i++) {
    msg->data[i] = packet->payload[1 + i];
  }

  return msg;
}

AidingEphemeris* UBXParser::parseAidingEphemeris(UBXPacket* packet)
{
  AidingEphemeris *msg = new AidingEphemeris(packet);
  msg->isValid &= packet->payloadLength == 8
    || packet->payloadLength == 104;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU4(0, packet->payload);
  msg->how = extractU4(4, packet->payload);

  msg->isValid &= msg->how == 0
    || (msg->how != 0 && packet->payloadLength == 104);

  if (msg->how != 0) {
    short idx = 8;

    msg->subframe1 = new GPSSubframe1();
    for (short i = 0; i < msg->subframe1->nbWords; i++) {
      msg->subframe1->words[i] = extractU4(idx, packet->payload);
      idx += 4;
    }

    msg->subframe2 = new GPSSubframe2();
    for (short i = 0; i < msg->subframe2->nbWords; i++) {
      msg->subframe2->words[i] = extractU4(idx, packet->payload);
      idx += 4;
    }

    msg->subframe3 = new GPSSubframe3();
    for (short i = 0; i < msg->subframe3->nbWords; i++) {
      msg->subframe3->words[i] = extractU4(idx, packet->payload);
      idx += 4;
    }
  }

  return msg;
}

AidingHealthUTCIonosphere* UBXParser::parseAidingHealthUTCIonosphere(
  UBXPacket* packet
) {
  AidingHealthUTCIonosphere *msg = new AidingHealthUTCIonosphere(packet);
  msg->isValid &= packet->payloadLength == 72;

  if (!msg->isValid) {
    return msg;
  }

  msg->health = extractU4(0, packet->payload);
  msg->utcA0 = extractR8(4, packet->payload);
  msg->utcA1 = extractR8(12, packet->payload);
  msg->utcTOW = extractI4(20, packet->payload);
  msg->utcWNT = extractI2(24, packet->payload);
  msg->utcLS = extractI2(26, packet->payload);
  msg->utcWNF = extractI2(28, packet->payload);
  msg->utcDN = extractI2(30, packet->payload);
  msg->utcLSF = extractI2(32, packet->payload);
  msg->utcSpare = extractI2(34, packet->payload);
  msg->klobA0 = extractR4(36, packet->payload);
  msg->klobA1 = extractR4(40, packet->payload);
  msg->klobA2 = extractR4(44, packet->payload);
  msg->klobA3 = extractR4(48, packet->payload);
  msg->klobB0 = extractR4(52, packet->payload);
  msg->klobB1 = extractR4(56, packet->payload);
  msg->klobB2 = extractR4(60, packet->payload);
  msg->klobB3 = extractR4(64, packet->payload);
  msg->flags = extractX4(68, packet->payload);

  return msg;
}

AidingInit* UBXParser::parseAidingInit(UBXPacket* packet) {
  AidingInit *msg = new AidingInit(packet);
  msg->isValid &= packet->payloadLength == 48;

  if (!msg->isValid) {
    return msg;
  }

  msg->ecefXOrLat = extractI4(0, packet->payload);
  msg->ecefYOrLon = extractI4(4, packet->payload);
  msg->ecefZOrAlt = extractI4(8, packet->payload);
  msg->posAcc = extractU4(12, packet->payload);
  msg->tmCfg = extractX2(16, packet->payload);
  msg->wnoOrDate = extractU2(18, packet->payload);
  msg->towOrTime = extractU4(20, packet->payload);
  msg->towNs = extractI4(24, packet->payload);
  msg->tAccMs = extractU4(28, packet->payload);
  msg->tAccNs = extractU4(32, packet->payload);
  msg->clkDOrFreq = extractI4(36, packet->payload);
  msg->clkDAccOrFreqAcc = extractU4(40, packet->payload);
  msg->flags = extractX4(44, packet->payload);

  return msg;
}

NavigationAOPStatus* UBXParser::parseNavigationAOPStatus(UBXPacket* packet)
{
  NavigationAOPStatus *msg = new NavigationAOPStatus(packet);
  msg->isValid &= packet->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->aopCfg = extractU1(4, packet->payload);
  msg->status = (AOPStatus) extractU1(5, packet->payload);
  // reserved0 U1
  // reserved1 U1
  msg->availGPS = extractU4(8, packet->payload);
  // reserved2 U4
  // reserved3 U4

  return msg;
}

NavigationClock* UBXParser::parseNavigationClock(UBXPacket* packet)
{
  NavigationClock *msg = new NavigationClock(packet);
  msg->isValid &= packet->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->clkB = extractI4(4, packet->payload);
  msg->clkD = extractI4(8, packet->payload);
  msg->tAcc = extractU4(12, packet->payload);
  msg->fAcc = extractU4(16, packet->payload);

  return msg;
}

NavigationDGPS* UBXParser::parseNavigationDGPS(UBXPacket* packet)
{
  NavigationDGPS *msg = new NavigationDGPS(packet);
  msg->isValid &= packet->payloadLength >= 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->age = extractI4(4, packet->payload);
  msg->baseId = extractI2(8, packet->payload);
  msg->baseHealth = extractI2(10, packet->payload);
  msg->numCh = extractU1(12, packet->payload);
  msg->status = (DGPSStatus) extractU1(13, packet->payload);
  // reserved1 U2

  msg->isValid &= packet->payloadLength = 16 + 12 * msg->numCh
    && msg->numCh <= GNSS_MAX_SVID;

  if (!msg->isValid) {
    return msg;
  }

  for (short i = 0; i < msg->numCh; i++) {
    NavigationDGPSChannel* chan = new NavigationDGPSChannel();
    int idx =  16 + i * 12;
    chan->svid = extractU1(idx, packet->payload);
    chan->flags = extractX1(idx + 1, packet->payload);
    chan->ageC = extractU2(idx + 2, packet->payload);
    chan->prc = extractU4(idx + 4, packet->payload);
    chan->prrc = extractU4(idx + 8, packet->payload);

    msg->channels[i] = chan;
  }

  return msg;
}

NavigationDOP* UBXParser::parseNavigationDOP(UBXPacket* packet)
{
  NavigationDOP *msg = new NavigationDOP(packet);
  msg->isValid &= packet->payloadLength == 18;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->gDOP = (double) extractU2(4, packet->payload) * 1e-2;
  msg->pDOP = (double) extractU2(6, packet->payload) * 1e-2;
  msg->tDOP = (double) extractU2(8, packet->payload) * 1e-2;
  msg->vDOP = (double) extractU2(10, packet->payload) * 1e-2;
  msg->hDOP = (double) extractU2(12, packet->payload) * 1e-2;
  msg->nDOP = (double) extractU2(14, packet->payload) * 1e-2;
  msg->eDOP = (double) extractU2(16, packet->payload) * 1e-2;

  return msg;
}

NavigationPosECEF* UBXParser::parseNavigationPosECEF(UBXPacket* packet)
{
  NavigationPosECEF *msg = new NavigationPosECEF(packet);
  msg->isValid &= packet->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->ecefX = extractI4(4, packet->payload);
  msg->ecefY = extractI4(8, packet->payload);
  msg->ecefZ = extractI4(12, packet->payload);
  msg->pAcc = extractU4(16, packet->payload);

  return msg;
}

NavigationPosLLH* UBXParser::parseNavigationPosLLH(UBXPacket* packet)
{
  NavigationPosLLH *msg = new NavigationPosLLH(packet);
  msg->isValid &= packet->payloadLength == 28;
  if (!msg->isValid) {
    return msg;
  }

  #ifdef GNSS_DEBUG
    for (int i = 0; i < packet->payloadLength; i++) {
      Serial.println(packet->payload[i], HEX);
    }
  #endif

  msg->iTOW = extractU4(0, packet->payload);
  msg->longitude = (double)extractI4(4, packet->payload) * 1e-7;
  msg->latitude = (double)extractI4(8, packet->payload) * 1e-7;
  msg->height = extractI4(12, packet->payload);
  msg->hMSL = extractI4(16, packet->payload);
  msg->hAcc = extractU4(20, packet->payload);
  msg->vAcc = extractU4(24, packet->payload);

  return msg;
}

NavigationPosVT* UBXParser::parseNavigationPosVT(UBXPacket* packet)
{
  NavigationPosVT *msg = new NavigationPosVT(packet);
  msg->isValid &= packet->payloadLength == 84;
  if (!msg->isValid) {
    return msg;
  }

  #ifdef GNSS_DEBUG
    for (int i = 0; i < packet->payloadLength; i++) {
      Serial.println(packet->payload[i], HEX);
    }
  #endif

  msg->iTOW = extractU4(0, packet->payload);
  msg->year = extractU2(4, packet->payload);
  msg->month = extractU1(6, packet->payload);
  msg->day = extractU1(7, packet->payload);
  msg->hour = extractU1(8, packet->payload);
  msg->minute = extractU1(9, packet->payload);
  msg->second = extractU1(10, packet->payload);
  msg->valid = extractX1(11, packet->payload);
  msg->tAcc = extractU4(12, packet->payload);
  msg->nano = extractI4(16, packet->payload);
  msg->fixType = (GNSSFixType) extractU1(20, packet->payload);
  msg->flags = extractX1(21, packet->payload);
  // reserved1 U1
  msg->numSV = extractU1(23, packet->payload);
  msg->longitude = (double)extractI4(24, packet->payload) * 1e-7;
  msg->latitude = (double)extractI4(28, packet->payload) * 1e-7;
  msg->height = extractI4(32, packet->payload);
  msg->hMSL = extractI4(36, packet->payload);
  msg->hAcc = extractU4(40, packet->payload);
  msg->vAcc = extractU4(44, packet->payload);
  msg->velocityNorth = (double) extractI4(48, packet->payload);
  msg->velocityEast = (double) extractI4(52, packet->payload);
  msg->velocityDown = (double) extractI4(56, packet->payload);
  msg->groundSpeed = (double) extractI4(60, packet->payload);
  msg->heading = (double) extractI4(64, packet->payload) * 1e-5;
  msg->sAcc = extractU4(68, packet->payload);
  msg->headingAcc = (double) extractU4(72, packet->payload) * 1e-5;
  msg->pDOP = (double) extractU2(76, packet->payload) * 1e-2;
  // reserved2 X2
  // reserved3 U4

  return msg;
}

NavigationSBAS* UBXParser::parseNavigationSBAS(UBXPacket* packet)
{
  NavigationSBAS *msg = new NavigationSBAS(packet);
  msg->isValid &= packet->payloadLength >= 12;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->geo = extractU1(4, packet->payload);
  msg->mode = (SBASMode) extractU1(5, packet->payload);
  msg->sys = (SBASSystem) extractI1(6, packet->payload);
  msg->service = extractX1(7, packet->payload);
  msg->cnt = extractU1(8, packet->payload);
  // reserved0 U1[3]

  msg->isValid &= packet->payloadLength == 12 + 12 * msg->cnt
    && msg->cnt <= GNSS_MAX_SVID;

  if (!msg->isValid) {
    return msg;
  }

  for (short i = 0; i < msg->cnt; i++) {
    int idx = 12 + i * 12;
    NavigationSBASItem* item = new NavigationSBASItem();
    item->svid = extractU1(idx, packet->payload);
    item->flags = extractX1(idx + 1, packet->payload);
    item->udre = extractX1(idx + 2, packet->payload);
    item->svSys = (SBASSystem) extractI1(idx + 3, packet->payload);
    item->svService = extractX1(idx + 4, packet->payload);
    // reserved1 U1
    item->prc = extractI2(idx + 6, packet->payload);
    // reserved2 U2
    item->ic = extractI2(idx + 10, packet->payload);

    msg->items[i] = item;
  }

  return msg;
}

NavigationSOL* UBXParser::parseNavigationSOL(UBXPacket* packet)
{
  NavigationSOL *msg = new NavigationSOL(packet);
  msg->isValid &= packet->payloadLength == 52;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->fTOW = extractI4(4, packet->payload);
  msg->week = extractI2(8, packet->payload);
  msg->gpsFix = (GNSSFixType) extractU1(10, packet->payload);
  msg->flags = extractX1(11, packet->payload);
  msg->ecefX = extractI4(12, packet->payload);
  msg->ecefY = extractI4(16, packet->payload);
  msg->ecefZ = extractI4(20, packet->payload);
  msg->pAcc = extractU4(24, packet->payload);
  msg->ecefVX = extractI4(28, packet->payload);
  msg->ecefVY = extractI4(32, packet->payload);
  msg->ecefVZ = extractI4(36, packet->payload);
  msg->sAcc = extractU4(40, packet->payload);
  msg->pDOP = (double) extractU2(44, packet->payload) * 1e-2;
  // reserved1 U1
  msg->numSV = extractU1(47, packet->payload);
  // reserved2 U4

  return msg;
}

NavigationStatus* UBXParser::parseNavigationStatus(UBXPacket* packet)
{
  NavigationStatus *msg = new NavigationStatus(packet);
  msg->isValid &= packet->payloadLength == 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->gpsFix = (GNSSFixType) extractU1(4, packet->payload);
  msg->flags = extractX1(5, packet->payload);
  msg->fixStat = extractX1(6, packet->payload);
  msg->flags2 = extractX1(7, packet->payload);
  msg->ttff = extractU4(8, packet->payload);
  msg->msss = extractU4(12, packet->payload);

  return msg;
}

NavigationSpaceVehiculeInfo* UBXParser::parseNavigationSpaceVehiculeInfo(
  UBXPacket* packet
) {
  NavigationSpaceVehiculeInfo *msg = new NavigationSpaceVehiculeInfo(packet);
  msg->isValid &= packet->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->numCh = extractU1(4, packet->payload);
  msg->globalFlags = extractX1(5, packet->payload);
  // reserved2 U2

  msg->isValid &= packet->payloadLength == 8 + 12 * msg->numCh
    && msg->numCh <= GNSS_MAX_SVID;

  if (!msg->isValid) {
    return msg;
  }

  for (short i = 0; i < msg->numCh; i++) {
    int idx = 8 + 12 * i;
    NavigationSpaceVehicule* sv = new NavigationSpaceVehicule();
    sv->chn = extractU1(idx, packet->payload);
    sv->svid = extractU1(idx + 1, packet->payload);
    sv->flags = extractX1(idx + 2, packet->payload);
    sv->quality = extractX1(idx + 3, packet->payload);
    sv->cno = extractU1(idx + 4, packet->payload);
    sv->elev = extractI1(idx + 5, packet->payload);
    sv->azim = extractI2(idx + 6, packet->payload);
    sv->prRes = extractI4(idx + 8, packet->payload);

    msg->spaceVehicules[i] = sv;
  }

  return msg;
}

NavigationTimeGPS* UBXParser::parseNavigationTimeGPS(UBXPacket* packet)
{
  NavigationTimeGPS *msg = new NavigationTimeGPS(packet);
  msg->isValid &= packet->payloadLength == 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->fTOW = extractI4(4, packet->payload);
  msg->week = extractI2(8, packet->payload);
  msg->leapS = extractI1(10, packet->payload);
  msg->valid = extractX1(11, packet->payload);
  msg->tAcc = extractU4(12, packet->payload);

  msg->isValid &= msg->valid == 0x07;

  return msg;
}

NavigationTimeUTC* UBXParser::parseNavigationTimeUTC(UBXPacket* packet)
{
  NavigationTimeUTC *msg = new NavigationTimeUTC(packet);
  msg->isValid &= packet->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  Serial.println("TimeUTC");
  for (int i = 0; i < packet->payloadLength; i++) {
    Serial.println(packet->payload[i], HEX);
  }
  Serial.println("end TimeUTC");

  msg->iTOW = extractU4(0, packet->payload);
  msg->tAcc = extractU4(4, packet->payload);
  msg->nano = extractI4(8, packet->payload);
  msg->year = extractU2(12, packet->payload);
  msg->month = extractU1(14, packet->payload);
  msg->day = extractU1(15, packet->payload);
  msg->hour = extractU1(16, packet->payload);
  msg->minute = extractU1(17, packet->payload);
  msg->second = extractU1(18, packet->payload);
  msg->flags = extractX1(19, packet->payload);
  msg->isValid &= msg->flags == 0x07;

  return msg;
}

NavigationVelECEF* UBXParser::parseNavigationVelECEF(UBXPacket* packet)
{
  NavigationVelECEF *msg = new NavigationVelECEF(packet);
  msg->isValid &= packet->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->ecefVX = extractI4(4, packet->payload);
  msg->ecefVY = extractI4(8, packet->payload);
  msg->ecefVZ = extractI4(12, packet->payload);
  msg->sAcc = extractU4(16, packet->payload);

  return msg;
}

NavigationVelNED* UBXParser::parseNavigationVelNED(UBXPacket* packet)
{
  NavigationVelNED *msg = new NavigationVelNED(packet);
  msg->isValid &= packet->payloadLength == 36;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->velocityNorth = extractI4(4, packet->payload);
  msg->velocityEast = extractI4(8, packet->payload);
  msg->velocityDown = extractI4(12, packet->payload);
  msg->speed = extractU4(16, packet->payload);
  msg->gSpeed = extractU4(20, packet->payload);
  msg->heading = (double) extractI4(24, packet->payload) * 1e-5;
  msg->sAcc = extractU4(28, packet->payload);
  msg->cAcc = (double) extractU4(32, packet->payload) * 1e-5;

  return msg;
}

ConfigurationAntenna* UBXParser::parseConfigurationAntenna(UBXPacket* packet)
{
  ConfigurationAntenna *msg = new ConfigurationAntenna(packet);
  msg->isValid &= packet->payloadLength == 4;

  if (!msg->isValid) {
    return msg;
  }

  msg->flags = extractX2(0, packet->payload);
  msg->pins = extractX2(2, packet->payload);

  return msg;
}

ConfigurationDatum* UBXParser::parseConfigurationDatum(UBXPacket* packet)
{
  ConfigurationDatum *msg = new ConfigurationDatum(packet);
  msg->isValid &= packet->payloadLength == 52;

  if (!msg->isValid) {
    return msg;
  }

  msg->datumNum = extractU2(0, packet->payload);
  extractCH(2, packet->payload, ConfigurationDatum::NAME_SIZE, msg->datumName);
  msg->majA = extractR8(8, packet->payload);
  msg->flat = extractR8(16, packet->payload);
  msg->dX = extractR4(24, packet->payload);
  msg->dY = extractR4(28, packet->payload);
  msg->dZ = extractR4(32, packet->payload);
  msg->rotX = extractR4(36, packet->payload);
  msg->rotY = extractR4(40, packet->payload);
  msg->rotZ = extractR4(44, packet->payload);
  msg->scale = extractR4(48, packet->payload);

  return msg;
}

ConfigurationGNSS* UBXParser::parseConfigurationGNSS(UBXPacket* packet)
{
  ConfigurationGNSS *msg = new ConfigurationGNSS(packet);
  msg->isValid &= packet->payloadLength >= 4;

  if (!msg->isValid) {
    return msg;
  }

  msg->msgVer = extractU1(0, packet->payload);
  msg->numTrkChHw = extractU1(1, packet->payload);
  msg->numTrkChUse = extractU1(2, packet->payload);
  msg->numConfigBlocks = extractU1(3, packet->payload);

  msg->isValid &= packet->payloadLength == 4 + 8 * msg->numConfigBlocks;

  if (!msg->isValid || msg->numConfigBlocks <= 0) {
    return msg;
  }

  uint16_t idx = 4;
  for (unsigned short i = 0; i < ConfigurationGNSS::MAX_NB_BLOCKS; i++) {
    ConfigurationGNSSBlock *block = new ConfigurationGNSSBlock();
    block->gnssId = extractU1(idx, packet->payload);
    block->resTrkCh = extractU1(idx + 1, packet->payload);
    block->maxTrkCh = extractU1(idx + 2, packet->payload);
    // reserved1 U1
    block->maxTrkCh = extractX4(idx + 4, packet->payload);

    msg->blocks[i] = block;
    idx += 8;
  }

  return msg;
}

ConfigurationInformation* UBXParser::parseConfigurationInformation(
  UBXPacket* packet,
  uint16_t startIdx
) {
  ConfigurationInformation *msg = new ConfigurationInformation(packet);
  msg->isValid &= packet->payloadLength >= startIdx + 10;

  if (!msg->isValid) {
    return msg;
  }

  msg->protocolId = (GNSSProtocol) extractU1(startIdx, packet->payload);
  // reserved0 U1
  // reserved1 U2

  for (uint8_t i = 0; i < ConfigurationInformation::MAX_NB_MSG_CLASS; i++) {
    msg->infMsgMask[i] = extractX1(startIdx + 4 + i, packet->payload);
  }

  if (packet->payloadLength > startIdx + 10) {
    msg->next = parseConfigurationInformation(packet, startIdx + 10);
  }

  return msg;
}

ConfigurationInterferenceMonitor* UBXParser::parseConfigurationInterferenceMonitor(
  UBXPacket* packet
) {
  ConfigurationInterferenceMonitor *msg
    = new ConfigurationInterferenceMonitor(packet);

  msg->isValid &= packet->payloadLength == 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->config = extractX4(0, packet->payload);
  msg->config2 = extractX4(4, packet->payload);

  return msg;
}

ConfigurationLogFilter* UBXParser::parseConfigurationLogFilter(
  UBXPacket* packet
) {
  ConfigurationLogFilter *msg = new ConfigurationLogFilter(packet);
  msg->isValid &= packet->payloadLength == 12;

  if (!msg->isValid) {
    return msg;
  }

  msg->version = extractU1(0, packet->payload);
  msg->flags = extractX1(1, packet->payload);
  msg->minInterval = extractU2(2, packet->payload);
  msg->timeThreshold = extractU2(4, packet->payload);
  msg->speedThreshold = extractU2(6, packet->payload);
  msg->positionThreshold = extractU4(8, packet->payload);

  return msg;
}

ConfigurationMessaging* UBXParser::parseConfigurationMessaging(
  UBXPacket* packet
) {
  ConfigurationMessaging *msg = new ConfigurationMessaging(packet);
  msg->isValid &= packet->payloadLength == 3;

  if (!msg->isValid) {
    return msg;
  }

  msg->msgClass = extractU1(0, packet->payload);
  msg->msgId = (msg->msgClass << 8) | extractX1(1, packet->payload);
  msg->rate = extractU1(2, packet->payload);

  return msg;
}

ConfigurationNavigation* UBXParser::parseConfigurationNavigation(
  UBXPacket* packet
) {
  ConfigurationNavigation *msg = new ConfigurationNavigation(packet);
  msg->isValid &= packet->payloadLength == 36;

  if (!msg->isValid) {
    return msg;
  }

  msg->mask = extractX2(0, packet->payload);
  msg->dynModel = (NavigationMode) extractU1(2, packet->payload);
  msg->fixMode = (GNSSFixType) extractU1(3, packet->payload);
  msg->fixedAlt = (double) extractI4(4, packet->payload) * 1e-2;
  msg->fixedAltVar = (double) extractU4(8, packet->payload) * 1e-4;
  msg->minElev = extractI1(12, packet->payload);
  msg->drLimit = extractU1(13, packet->payload);
  msg->pDOP = (double) extractU2(14, packet->payload) * 1e-1;
  msg->tDOP = (double) extractU2(16, packet->payload) * 1e-1;
  msg->pAcc = extractU2(18, packet->payload);
  msg->tAcc = extractU2(20, packet->payload);
  msg->staticHoldThresh = extractU1(22, packet->payload);
  msg->dgpsTimeOut = extractU1(23, packet->payload);
  msg->cnoThreshNumSVs = extractU1(24, packet->payload);
  msg->cnoThresh = extractU1(25, packet->payload);
  // reserved2 U2
  // reserved3 U4
  // reserved4 U4

  return msg;
}

ConfigurationNavigationExpert* UBXParser::parseConfigurationNavigationExpert(
  UBXPacket* packet
) {
  ConfigurationNavigationExpert *msg
    = new ConfigurationNavigationExpert(packet);

  msg->isValid &= packet->payloadLength == 40;

  if (!msg->isValid) {
    return msg;
  }

  msg->version = extractU2(0, packet->payload);
  msg->mask1 = extractX2(2, packet->payload);
  // reserved0 U4
  // reserved1 U1
  // reserved2 U1
  msg->minSVs = extractU1(10, packet->payload);
  msg->maxSVs = extractU1(11, packet->payload);
  msg->minCNO = extractU1(12, packet->payload);
  // reserved5 U1
  msg->iniFix3D = 0x01 == extractU1(13, packet->payload);
  // reserved6 U1
  // reserved7 U1
  // reserved8 U1
  msg->wknRollover = extractU2(18, packet->payload);
  // reserved9 U4
  // reserved10 U1
  // reserved11 U1
  msg->usePPP = 0x01 == extractU1(26, packet->payload);
  msg->aopCfg = extractU1(27, packet->payload);
  // reserved12 U1
  // reserved13 U1
  msg->aopOrbMaxErr = extractU2(30, packet->payload);
  // reserved14 U1
  // reserved15 U1
  // reserved3 U2
  // reserved4 U4

  return msg;
}

ConfigurationNMEA* UBXParser::parseConfigurationNMEA(UBXPacket* packet) {
  ConfigurationNMEA *msg = new ConfigurationNMEA(packet);
  msg->isValid &= packet->payloadLength >= 4;

  if (!msg->isValid) {
    return msg;
  }

  msg->filter = extractX1(0, packet->payload);
  msg->nmeaVersion = extractU1(1, packet->payload);
  msg->numSV = extractU1(2, packet->payload);
  msg->flags = extractX1(3, packet->payload);

  if (packet->payloadLength <= 4) {
    return msg;
  }

  msg->isValid &= packet->payloadLength == 12;

  if (!msg->isValid) {
    return msg;
  }

  msg->gnssToFilter = extractX4(4, packet->payload);
  msg->svNumbering = extractU1(8, packet->payload);
  msg->mainTalkerId = extractU1(9, packet->payload);
  msg->gsvTalkerId = extractU1(10, packet->payload);
  // reserved U1

  return msg;
}

ConfigurationPort* UBXParser::parseConfigurationPort(
  UBXPacket* packet,
  uint16_t startIdx
) {
  ConfigurationPort *msg = new ConfigurationPort(packet);
  msg->isValid &= packet->payloadLength >= startIdx + 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->portId = (PortId) extractU1(startIdx, packet->payload);
  // reserved0 U1
  msg->txReady = extractX2(startIdx + 2, packet->payload);
  msg->mode = extractX4(startIdx + 4, packet->payload);
  msg->baudRate = (PortRate) extractU4(startIdx + 8, packet->payload);
  msg->inProtoMask = extractX2(startIdx + 12, packet->payload);
  msg->outProtoMask = extractX2(startIdx + 14, packet->payload);
  msg->flags = extractX2(startIdx + 16, packet->payload);
  // reserved5 U2

  if (packet->payloadLength > startIdx + 20) {
    msg->next = parseConfigurationPort(packet, startIdx + 20);
  }

  return msg;
}

ConfigurationPower* UBXParser::parseConfigurationPower(
  UBXPacket* packet
) {
  ConfigurationPower *msg = new ConfigurationPower(packet);
  msg->isValid &= packet->payloadLength == 44;

  if (!msg->isValid) {
    return msg;
  }

  msg->version = extractU1(0, packet->payload);
  // reserved1 U1
  // reserved2 U1
  // reserved3 U1
  msg->flags = extractX4(4, packet->payload);
  msg->updatePeriod = extractU4(8, packet->payload);
  msg->searchPeriod = extractU4(12, packet->payload);
  msg->gridOffset = extractU4(16, packet->payload);
  msg->onTime = extractU2(18, packet->payload);
  msg->minAcqTime = extractU2(20, packet->payload);
  // reserved4 U2
  // reserved5 U2
  // reserved6 U4
  // reserved7 U4
  // reserved8 U1
  // reserved9 U1
  // reserved10 U2
  // reserved11 U4

  return msg;
}

ConfigurationRate* UBXParser::parseConfigurationRate(UBXPacket* packet)
{
  ConfigurationRate *msg = new ConfigurationRate(packet);
  msg->isValid &= packet->payloadLength == 6;

  if (!msg->isValid) {
    return msg;
  }

  msg->measRate = (DataRate) extractU2(0, packet->payload);
  msg->navRate = extractU2(2, packet->payload);
  msg->timeRef = (GNSSReferenceTime) extractU2(4, packet->payload);

  return msg;
}

ConfigurationRemoteInventory* UBXParser::parseConfigurationRemoteInventory(
  UBXPacket* packet
) {
  ConfigurationRemoteInventory *msg = new ConfigurationRemoteInventory(packet);
  msg->isValid &= packet->payloadLength >= 1
    && packet->payloadLength - 1 <= ConfigurationRemoteInventory::MAX_DATA_SIZE;

  if (!msg->isValid) {
    return msg;
  }

  msg->flags = extractX1(0, packet->payload);
  msg->dataSize = packet->payloadLength - 1;

  for (int i = 0; i < msg->dataSize; i++) {
    msg->data[i] = packet->payload[1 + i];
  }

  return msg;
}

ConfigurationReceiver* UBXParser::parseConfigurationReceiver(
  UBXPacket* packet
) {
  ConfigurationReceiver *msg = new ConfigurationReceiver(packet);
  msg->isValid &= packet->payloadLength == 2;

  if (!msg->isValid) {
    return msg;
  }

  // reserved1 U1
  msg->lpMode = (LowPowerMode) extractU1(1, packet->payload);

  return msg;
}

ConfigurationSBAS* UBXParser::parseConfigurationSBAS(UBXPacket* packet) {
  ConfigurationSBAS *msg = new ConfigurationSBAS(packet);
  msg->isValid &= packet->payloadLength == 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->mode = extractX1(0, packet->payload);
  msg->usage = extractX1(1, packet->payload);
  msg->maxSBAS = extractU1(2, packet->payload);
  msg->scanmode2 = extractX1(3, packet->payload);
  msg->scanmode1 = extractX4(4, packet->payload);

  return msg;
}

ConfigurationTimePulse* UBXParser::parseConfigurationTimePulse(
  UBXPacket* packet
) {
  ConfigurationTimePulse *msg = new ConfigurationTimePulse(packet);
  msg->isValid &= packet->payloadLength == 32;

  if (!msg->isValid) {
    return msg;
  }

  msg->tpIdx = extractU1(0, packet->payload);
  // reserved0 U1
  // reserved1 U2
  msg->antCableDelay = extractI2(4, packet->payload);
  msg->rfGroupDelay = extractI2(6, packet->payload);
  msg->freqPeriod = extractU4(8, packet->payload);
  msg->freqPeriodLock = extractU4(12, packet->payload);
  msg->pulseLenRatio = extractU4(16, packet->payload);
  msg->pulseLenRatioLock = extractU4(20, packet->payload);
  msg->userConfigDelay = extractI4(24, packet->payload);
  msg->flags = extractX4(28, packet->payload);

  return msg;
}

ConfigurationUSB* UBXParser::parseConfigurationUSB(UBXPacket* packet) {
  ConfigurationUSB *msg = new ConfigurationUSB(packet);
  msg->isValid &= packet->payloadLength == 12
    + ConfigurationUSB::VENDOR_NAME_SIZE
    + ConfigurationUSB::PRODUCT_NAME_SIZE
    + ConfigurationUSB::SERIAL_NUMBER_SIZE;

  if (!msg->isValid) {
    return msg;
  }

  msg->vendorId = extractU2(0, packet->payload);
  msg->productId = extractU2(2, packet->payload);
  // reserved1 U2
  // reserved2 U2
  msg->powerConsumption = extractU2(8, packet->payload);
  msg->flags = extractX2(10, packet->payload);

  int idx = 12;

  extractCH(
    12,
    packet->payload,
    ConfigurationUSB::VENDOR_NAME_SIZE,
    msg->vendorString
  );
  idx += ConfigurationUSB::VENDOR_NAME_SIZE;

  extractCH(
    idx,
    packet->payload,
    ConfigurationUSB::PRODUCT_NAME_SIZE,
    msg->productString
  );
  idx += ConfigurationUSB::PRODUCT_NAME_SIZE;

  extractCH(
    idx,
    packet->payload,
    ConfigurationUSB::SERIAL_NUMBER_SIZE,
    msg->serialNumber
  );

  return msg;
}

InformationDebug* UBXParser::parseInformationDebug(UBXPacket* packet) {
  return static_cast<InformationDebug*>(packet);
}

InformationError* UBXParser::parseInformationError(UBXPacket* packet) {
  return static_cast<InformationError*>(packet);
}

InformationNotice* UBXParser::parseInformationNotice(UBXPacket* packet) {
  return static_cast<InformationNotice*>(packet);
}

InformationTest* UBXParser::parseInformationTest(UBXPacket* packet) {
  return static_cast<InformationTest*>(packet);
}

InformationWarning* UBXParser::parseInformationWarning(UBXPacket* packet) {
  return static_cast<InformationWarning*>(packet);
}

LogFindTime* UBXParser::parseLogFindTime(UBXPacket* packet) {
  LogFindTime *msg = new LogFindTime(packet);
  msg->isValid &= packet->payloadLength == 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->version = extractU1(0, packet->payload);
  msg->type = extractU1(1, packet->payload);
  // reserved1 U2
  msg->entryNumber = extractU4(4, packet->payload);

  return msg;
}

LogInfo* UBXParser::parseLogInfo(UBXPacket* packet) {
  LogInfo *msg = new LogInfo(packet);
  msg->isValid &= packet->payloadLength == 48;

  if (!msg->isValid) {
    return msg;
  }

  msg->version = extractU1(0, packet->payload);
  // reserved1 U1[3]
  msg->filestoreCapacity = extractU4(4, packet->payload);
  // reserved2 U4
  // reserved3 U4
  msg->currentMaxLogSize = extractU4(16, packet->payload);
  msg->currentLogSize = extractU4(20, packet->payload);
  msg->entryCount = extractU4(24, packet->payload);
  msg->oldestYear = extractU2(28, packet->payload);
  msg->oldestMonth = extractU1(30, packet->payload);
  msg->oldestDay = extractU1(31, packet->payload);
  msg->oldestHour = extractU1(32, packet->payload);
  msg->oldestMinute = extractU1(33, packet->payload);
  msg->oldestSecond = extractU1(34, packet->payload);
  // reserved4 U1
  msg->newestYear = extractU2(36, packet->payload);
  msg->newestMonth = extractU1(38, packet->payload);
  msg->newestDay = extractU1(39, packet->payload);
  msg->newestHour = extractU1(40, packet->payload);
  msg->newestMinute = extractU1(41, packet->payload);
  msg->newestSecond = extractU1(42, packet->payload);
  // reserved5 U1
  msg->status = extractX1(44, packet->payload);
  // reserved6 U1[3]

  return msg;
}

LogRetrievePosition* UBXParser::parseLogRetrievePosition(UBXPacket* packet) {
  LogRetrievePosition *msg = new LogRetrievePosition(packet);
  msg->isValid &= packet->payloadLength == 40;

  if (!msg->isValid) {
    return msg;
  }

  msg->entryIndex = extractU4(0, packet->payload);
  msg->lon = ((double) extractI4(4, packet->payload)) * 1e-7;
  msg->lat = ((double) extractI4(8, packet->payload)) * 1e-7;
  msg->hMSL = ((double) extractI4(12, packet->payload)) * 1e-7;
  msg->hAcc = extractU4(16, packet->payload);
  msg->gSpeed = extractU4(20, packet->payload);
  msg->heading = extractU4(24, packet->payload);
  msg->version = extractU1(28, packet->payload);
  msg->fixType = (GNSSFixType) extractU1(29, packet->payload);
  msg->year = extractU2(30, packet->payload);
  msg->month = extractU1(32, packet->payload);
  msg->day = extractU1(33, packet->payload);
  msg->hour = extractU1(34, packet->payload);
  msg->minute = extractU1(35, packet->payload);
  msg->second = extractU1(36, packet->payload);
  // reserved1 U1
  msg->numSV = extractU1(38, packet->payload);
  // reserved2 U1

  return msg;
}

LogRetrieveString* UBXParser::parseLogRetrieveString(UBXPacket* packet) {
  LogRetrieveString *msg = new LogRetrieveString(packet);
  msg->isValid &= packet->payloadLength >= 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->entryIndex = extractU4(0, packet->payload);
  msg->version = extractU1(4, packet->payload);
  // reserved1 U1
  msg->year = extractU2(6, packet->payload);
  msg->month = extractU1(8, packet->payload);
  msg->day = extractU1(9, packet->payload);
  msg->hour = extractU1(10, packet->payload);
  msg->minute = extractU1(11, packet->payload);
  msg->second = extractU1(12, packet->payload);
  // reserved2 U1
  msg->byteCount = extractU2(14, packet->payload);

  msg->isValid &= packet->payloadLength == 16 + msg->byteCount;

  if (!msg->isValid) {
    return msg;
  }

  for (int i = 0; i < msg->byteCount; i++) {
    msg->bytes[i] = packet->payload[16 + i];
  }

  return msg;
}

MonitoringHardware* UBXParser::parseMonitoringHardware(UBXPacket* packet) {
  MonitoringHardware *msg = new MonitoringHardware(packet);
  msg->isValid &= packet->payloadLength
    == 28 + MonitoringHardware::NB_PINS + 15;

  if (!msg->isValid) {
    return msg;
  }

  msg->pinSel = extractX4(0, packet->payload);
  msg->pinBank = extractX4(4, packet->payload);
  msg->pinDir = extractX4(8, packet->payload);
  msg->pinVal = extractX4(12, packet->payload);
  msg->noisePerMS = extractU2(16, packet->payload);
  msg->agcCnt = extractU2(18, packet->payload);
  msg->aStatus = (AntennaSupervisorStatus) extractU1(20, packet->payload);
  msg->aPower = (AntennaPowerStatus) extractU1(21, packet->payload);
  msg->flags = extractX1(22, packet->payload);
  // reserved1 U1
  msg->usedMask = extractX4(24, packet->payload);

  int idx = 28;
  for (uint8_t i = 0; i < MonitoringHardware::NB_PINS; i++) {
    msg->VP[i] = extractU1(idx, packet->payload);
    idx++;
  }

  msg->jamInd = extractU1(idx, packet->payload);
  idx++;
  // reserved3 U2
  idx += 2;

  msg->pinIrq = extractX4(idx, packet->payload);
  idx += 4;
  msg->pullHigh = extractX4(idx, packet->payload);
  idx += 4;
  msg->pullLow = extractX4(idx, packet->payload);
  idx += 4;

  return msg;
}

MonitoringHardwareExtended* UBXParser::parseMonitoringHardwareExtended(
  UBXPacket* packet
) {
  MonitoringHardwareExtended *msg = new MonitoringHardwareExtended(packet);
  msg->isValid &= packet->payloadLength == 28;

  if (!msg->isValid) {
    return msg;
  }

  msg->ofsI = extractI1(0, packet->payload);
  msg->magI = extractU1(1, packet->payload);
  msg->ofsQ = extractI1(2, packet->payload);
  msg->magQ = extractU1(3, packet->payload);
  msg->cfgSource = extractU1(4, packet->payload);
  // reserved0 U1[3]
  msg->lowLevCfg = extractU4(8, packet->payload);
  // reserved1 U4[2]
  msg->postStatus = extractU4(20, packet->payload);
  // reserved2 U4

  return msg;
}

MonitoringIO* UBXParser::parseMonitoringIO(
  UBXPacket* packet,
  uint16_t startIdx
) {
  MonitoringIO *msg = new MonitoringIO(packet);
  msg->isValid &= packet->payloadLength >= startIdx + 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->rxBytes = extractU4(startIdx, packet->payload);
  msg->txBytes = extractU4(startIdx + 4, packet->payload);
  msg->parityErrs = extractU2(startIdx + 8, packet->payload);
  msg->framingErrs = extractU2(startIdx + 10, packet->payload);
  msg->overrunErrs = extractU2(startIdx + 12, packet->payload);
  msg->breakCond = extractU2(startIdx + 14, packet->payload);
  msg->rxBusy = extractU1(startIdx + 16, packet->payload);
  msg->txBusy = extractU1(startIdx + 17, packet->payload);
  // reserved1 U2

  if (packet->payloadLength > startIdx + 20) {
    msg->next = parseMonitoringIO(packet, startIdx + 20);
  }

  return msg;
}

MonitoringMsgParseProcess* UBXParser::parseMonitoringMsgParseProcess(
  UBXPacket* packet
) {
  MonitoringMsgParseProcess *msg = new MonitoringMsgParseProcess(packet);
  msg->isValid &= packet->payloadLength
    == 2 * GNSS_NB_PORTS
        * GNSS_NB_PROTOCOLS
      + 4 * GNSS_NB_PORTS;

  if (!msg->isValid) {
    return msg;
  }

  for (uint8_t p = 0; p < GNSS_NB_PORTS; p++) {
    for (uint8_t pr = 0; pr < GNSS_NB_PROTOCOLS; pr++) {
      msg->msgs[p][pr] = extractU2(
        2 * (
          GNSS_NB_PROTOCOLS * p + pr
        ),
        packet->payload
      );
    }

    msg->skipped[p] = extractU4(
      2 * GNSS_NB_PORTS
        * GNSS_NB_PROTOCOLS
      + 4 * p,
      packet->payload
    );
  }

  return msg;
}

MonitoringReceiver* UBXParser::parseMonitoringReceiver(UBXPacket* packet) {
  MonitoringReceiver *msg = new MonitoringReceiver(packet);
  msg->isValid &= packet->payloadLength == 1;

  if (!msg->isValid) {
    return msg;
  }

  msg->flags = extractX1(0, packet->payload);

  return msg;
}

MonitoringReceiverBuffer* UBXParser::parseMonitoringReceiverBuffer(
  UBXPacket* packet
) {
  MonitoringReceiverBuffer *msg = new MonitoringReceiverBuffer(packet);
  msg->isValid &= packet->payloadLength == 24;

  if (!msg->isValid) {
    return msg;
  }

  for (uint8_t p = 0; p < GNSS_NB_PORTS; p++) {
    msg->pending[p] = extractU2(
      2 * p,
      packet->payload
    );

    msg->usage[p] = extractU1(
      2 * GNSS_NB_PORTS + p,
      packet->payload
    );

    msg->usage[p] = extractU1(
      2 * GNSS_NB_PORTS + GNSS_NB_PORTS + p,
      packet->payload
    );
  }

  return msg;
}

MonitoringTransmitterBuffer* UBXParser::parseMonitoringTransmitterBuffer(
  UBXPacket* packet
) {
  MonitoringTransmitterBuffer *msg = new MonitoringTransmitterBuffer(packet);
  msg->isValid &= packet->payloadLength == 24;

  if (!msg->isValid) {
    return msg;
  }

  for (uint8_t p = 0; p < GNSS_NB_PORTS; p++) {
    msg->pending[p] = extractU2(
      2 * p,
      packet->payload
    );

    msg->usage[p] = extractU1(
      2 * GNSS_NB_PORTS + p,
      packet->payload
    );

    msg->usage[p] = extractU1(
      2 * GNSS_NB_PORTS + GNSS_NB_PORTS + p,
      packet->payload
    );
  }

  return msg;
}

MonitoringVersion* UBXParser::parseMonitoringVersion(UBXPacket* packet) {
  MonitoringVersion *msg = new MonitoringVersion(packet);
  int extensionsLength = packet->payloadLength - (
    MonitoringVersion::SOFTWARE_VERSION_SIZE
    + MonitoringVersion::HARDWARE_VERSION_SIZE
  );

  float nbExtensions = extensionsLength / MonitoringVersion::EXTENSION_SIZE;

  msg->isValid &= packet->payloadLength
      >= MonitoringVersion::SOFTWARE_VERSION_SIZE
        + MonitoringVersion::HARDWARE_VERSION_SIZE
    & nbExtensions == int(nbExtensions);

  if (!msg->isValid) {
    return msg;
  }

  int idx = 0;
  extractCH(
    idx,
    packet->payload,
    MonitoringVersion::SOFTWARE_VERSION_SIZE,
    msg->swVersion
  );
  idx += MonitoringVersion::SOFTWARE_VERSION_SIZE;

  extractCH(
    idx,
    packet->payload,
    MonitoringVersion::HARDWARE_VERSION_SIZE,
    msg->hwVersion
  );
  idx += MonitoringVersion::HARDWARE_VERSION_SIZE;

  for (int i = 0; i < nbExtensions; i++) {
    extractCH(
      idx,
      packet->payload,
      MonitoringVersion::EXTENSION_SIZE,
      msg->extension[i]
    );
    idx += MonitoringVersion::EXTENSION_SIZE;
  }

  return msg;
}

ReceiverManagerAlmanach* UBXParser::parseReceiverManagerAlmanach(
  UBXPacket* packet
) {
  ReceiverManagerAlmanach *msg = new ReceiverManagerAlmanach(packet);
  msg->isValid &= packet->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU4(0, packet->payload);
  msg->week = extractU4(4, packet->payload);

  msg->isValid &= packet->payloadLength == 8
    || packet->payloadLength == 8 + 4 * GPSSubframe::NB_WORDS;

  if (!msg->isValid || packet->payloadLength == 8) {
    return msg;
  }

  msg->subframe = new GPSSubframe();
  for (uint8_t i = 0; i < msg->subframe->nbWords; i++) {
    msg->subframe->words[i] = extractU4(8 + 4 * i, packet->payload);
  }

  return msg;
}

ReceiverManagerEphemeris* UBXParser::parseReceiverManagerEphemeris(
  UBXPacket* packet
) {
  ReceiverManagerEphemeris *msg = new ReceiverManagerEphemeris(packet);
  msg->isValid &= packet->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU4(0, packet->payload);
  msg->how = extractU4(4, packet->payload);

  msg->isValid &= packet->payloadLength == 8
    || packet->payloadLength == 8 + 3 * 4 * GPSSubframe::NB_WORDS;

  if (!msg->isValid || packet->payloadLength == 8) {
    return msg;
  }

  int idx = 8;
  msg->subframe1 = new GPSSubframe1();
  for (uint8_t i = 0; i < msg->subframe1->nbWords; i++) {
    msg->subframe1->words[i] = extractU4(idx, packet->payload);
    idx += 4;
  }

  msg->subframe2 = new GPSSubframe2();
  for (uint8_t i = 0; i < msg->subframe1->nbWords; i++) {
    msg->subframe1->words[i] = extractU4(idx, packet->payload);
    idx += 4;
  }

  msg->subframe3 = new GPSSubframe3();
  for (uint8_t i = 0; i < msg->subframe1->nbWords; i++) {
    msg->subframe1->words[i] = extractU4(idx, packet->payload);
    idx += 4;
  }

  return msg;
}

ReceiverManagerRaw* UBXParser::parseReceiverManagerRaw(UBXPacket* packet) {
  ReceiverManagerRaw *msg = new ReceiverManagerRaw(packet);
  msg->isValid &= packet->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->rcvTow = extractI4(0, packet->payload);
  msg->week = extractI2(4, packet->payload);
  msg->numSV = extractU1(6, packet->payload);
  // reserved1 U1

  msg->isValid &= msg->numSV <= GNSS_MAX_SVID
    && (packet->payloadLength == 8
      || packet->payloadLength == 8 + 24 * msg->numSV
    );

  if (!msg->isValid || packet->payloadLength == 8) {
    return msg;
  }

  int idx = 8;
  for (uint8_t i = 0; i < msg->numSV; i++) {
    msg->SVs[i] = new ReceiverManagerRawSpaceVehicule();
    msg->SVs[i]->cpMes = extractR8(idx, packet->payload);
    msg->SVs[i]->prMes = extractR8(idx + 8, packet->payload);
    msg->SVs[i]->doMes = extractR4(idx + 16, packet->payload);
    msg->SVs[i]->svid = extractU1(idx + 20, packet->payload);
    msg->SVs[i]->mesQI = extractU1(idx + 21, packet->payload);
    msg->SVs[i]->cno = extractU1(idx + 22, packet->payload);
    msg->SVs[i]->lli = extractU1(idx + 23, packet->payload);
    idx += 24;
  }

  return msg;
}

ReceiverManagerSubframe* UBXParser::parseReceiverManagerSubframe(
  UBXPacket* packet
) {
  ReceiverManagerSubframe *msg = new ReceiverManagerSubframe(packet);
  msg->isValid &= packet->payloadLength == 42;

  if (!msg->isValid) {
    return msg;
  }

  msg->chn = extractU1(0, packet->payload);
  msg->svid = extractU1(1, packet->payload);
  uint32_t word0 = extractX4(5, packet->payload);
  uint32_t word1 = extractX4(9, packet->payload);
  uint8_t subframeId = (word1 >> 2) & 0x7;

  switch (subframeId) {
    case 1:
      msg->subframe = new GPSSubframe1(true);
      break;
    case 2:
      msg->subframe = new GPSSubframe2(true);
      break;
    case 3:
      msg->subframe = new GPSSubframe3(true);
      break;
    default:
      msg->subframe = new GPSSubframe(true);
      break;
  }

  msg->subframe->words[0] = word0;
  msg->subframe->words[1] = word1;

  int idx = 10;
  for (uint8_t i = 2; i < msg->subframe->nbWords; i++) {
    msg->subframe->words[i] = extractX4(idx, packet->payload);
    idx += 4;
  }

  return msg;
}

ReceiverManagerSpaceVehiculeInfo* UBXParser::parseReceiverManagerSpaceVehiculeInfo(
  UBXPacket* packet
) {
  ReceiverManagerSpaceVehiculeInfo *msg = new ReceiverManagerSpaceVehiculeInfo(packet);
  msg->isValid &= packet->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, packet->payload);
  msg->week = extractI2(4, packet->payload);
  msg->numVisibleSV = extractU1(6, packet->payload);
  msg->numSV = extractU1(7, packet->payload);

  msg->isValid &= msg->numSV <= GNSS_MAX_SVID
    & packet->payloadLength == 8 + 6 * msg->numSV;

  if (!msg->isValid || msg->numSV == 0) {
    return msg;
  }

  int idx = 8;
  for (uint8_t i = 0; i < msg->numSV; i++) {
    msg->SVs[i] = new ReceiverManagerSpaceVehicule();
    msg->SVs[i]->svid = extractU1(idx, packet->payload);
    msg->SVs[i]->svFlag = extractX1(idx + 1, packet->payload);
    msg->SVs[i]->azim = extractI2(idx + 2, packet->payload);
    msg->SVs[i]->elev = extractI1(idx + 4, packet->payload);
    msg->SVs[i]->age = extractX1(idx + 5, packet->payload);
    idx += 6;
  }

  return msg;
}

TimingMark* UBXParser::parseTimingMark(UBXPacket* packet) {
  TimingMark *msg = new TimingMark(packet);
  msg->isValid &= packet->payloadLength == 28;

  if (!msg->isValid) {
    return msg;
  }

  msg->ch = extractU1(0, packet->payload);
  msg->flags = extractX1(1, packet->payload);
  msg->count = extractU2(2, packet->payload);
  msg->wnR = extractU2(4, packet->payload);
  msg->wnF = extractU2(6, packet->payload);
  msg->towMsR = extractU4(8, packet->payload);
  msg->towSubMsR = extractU4(12, packet->payload);
  msg->towMsF = extractU4(16, packet->payload);
  msg->towSubMsF = extractU4(20, packet->payload);
  msg->accEst = extractU4(24, packet->payload);

  return msg;
}

TimingPulse* UBXParser::parseTimingPulse(UBXPacket* packet) {
  TimingPulse *msg = new TimingPulse(packet);
  msg->isValid &= packet->payloadLength == 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->towMS = extractU4(0, packet->payload);
  msg->towSubMS = extractU4(4, packet->payload);
  msg->qErr = extractI4(8, packet->payload);
  msg->week = extractU2(12, packet->payload);
  msg->flags = extractX1(14, packet->payload);
  // reserved1 U1

  return msg;
}

TimingVerification* UBXParser::parseTimingVerification(UBXPacket* packet) {
  TimingVerification *msg = new TimingVerification(packet);
  msg->isValid &= packet->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractI4(0, packet->payload);
  msg->frac = extractI4(4, packet->payload);
  msg->deltaMs = extractI4(8, packet->payload);
  msg->deltaNs = extractI4(12, packet->payload);
  msg->wno = extractU2(16, packet->payload);
  msg->flags = extractX1(18, packet->payload);
  // reserved1 U1

  return msg;
}

uint8_t UBXParser::extractU1(uint8_t startIdx, byte* msgData)
{
  return msgData[startIdx] & 0xFF;
}

int8_t UBXParser::extractI1(uint8_t startIdx, byte* msgData)
{
  union // Use a union to convert from uint32_t to int32_t
  {
      uint8_t unsignedLong;
      int8_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU1(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

byte UBXParser::extractX1(uint8_t startIdx, byte* msgData)
{
  return msgData[startIdx] & 0xFF;
}

uint16_t UBXParser::extractU2(uint8_t startIdx, byte* msgData)
{
  uint16_t val = 0;

  val |= (uint16_t)msgData[startIdx] & 0xFF;
  val |= (uint16_t)msgData[startIdx + 1] << 8;

  return val;
}

int16_t UBXParser::extractI2(uint8_t startIdx, byte* msgData)
{
  union // Use a union to convert from uint32_t to int32_t
  {
      uint16_t unsignedLong;
      int16_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU2(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

uint16_t UBXParser::extractX2(uint8_t startIdx, byte* msgData)
{
  return extractU2(startIdx, msgData);
}

uint32_t UBXParser::extractU4(uint8_t startIdx, byte* msgData)
{
  uint32_t val = 0;

  val |= (uint32_t)msgData[startIdx] & 0xFF;
  val |= (uint32_t)msgData[startIdx + 1] << 8;
  val |= (uint32_t)msgData[startIdx + 2] << 16;
  val |= (uint32_t)msgData[startIdx + 3] << 24;

  return val;
}

//Just so there is no ambiguity about whether a uint32_t will cast to a int32_t correctly...
int32_t UBXParser::extractI4(uint8_t startIdx, byte* msgData)
{
  union // Use a union to convert from uint32_t to int32_t
  {
      uint32_t unsignedLong;
      int32_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU4(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

uint32_t UBXParser::extractX4(uint8_t startIdx, byte* msgData)
{
  return extractU4(startIdx, msgData);
}

uint32_t UBXParser::extractR4(uint8_t startIdx, byte* msgData)
{
  return extractU4(startIdx, msgData);
}

uint64_t UBXParser::extractU8(uint8_t startIdx, byte* msgData)
{
  uint64_t val = 0;

  val |= (uint64_t)msgData[startIdx] & 0xFF;
  val |= (uint64_t)msgData[startIdx + 1] << 8;
  val |= (uint64_t)msgData[startIdx + 2] << 16;
  val |= (uint64_t)msgData[startIdx + 3] << 24;
  val |= (uint64_t)msgData[startIdx + 4] << 32;
  val |= (uint64_t)msgData[startIdx + 5] << 40;
  val |= (uint64_t)msgData[startIdx + 6] << 48;
  val |= (uint64_t)msgData[startIdx + 7] << 56;

  return val;
}

int64_t UBXParser::extractI8(uint8_t startIdx, byte* msgData)
{
  union // Use a union to convert from uint32_t to int32_t
  {
      uint64_t unsignedLong;
      int64_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU8(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

uint64_t UBXParser::extractR8(uint8_t startIdx, byte* msgData)
{
  return extractU8(startIdx, msgData);
}

char UBXParser::extractCH(uint8_t startIdx, byte* msgData)
{
  return char(msgData[startIdx]);
}

void UBXParser::extractCH(
  uint8_t startIdx,
  byte* msgData,
  int length,
  char* out
) {
  for (int i = 0; i < length; i++) {
    out[i] = extractCH(startIdx + i, msgData);
  }
}
