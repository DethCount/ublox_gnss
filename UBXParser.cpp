#include "GNSS.h"

UBXMessage* UBXParser::parse(UBXMessage* msg)
{
  bool successfull_parsing = false;

  switch (highByte(msg->msgId))
  {
    case MessageClass::ACK:
      return parseACK(msg);
    case MessageClass::Aiding:
      return parseAiding(msg);
    case MessageClass::Navigation:
      return parseNavigation(msg);
    case MessageClass::Configuration:
      return parseConfiguration(msg);
    default:
      break;
  }

  #ifdef GNSS_DEBUG
    Serial.println("--- MSG ---");
    Serial.println(msg->msgId, HEX);

    for (int i = 0; i < msg->payloadLength; i++) {
      if (i > 0) {
        Serial.print(' ');
      }

      Serial.print(msg->payload[i] >> 4, HEX);
      Serial.print(msg->payload[i] & 0x0F, HEX);
    }

    Serial.println();
    Serial.println("!!!");
  #endif

  return msg;
}

UBXAck* UBXParser::parseACK(UBXMessage* msg)
{
  return parseACK(static_cast<UBXAck*>(msg));
}

UBXAck* UBXParser::parseACK(UBXAck* msg)
{
  msg->isValid &= msg->payloadLength == 2;

  if (msg->isValid) {
    msg->incomingMsgId = (MessageId) (
      extractU1(0, msg->payload) << 8
      | extractU1(1, msg->payload)
    );
  }

  Serial.println("ACK ok");
  Serial.println(msg->msgId, HEX);
  Serial.println(msg->incomingMsgId, HEX);

  return msg;
}

UBXMessage* UBXParser::parseAiding(UBXMessage* msg)
{
  switch (msg->msgId)
  {
    case MessageId::Aiding_Almanach:
      return parseAidingAlmanach(msg);
    case MessageId::Aiding_AlmanachPlus:
      return parseAidingAlmanachPlus(msg);
    case MessageId::Aiding_AOP:
      return parseAidingAOP(msg);
    case MessageId::Aiding_Ephemeris:
      return parseAidingEphemeris(msg);
    case MessageId::Aiding_HealthUTCIonosphere:
      return parseAidingHealthUTCIonosphere(msg);
    case MessageId::Aiding_Init:
      return parseAidingInit(msg);
    default:
      break;
  }

  return msg;
}

UBXMessage* UBXParser::parseNavigation(UBXMessage* msg)
{
  switch (msg->msgId)
  {
    case MessageId::Navigation_AOPStatus:
      return parseNavigationAOPStatus(msg);
    case MessageId::Navigation_Clock:
      return parseNavigationClock(msg);
    case MessageId::Navigation_DGPS:
      return parseNavigationDGPS(msg);
    case MessageId::Navigation_DOP:
      return parseNavigationDOP(msg);
    case MessageId::Navigation_PosECEF:
      return parseNavigationPosECEF(msg);
    case MessageId::Navigation_PosLLH:
      return parseNavigationPosLLH(msg);
    case MessageId::Navigation_PosVT:
      return parseNavigationPosVT(msg);
    case MessageId::Navigation_SBAS:
      return parseNavigationSBAS(msg);
    case MessageId::Navigation_SOL:
      return parseNavigationSOL(msg);
    case MessageId::Navigation_Status:
      return parseNavigationStatus(msg);
    case MessageId::Navigation_SpaceVehiculeInfo:
      return parseNavigationSpaceVehiculeInfo(msg);
    case MessageId::Navigation_TimeGPS:
      return parseNavigationTimeGPS(msg);
    case MessageId::Navigation_TimeUTC:
      return parseNavigationTimeUTC(msg);
    case MessageId::Navigation_VelECEF:
      return parseNavigationVelECEF(msg);
    case MessageId::Navigation_VelNED:
      return parseNavigationVelNED(msg);
    default:
      break;
  }

  return msg;
}

UBXMessage* UBXParser::parseConfiguration(UBXMessage* msg)
{
  switch (msg->msgId)
  {
    case MessageId::Configuration_Antenna:
      return parseConfigurationAntenna(msg);
    case MessageId::Configuration_Datum:
      return parseConfigurationDatum(msg);
    case MessageId::Configuration_Rate:
      return parseConfigurationRate(msg);
    default:
      break;
  }

  return msg;
}

AidingAlmanach* UBXParser::parseAidingAlmanach(UBXMessage* msg)
{
  return parseAidingAlmanach(static_cast<AidingAlmanach*>(msg));
}

AidingAlmanach* UBXParser::parseAidingAlmanach(AidingAlmanach* msg)
{
  msg->isValid &= msg->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU4(0, msg->payload);
  msg->week = extractU4(4, msg->payload);

  msg->isValid &= (msg->week == 0 && msg->payloadLength == 8)
    || (msg->week != 0 && msg->payloadLength == 40);

  if (!msg->isValid || msg->payloadLength <= 8) {
    return msg;
  }

  for (short i = 0; i < AidingAlmanach::MAX_NB_DWORD; i++) {
    msg->dword[i] = extractU4(8 + i * 4, msg->payload);
  }

  return msg;
}

AidingAlmanachPlus* UBXParser::parseAidingAlmanachPlus(UBXMessage* msg)
{
  return parseAidingAlmanachPlus(static_cast<AidingAlmanachPlus*>(msg));
}

AidingAlmanachPlus* UBXParser::parseAidingAlmanachPlus(AidingAlmanachPlus* msg)
{
  msg->isValid &= msg->payloadLength >= 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->idSize = extractU1(0, msg->payload);
  msg->type = extractU1(1, msg->payload);
  msg->ofs = extractU2(2, msg->payload);
  msg->size = extractU2(4, msg->payload);
  msg->fileId = extractU2(6, msg->payload);
  msg->dataSize = extractU2(8, msg->payload);
  msg->id1 = extractU1(10, msg->payload);
  msg->id2 = extractU1(11, msg->payload);
  msg->id3 = extractU4(12, msg->payload);

  msg->dataPayloadOffsetStart = 16;

  msg->isValid &= msg->payloadLength
    == msg->dataPayloadOffsetStart + msg->dataSize;

  return msg;
}

AidingAOP* UBXParser::parseAidingAOP(UBXMessage* msg)
{
  return parseAidingAOP(static_cast<AidingAOP*>(msg));
}

AidingAOP* UBXParser::parseAidingAOP(AidingAOP* msg)
{
  msg->isValid &= msg->payloadLength == 60
    || msg->payloadLength == 204;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU1(0, msg->payload);
  msg->dataSize = msg->payloadLength - 1;
  msg->dataPayloadOffsetStart = 1;

  msg->isValid &= msg->payloadLength
    == msg->dataPayloadOffsetStart + msg->dataSize;

  return msg;
}

AidingEphemeris* UBXParser::parseAidingEphemeris(UBXMessage* msg)
{
  return parseAidingEphemeris(static_cast<AidingEphemeris*>(msg));
}

AidingEphemeris* UBXParser::parseAidingEphemeris(AidingEphemeris* msg)
{
  msg->isValid &= msg->payloadLength == 8
    || msg->payloadLength == 104;

  if (!msg->isValid) {
    return msg;
  }

  msg->svid = extractU4(0, msg->payload);
  msg->how = extractU4(4, msg->payload);

  msg->isValid &= msg->how == 0
    || (msg->how != 0 && msg->payloadLength == 104);

  if (msg->how != 0) {
    short idx = 8;

    for (short i = 0; i < AidingEphemeris::WORDS_PER_SUBFRAME; i++) {
      msg->subframe1[i] = extractU4(idx, msg->payload);
      idx += 4;
    }

    for (short i = 0; i < AidingEphemeris::WORDS_PER_SUBFRAME; i++) {
      msg->subframe2[i] = extractU4(idx, msg->payload);
      idx += 4;
    }

    for (short i = 0; i < AidingEphemeris::WORDS_PER_SUBFRAME; i++) {
      msg->subframe3[i] = extractU4(idx, msg->payload);
      idx += 4;
    }
  }

  return msg;
}

AidingHealthUTCIonosphere* UBXParser::parseAidingHealthUTCIonosphere(
  UBXMessage* msg
) {
  return parseAidingHealthUTCIonosphere(
    static_cast<AidingHealthUTCIonosphere*>(msg)
  );
}

AidingHealthUTCIonosphere* UBXParser::parseAidingHealthUTCIonosphere(
  AidingHealthUTCIonosphere* msg
) {
  msg->isValid &= msg->payloadLength == 72;

  if (!msg->isValid) {
    return msg;
  }

  msg->health = extractU4(0, msg->payload);
  msg->utcA0 = extractR8(4, msg->payload);
  msg->utcA1 = extractR8(12, msg->payload);
  msg->utcTOW = extractI4(20, msg->payload);
  msg->utcWNT = extractI2(24, msg->payload);
  msg->utcLS = extractI2(26, msg->payload);
  msg->utcWNF = extractI2(28, msg->payload);
  msg->utcDN = extractI2(30, msg->payload);
  msg->utcLSF = extractI2(32, msg->payload);
  msg->utcSpare = extractI2(34, msg->payload);
  msg->klobA0 = extractR4(36, msg->payload);
  msg->klobA1 = extractR4(40, msg->payload);
  msg->klobA2 = extractR4(44, msg->payload);
  msg->klobA3 = extractR4(48, msg->payload);
  msg->klobB0 = extractR4(52, msg->payload);
  msg->klobB1 = extractR4(56, msg->payload);
  msg->klobB2 = extractR4(60, msg->payload);
  msg->klobB3 = extractR4(64, msg->payload);
  msg->flags = extractX4(68, msg->payload);

  return msg;
}

AidingInit* UBXParser::parseAidingInit(
  UBXMessage* msg
) {
  return parseAidingInit(
    static_cast<AidingInit*>(msg)
  );
}

AidingInit* UBXParser::parseAidingInit(
  AidingInit* msg
) {
  msg->isValid &= msg->payloadLength == 48;

  if (!msg->isValid) {
    return msg;
  }

  msg->ecefXOrLat = extractI4(0, msg->payload);
  msg->ecefYOrLon = extractI4(4, msg->payload);
  msg->ecefZOrAlt = extractI4(8, msg->payload);
  msg->posAcc = extractU4(12, msg->payload);
  msg->tmCfg = extractX2(16, msg->payload);
  msg->wnoOrDate = extractU2(18, msg->payload);
  msg->towOrTime = extractU4(20, msg->payload);
  msg->towNs = extractI4(24, msg->payload);
  msg->tAccMs = extractU4(28, msg->payload);
  msg->tAccNs = extractU4(32, msg->payload);
  msg->clkDOrFreq = extractI4(36, msg->payload);
  msg->clkDAccOrFreqAcc = extractU4(40, msg->payload);
  msg->flags = extractX4(44, msg->payload);

  return msg;
}

NavigationAOPStatus* UBXParser::parseNavigationAOPStatus(UBXMessage* msg)
{
  return parseNavigationAOPStatus(static_cast<NavigationAOPStatus*>(msg));
}

NavigationAOPStatus* UBXParser::parseNavigationAOPStatus(NavigationAOPStatus* msg)
{
  msg->isValid &= msg->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->aopCfg = extractU1(4, msg->payload);
  msg->status = (AOPStatus) extractU1(5, msg->payload);
  // reserved0 U1
  // reserved1 U1
  msg->availGPS = extractU4(8, msg->payload);
  // reserved2 U4
  // reserved3 U4

  return msg;
}

NavigationClock* UBXParser::parseNavigationClock(UBXMessage* msg)
{
  return parseNavigationClock(static_cast<NavigationClock*>(msg));
}

NavigationClock* UBXParser::parseNavigationClock(NavigationClock* msg)
{
  msg->isValid &= msg->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->clkB = extractI4(4, msg->payload);
  msg->clkD = extractI4(8, msg->payload);
  msg->tAcc = extractU4(12, msg->payload);
  msg->fAcc = extractU4(16, msg->payload);

  return msg;
}

NavigationDGPS* UBXParser::parseNavigationDGPS(UBXMessage* msg)
{
  return parseNavigationDGPS(static_cast<NavigationDGPS*>(msg));
}

NavigationDGPS* UBXParser::parseNavigationDGPS(NavigationDGPS* msg)
{
  msg->isValid &= msg->payloadLength >= 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->age = extractI4(4, msg->payload);
  msg->baseId = extractI2(8, msg->payload);
  msg->baseHealth = extractI2(10, msg->payload);
  msg->numCh = extractU1(12, msg->payload);
  msg->status = (DGPSStatus) extractU1(13, msg->payload);
  // reserved1 U2

  msg->isValid &= msg->payloadLength = 16 + 12 * msg->numCh;

  if (!msg->isValid) {
    return msg;
  }

  for (short i = 0; i < msg->numCh; i++) {
    NavigationDGPSChannel* chan = new NavigationDGPSChannel();
    int idx =  16 + i * 12;
    chan->svid = extractU1(idx, msg->payload);
    chan->flags = extractX1(idx + 1, msg->payload);
    chan->ageC = extractU2(idx + 2, msg->payload);
    chan->prc = extractU4(idx + 4, msg->payload);
    chan->prrc = extractU4(idx + 8, msg->payload);

    msg->channels[i] = chan;
  }

  return msg;
}

NavigationDOP* UBXParser::parseNavigationDOP(UBXMessage* msg)
{
  return parseNavigationDOP(static_cast<NavigationDOP*>(msg));
}

NavigationDOP* UBXParser::parseNavigationDOP(NavigationDOP* msg)
{
  msg->isValid &= msg->payloadLength == 18;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->gDOP = (double) extractU2(4, msg->payload) * 1e-2;
  msg->pDOP = (double) extractU2(6, msg->payload) * 1e-2;
  msg->tDOP = (double) extractU2(8, msg->payload) * 1e-2;
  msg->vDOP = (double) extractU2(10, msg->payload) * 1e-2;
  msg->hDOP = (double) extractU2(12, msg->payload) * 1e-2;
  msg->nDOP = (double) extractU2(14, msg->payload) * 1e-2;
  msg->eDOP = (double) extractU2(16, msg->payload) * 1e-2;

  return msg;
}

NavigationPosECEF* UBXParser::parseNavigationPosECEF(UBXMessage* msg)
{
  return parseNavigationPosECEF(static_cast<NavigationPosECEF*>(msg));
}

NavigationPosECEF* UBXParser::parseNavigationPosECEF(NavigationPosECEF* msg)
{
  msg->isValid &= msg->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->ecefX = extractI4(4, msg->payload);
  msg->ecefY = extractI4(8, msg->payload);
  msg->ecefZ = extractI4(12, msg->payload);
  msg->pAcc = extractU4(16, msg->payload);

  return msg;
}

NavigationPosLLH* UBXParser::parseNavigationPosLLH(UBXMessage* msg)
{
  return parseNavigationPosLLH(static_cast<NavigationPosLLH*>(msg));
}

NavigationPosLLH* UBXParser::parseNavigationPosLLH(NavigationPosLLH* msg)
{
  msg->isValid &= msg->payloadLength == 28;
  if (!msg->isValid) {
    return msg;
  }

  #ifdef GNSS_DEBUG
    for (int i = 0; i < msg->payloadLength; i++) {
      Serial.println(msg->payload[i], HEX);
    }
  #endif

  msg->iTOW = extractU4(0, msg->payload);
  msg->longitude = (double)extractI4(4, msg->payload) * 1e-7;
  msg->latitude = (double)extractI4(8, msg->payload) * 1e-7;
  msg->height = extractI4(12, msg->payload);
  msg->hMSL = extractI4(16, msg->payload);
  msg->hAcc = extractU4(20, msg->payload);
  msg->vAcc = extractU4(24, msg->payload);

  return msg;
}

NavigationPosVT* UBXParser::parseNavigationPosVT(UBXMessage* msg)
{
  return parseNavigationPosVT(static_cast<NavigationPosVT*>(msg));
}

NavigationPosVT* UBXParser::parseNavigationPosVT(NavigationPosVT* msg)
{
  msg->isValid &= msg->payloadLength == 84;
  if (!msg->isValid) {
    return msg;
  }

  #ifdef GNSS_DEBUG
    for (int i = 0; i < msg->payloadLength; i++) {
      Serial.println(msg->payload[i], HEX);
    }
  #endif

  msg->iTOW = extractU4(0, msg->payload);
  msg->year = extractU2(4, msg->payload);
  msg->month = extractU1(6, msg->payload);
  msg->day = extractU1(7, msg->payload);
  msg->hour = extractU1(8, msg->payload);
  msg->minute = extractU1(9, msg->payload);
  msg->second = extractU1(10, msg->payload);
  msg->valid = extractX1(11, msg->payload);
  msg->tAcc = extractU4(12, msg->payload);
  msg->nano = extractI4(16, msg->payload);
  msg->fixType = (GNSSFixType) extractU1(20, msg->payload);
  msg->flags = extractX1(21, msg->payload);
  // reserved1 U1
  msg->numSV = extractU1(23, msg->payload);
  msg->longitude = (double)extractI4(24, msg->payload) * 1e-7;
  msg->latitude = (double)extractI4(28, msg->payload) * 1e-7;
  msg->height = extractI4(32, msg->payload);
  msg->hMSL = extractI4(36, msg->payload);
  msg->hAcc = extractU4(40, msg->payload);
  msg->vAcc = extractU4(44, msg->payload);
  msg->velocityNorth = (double) extractI4(48, msg->payload);
  msg->velocityEast = (double) extractI4(52, msg->payload);
  msg->velocityDown = (double) extractI4(56, msg->payload);
  msg->groundSpeed = (double) extractI4(60, msg->payload);
  msg->heading = (double) extractI4(64, msg->payload) * 1e-5;
  msg->sAcc = extractU4(68, msg->payload);
  msg->headingAcc = (double) extractU4(72, msg->payload) * 1e-5;
  msg->pDOP = (double) extractU2(76, msg->payload) * 1e-2;
  // reserved2 X2
  // reserved3 U4

  return msg;
}

NavigationSBAS* UBXParser::parseNavigationSBAS(UBXMessage* msg)
{
  return parseNavigationSBAS(static_cast<NavigationSBAS*>(msg));
}

NavigationSBAS* UBXParser::parseNavigationSBAS(NavigationSBAS* msg)
{
  msg->isValid &= msg->payloadLength >= 12;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->geo = extractU1(4, msg->payload);
  msg->mode = (SBASMode) extractU1(5, msg->payload);
  msg->sys = (SBASSystem) extractI1(6, msg->payload);
  msg->service = extractX1(7, msg->payload);
  msg->cnt = extractU1(8, msg->payload);
  // reserved0 U1[3]

  msg->isValid &= msg->payloadLength == 12 + 12 * msg->cnt;

  if (!msg->isValid) {
    return msg;
  }

  for (short i = 0; i < msg->cnt; i++) {
    int idx = 12 + i * 12;
    NavigationSBASItem* item = new NavigationSBASItem();
    item->svid = extractU1(idx, msg->payload);
    item->flags = extractX1(idx + 1, msg->payload);
    item->udre = extractX1(idx + 2, msg->payload);
    item->svSys = (SBASSystem) extractI1(idx + 3, msg->payload);
    item->svService = extractX1(idx + 4, msg->payload);
    // reserved1 U1
    item->prc = extractI2(idx + 6, msg->payload);
    // reserved2 U2
    item->ic = extractI2(idx + 10, msg->payload);

    msg->items[i] = item;
  }

  return msg;
}

NavigationSOL* UBXParser::parseNavigationSOL(UBXMessage* msg)
{
  return parseNavigationSOL(static_cast<NavigationSOL*>(msg));
}

NavigationSOL* UBXParser::parseNavigationSOL(NavigationSOL* msg)
{
  msg->isValid &= msg->payloadLength == 52;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->fTOW = extractI4(4, msg->payload);
  msg->week = extractI2(8, msg->payload);
  msg->gpsFix = (GNSSFixType) extractU1(10, msg->payload);
  msg->flags = extractX1(11, msg->payload);
  msg->ecefX = extractI4(12, msg->payload);
  msg->ecefY = extractI4(16, msg->payload);
  msg->ecefZ = extractI4(20, msg->payload);
  msg->pAcc = extractU4(24, msg->payload);
  msg->ecefVX = extractI4(28, msg->payload);
  msg->ecefVY = extractI4(32, msg->payload);
  msg->ecefVZ = extractI4(36, msg->payload);
  msg->sAcc = extractU4(40, msg->payload);
  msg->pDOP = (double) extractU2(44, msg->payload) * 1e-2;
  // reserved1 U1
  msg->numSV = extractU1(47, msg->payload);
  // reserved2 U4

  return msg;
}

NavigationStatus* UBXParser::parseNavigationStatus(UBXMessage* msg)
{
  return parseNavigationStatus(static_cast<NavigationStatus*>(msg));
}

NavigationStatus* UBXParser::parseNavigationStatus(NavigationStatus* msg)
{
  msg->isValid &= msg->payloadLength == 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->gpsFix = (GNSSFixType) extractU1(4, msg->payload);
  msg->flags = extractX1(5, msg->payload);
  msg->fixStat = extractX1(6, msg->payload);
  msg->flags2 = extractX1(7, msg->payload);
  msg->ttff = extractU4(8, msg->payload);
  msg->msss = extractU4(12, msg->payload);

  return msg;
}

NavigationSpaceVehiculeInfo* UBXParser::parseNavigationSpaceVehiculeInfo(
  UBXMessage* msg
) {
  return parseNavigationSpaceVehiculeInfo(
    static_cast<NavigationSpaceVehiculeInfo*>(msg)
  );
}

NavigationSpaceVehiculeInfo* UBXParser::parseNavigationSpaceVehiculeInfo(
  NavigationSpaceVehiculeInfo* msg
) {
  msg->isValid &= msg->payloadLength >= 8;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->numCh = extractU1(4, msg->payload);
  msg->globalFlags = extractX1(5, msg->payload);
  // reserved2 U2

  msg->isValid &= msg->payloadLength == 8 + 12 * msg->numCh;

  if (!msg->isValid) {
    return msg;
  }

  for (short i = 0; i < msg->numCh; i++) {
    int idx = 8 + 12 * i;
    NavigationSpaceVehicule* sv = new NavigationSpaceVehicule();
    sv->chn = extractU1(idx, msg->payload);
    sv->svid = extractU1(idx + 1, msg->payload);
    sv->flags = extractX1(idx + 2, msg->payload);
    sv->quality = extractX1(idx + 3, msg->payload);
    sv->cno = extractU1(idx + 4, msg->payload);
    sv->elev = extractI1(idx + 5, msg->payload);
    sv->azim = extractI2(idx + 6, msg->payload);
    sv->prRes = extractI4(idx + 8, msg->payload);

    msg->spaceVehicules[i] = sv;
  }

  return msg;
}

NavigationTimeGPS* UBXParser::parseNavigationTimeGPS(UBXMessage* msg)
{
  return parseNavigationTimeGPS(static_cast<NavigationTimeGPS*>(msg));
}

NavigationTimeGPS* UBXParser::parseNavigationTimeGPS(NavigationTimeGPS* msg)
{
  msg->isValid &= msg->payloadLength == 16;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->fTOW = extractI4(4, msg->payload);
  msg->week = extractI2(8, msg->payload);
  msg->leapS = extractI1(10, msg->payload);
  msg->valid = extractX1(11, msg->payload);
  msg->tAcc = extractU4(12, msg->payload);

  msg->isValid &= msg->valid == 0x07;

  return msg;
}

NavigationTimeUTC* UBXParser::parseNavigationTimeUTC(UBXMessage* msg)
{
  return parseNavigationTimeUTC(static_cast<NavigationTimeUTC*>(msg));
}

NavigationTimeUTC* UBXParser::parseNavigationTimeUTC(NavigationTimeUTC* msg)
{
  msg->isValid &= msg->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  Serial.println("TimeUTC");
  for (int i = 0; i < msg->payloadLength; i++) {
    Serial.println(msg->payload[i], HEX);
  }
  Serial.println("end TimeUTC");

  msg->iTOW = extractU4(0, msg->payload);
  msg->tAcc = extractU4(4, msg->payload);
  msg->nano = extractI4(8, msg->payload);
  msg->year = extractU2(12, msg->payload);
  msg->month = extractU1(14, msg->payload);
  msg->day = extractU1(15, msg->payload);
  msg->hour = extractU1(16, msg->payload);
  msg->minute = extractU1(17, msg->payload);
  msg->second = extractU1(18, msg->payload);
  msg->flags = extractX1(19, msg->payload);
  msg->isValid &= msg->flags == 0x07;

  return msg;
}

NavigationVelECEF* UBXParser::parseNavigationVelECEF(UBXMessage* msg)
{
  return parseNavigationVelECEF(static_cast<NavigationVelECEF*>(msg));
}

NavigationVelECEF* UBXParser::parseNavigationVelECEF(NavigationVelECEF* msg)
{
  msg->isValid &= msg->payloadLength == 20;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->ecefVX = extractI4(4, msg->payload);
  msg->ecefVY = extractI4(8, msg->payload);
  msg->ecefVZ = extractI4(12, msg->payload);
  msg->sAcc = extractU4(16, msg->payload);

  return msg;
}

NavigationVelNED* UBXParser::parseNavigationVelNED(UBXMessage* msg)
{
  return parseNavigationVelNED(static_cast<NavigationVelNED*>(msg));
}

NavigationVelNED* UBXParser::parseNavigationVelNED(NavigationVelNED* msg)
{
  msg->isValid &= msg->payloadLength == 36;

  if (!msg->isValid) {
    return msg;
  }

  msg->iTOW = extractU4(0, msg->payload);
  msg->velocityNorth = extractI4(4, msg->payload);
  msg->velocityEast = extractI4(8, msg->payload);
  msg->velocityDown = extractI4(12, msg->payload);
  msg->speed = extractU4(16, msg->payload);
  msg->gSpeed = extractU4(20, msg->payload);
  msg->heading = (double) extractI4(24, msg->payload) * 1e-5;
  msg->sAcc = extractU4(28, msg->payload);
  msg->cAcc = (double) extractU4(32, msg->payload) * 1e-5;

  return msg;
}

ConfigurationAntenna* UBXParser::parseConfigurationAntenna(UBXMessage* msg)
{
  return parseConfigurationAntenna(static_cast<ConfigurationAntenna*>(msg));
}

ConfigurationAntenna* UBXParser::parseConfigurationAntenna(ConfigurationAntenna* msg)
{
  msg->isValid &= msg->payloadLength == 4;

  if (!msg->isValid) {
    return msg;
  }

  msg->flags = extractX2(0, msg->payload);
  msg->pins = extractX2(2, msg->payload);

  return msg;
}

ConfigurationDatum* UBXParser::parseConfigurationDatum(UBXMessage* msg)
{
  return parseConfigurationDatum(static_cast<ConfigurationDatum*>(msg));
}

ConfigurationDatum* UBXParser::parseConfigurationDatum(ConfigurationDatum* msg)
{
  msg->isValid &= msg->payloadLength == 52;

  if (!msg->isValid) {
    return msg;
  }

  msg->datumNum = extractU2(0, msg->payload);
  extractCH(2, msg->payload, ConfigurationDatum::NAME_SIZE, msg->datumName);
  msg->majA = extractR8(8, msg->payload);
  msg->flat = extractR8(16, msg->payload);
  msg->dX = extractR4(24, msg->payload);
  msg->dY = extractR4(28, msg->payload);
  msg->dZ = extractR4(32, msg->payload);
  msg->rotX = extractR4(36, msg->payload);
  msg->rotY = extractR4(40, msg->payload);
  msg->rotZ = extractR4(44, msg->payload);
  msg->scale = extractR4(48, msg->payload);

  return msg;
}

ConfigurationRate* UBXParser::parseConfigurationRate(UBXMessage* msg)
{
  return parseConfigurationRate(static_cast<ConfigurationRate*>(msg));
}

ConfigurationRate* UBXParser::parseConfigurationRate(ConfigurationRate* msg)
{
  msg->isValid &= msg->payloadLength == 6;

  if (msg->isValid) {
    msg->measRate = extractU2(0, msg->payload);
    msg->navRate = extractU2(2, msg->payload);
    msg->timeRef = extractU2(4, msg->payload);
  }

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

void UBXParser::extractCH(uint8_t startIdx, byte* msgData, int length, char* out)
{
  for (int i = 0; i < length; i++) {
    out[i] = extractCH(startIdx + i, msgData);
  }
}
