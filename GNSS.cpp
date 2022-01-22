#include "GNSS.h"

#ifdef __AVR__
GNSS::GNSS(SoftwareSerial *ss)
{
	swSerial = ss;
	stream = ss;
}
#endif

GNSS::GNSS(HardwareSerial *hs)
{
	hwSerial = hs;
	stream = hs;
}

void GNSS::begin(PortRate baudrate)
{
	Serial.println((uint32_t) baudrate);
	portRate = baudrate;

	if (hwSerial) {
		hwSerial->begin((uint32_t) portRate);
	}

	#ifdef __AVR__
		if (swSerial) {
			swSerial->begin((uint32_t) portRate);
		}
	#endif

	sendConfiguration();
}

UBXRequestStatus GNSS::enableMessage(
	uint16_t msgId,
	bool changePort,
  byte port1,
  byte port2,
  byte port3,
  byte port4,
  byte port5,
  byte port6,
	unsigned short numTries,
	unsigned int timeout
) {
	UBXMessage* enableMsg = new UBXMessage();
	enableMsg->msgId = MessageId::Configuration_Messaging;
	enableMsg->payload[0] = highByte(msgId);
	enableMsg->payload[1] = lowByte(msgId);
	enableMsg->payload[2] = port1;
	enableMsg->payloadLength = 3;

	if (changePort) {
		enableMsg->payload[3] = port2;
		enableMsg->payload[4] = port3;
		enableMsg->payload[5] = port4;
		enableMsg->payload[6] = port5;
		enableMsg->payload[7] = port6;
		enableMsg->payloadLength += 5;
	}

	calcChecksum(enableMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Enabling Message ");
		Serial.println(msgId, HEX);
	#endif

	return trySendUBXWithACK(enableMsg, numTries, timeout);
}

UBXRequestStatus GNSS::updatePortRate(
	unsigned short numTries,
	unsigned int timeout
) {
	UBXMessage* setPortRate = new UBXMessage();
	setPortRate->msgId = MessageId::Configuration_Port;

	setPortRate->payload[0] = 0x01; // port ID

	setPortRate->payload[1] = 0x00; // reserved

	// TX Ready PIN
	setPortRate->payload[2] = 0x00;
	setPortRate->payload[3] = 0x00;

	// mode
	setPortRate->payload[4] = 0xD0;
	setPortRate->payload[5] = 0x08;
	setPortRate->payload[6] = 0x00;
	setPortRate->payload[7] = 0x00;

	setPortRate->payload[8] = ((uint32_t) portRate) & 0xFF;
	setPortRate->payload[9] = ((uint32_t) portRate) >> 8;
	setPortRate->payload[10] = ((uint32_t) portRate) >> 16;
	setPortRate->payload[11] = ((uint32_t) portRate) >> 24;

	// inProtoMask
	setPortRate->payload[12] = 0x07;
	setPortRate->payload[13] = 0x00;

	// outProtoMask
	setPortRate->payload[14] = 0x03;
	setPortRate->payload[15] = 0x00;

	// flags
	setPortRate->payload[16] = 0x00;
	setPortRate->payload[17] = 0x00;

	// reserved
	setPortRate->payload[18] = 0x00;
	setPortRate->payload[19] = 0x00;

	setPortRate->payloadLength = 20;

	calcChecksum(setPortRate);

	#ifdef GNSS_DEBUG
		Serial.print("Setting Port Baud Rate... ");
	#endif

	return trySendUBXWithACK(setPortRate, numTries, timeout);
}

AidingAlmanach* GNSS::getAidingAlmanach(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Almanach;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach... ");
	#endif

	return static_cast<AidingAlmanach*>(trySendUBX(
		getMsg,
		MessageId::Aiding_Almanach,
		numTries,
		timeout
	));
}

AidingAlmanach* GNSS::getAidingAlmanach(
	uint8_t svid,
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Almanach;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = svid;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach... ");
	#endif

	return static_cast<AidingAlmanach*>(trySendUBX(
		getMsg,
		MessageId::Aiding_Almanach,
		numTries,
		timeout
	));
}

AidingAlmanachPlus* GNSS::getAidingAlmanachPlus(
  uint8_t idSize,
  uint8_t type,
  uint16_t ofs,
  uint16_t size,
  uint16_t fileId,
  uint16_t dataSize,
  uint8_t id1,
  uint8_t id2,
  uint16_t id3,
  unsigned short numTries = UBX_NUM_TRIES,
  unsigned int timeout = UBX_TIMEOUT
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_AlmanachPlus;
	getMsg->payloadLength = 16;
	getMsg->payload[0] = idSize;
	getMsg->payload[1] = type;
	getMsg->payload[2] = highByte(ofs);
	getMsg->payload[3] = lowByte(ofs);
	getMsg->payload[4] = highByte(size);
	getMsg->payload[5] = lowByte(size);
	getMsg->payload[6] = highByte(fileId);
	getMsg->payload[7] = lowByte(fileId);
	getMsg->payload[8] = highByte(dataSize);
	getMsg->payload[9] = lowByte(dataSize);
	getMsg->payload[10] = id1;
	getMsg->payload[11] = id2;
	getMsg->payload[12] = (id3 >> 24) & 0xFF;
	getMsg->payload[13] = (id3 >> 16) & 0xFF;
	getMsg->payload[14] = (id3 >> 8) & 0xFF;
	getMsg->payload[15] = id3 & 0xFF;

	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach plus... ");
	#endif

	return static_cast<AidingAlmanachPlus*>(trySendUBX(
		getMsg,
		MessageId::Aiding_AlmanachPlus,
		numTries,
		timeout
	));
}

AidingAOP* GNSS::getAidingAOP(
  unsigned short numTries = UBX_NUM_TRIES,
  unsigned int timeout = UBX_TIMEOUT
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_AOP;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding AOP... ");
	#endif

	return static_cast<AidingAOP*>(trySendUBX(
		getMsg,
		MessageId::Aiding_AOP,
		numTries,
		timeout
	));
}

AidingAOP* GNSS::getAidingAOP(
  uint8_t svid,
  unsigned short numTries = UBX_NUM_TRIES,
  unsigned int timeout = UBX_TIMEOUT
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_AOP;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = svid;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding AOP for given svid... ");
	#endif

	return static_cast<AidingAOP*>(trySendUBX(
		getMsg,
		MessageId::Aiding_AOP,
		numTries,
		timeout
	));
}

void GNSS::getAidingData(
  unsigned short numTries = UBX_NUM_TRIES,
  unsigned int timeout = UBX_TIMEOUT
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Data;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print(
			"Requesting aiding data... Expecting AID-INI, AID-HUI, AID-EPH and AID-ALM messages."
		);
	#endif
}

AidingEphemeris* GNSS::getAidingEphemeris(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Ephemeris;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding ephemeris... ");
	#endif

	return static_cast<AidingEphemeris*>(trySendUBX(
		getMsg,
		MessageId::Aiding_Ephemeris,
		numTries,
		timeout
	));
}

AidingEphemeris* GNSS::getAidingEphemeris(
	uint8_t svid,
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Ephemeris;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = svid;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding ephemeris for given svid... ");
	#endif

	return static_cast<AidingEphemeris*>(trySendUBX(
		getMsg,
		MessageId::Aiding_Ephemeris,
		numTries,
		timeout
	));
}

AidingHealthUTCIonosphere* GNSS::getAidingHealthUTCIonosphere(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_HealthUTCIonosphere;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding health, UTC and ionosphere... ");
	#endif

	return static_cast<AidingHealthUTCIonosphere*>(trySendUBX(
		getMsg,
		MessageId::Aiding_HealthUTCIonosphere,
		numTries,
		timeout
	));
}

AidingInit* GNSS::getAidingInit(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Init;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding initial data... ");
	#endif

	return static_cast<AidingInit*>(trySendUBX(
		getMsg,
		MessageId::Aiding_Init,
		numTries,
		timeout
	));
}

NavigationAOPStatus* GNSS::getNavigationAOPStatus(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_AOPStatus;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation AOP status... ");
	#endif

	return static_cast<NavigationAOPStatus*>(trySendUBX(
		getMsg,
		MessageId::Navigation_AOPStatus,
		numTries,
		timeout
	));
}

NavigationClock* GNSS::getNavigationClock(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_Clock;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation clock... ");
	#endif

	return static_cast<NavigationClock*>(trySendUBX(
		getMsg,
		MessageId::Navigation_Clock,
		numTries,
		timeout
	));
}

NavigationDGPS* GNSS::getNavigationDGPS(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_DGPS;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation DGPS... ");
	#endif

	return static_cast<NavigationDGPS*>(trySendUBX(
		getMsg,
		MessageId::Navigation_DGPS,
		numTries,
		timeout
	));
}

NavigationDOP* GNSS::getNavigationDOP(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_DOP;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation DOP... ");
	#endif

	return static_cast<NavigationDOP*>(trySendUBX(
		getMsg,
		MessageId::Navigation_DOP,
		numTries,
		timeout
	));
}

NavigationPosECEF* GNSS::getNavigationPosECEF(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_PosECEF;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation ECEF position... ");
	#endif

	return static_cast<NavigationPosECEF*>(trySendUBX(
		getMsg,
		MessageId::Navigation_PosECEF,
		numTries,
		timeout
	));
}

NavigationPosLLH* GNSS::getNavigationPosLLH(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_PosLLH;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation LLH position... ");
	#endif

	return static_cast<NavigationPosLLH*>(trySendUBX(
		getMsg,
		MessageId::Navigation_PosLLH,
		numTries,
		timeout
	));
}

NavigationPosVT* GNSS::getNavigationPosVT(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_PosVT;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation position velocity and time... ");
	#endif

	return static_cast<NavigationPosVT*>(trySendUBX(
		getMsg,
		MessageId::Navigation_PosVT,
		numTries,
		timeout
	));
}

NavigationSBAS* GNSS::getNavigationSBAS(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_SBAS;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation SBAS... ");
	#endif

	return static_cast<NavigationSBAS*>(trySendUBX(
		getMsg,
		MessageId::Navigation_SBAS,
		numTries,
		timeout
	));
}

NavigationSOL* GNSS::getNavigationSOL(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_SOL;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation SOL... ");
	#endif

	return static_cast<NavigationSOL*>(trySendUBX(
		getMsg,
		MessageId::Navigation_SOL,
		numTries,
		timeout
	));
}

NavigationStatus* GNSS::getNavigationStatus(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_Status;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation status... ");
	#endif

	return static_cast<NavigationStatus*>(trySendUBX(
		getMsg,
		MessageId::Navigation_Status,
		numTries,
		timeout
	));
}

NavigationSpaceVehiculeInfo* GNSS::getNavigationSpaceVehiculeInfo(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_SpaceVehiculeInfo;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation space vehicule information... ");
	#endif

	return static_cast<NavigationSpaceVehiculeInfo*>(trySendUBX(
		getMsg,
		MessageId::Navigation_SpaceVehiculeInfo,
		numTries,
		timeout
	));
}

NavigationTimeGPS* GNSS::getNavigationTimeGPS(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_TimeGPS;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation GPS time... ");
	#endif

	return static_cast<NavigationTimeGPS*>(trySendUBX(
		getMsg,
		MessageId::Navigation_TimeGPS,
		numTries,
		timeout
	));
}

NavigationTimeUTC* GNSS::getNavigationTimeUTC(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_TimeUTC;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation UTC time... ");
	#endif

	return static_cast<NavigationTimeUTC*>(trySendUBX(
		getMsg,
		MessageId::Navigation_TimeUTC,
		numTries,
		timeout
	));
}

NavigationVelECEF* GNSS::getNavigationVelECEF(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_VelECEF;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation ECEF velocity... ");
	#endif

	return static_cast<NavigationVelECEF*>(trySendUBX(
		getMsg,
		MessageId::Navigation_VelECEF,
		numTries,
		timeout
	));
}

NavigationVelNED* GNSS::getNavigationVelNED(
  unsigned short numTries,
  unsigned int timeout
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_VelNED;
	getMsg->payloadLength = 0;
	calcChecksum(getMsg);

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation NED velocity... ");
	#endif

	return static_cast<NavigationVelNED*>(trySendUBX(
		getMsg,
		MessageId::Navigation_VelNED,
		numTries,
		timeout
	));
}

ConfigurationRate* GNSS::getConfigurationRate(
	unsigned short numTries,
	unsigned int timeout
) {
	UBXMessage* getDataRate = new UBXMessage();
	getDataRate->msgId = MessageId::Configuration_Rate;
	getDataRate->payloadLength = 0;
	calcChecksum(getDataRate);

	#ifdef GNSS_DEBUG
		Serial.print("Getting Data Rate... ");
	#endif

	return static_cast<ConfigurationRate*>(trySendUBX(
		getDataRate,
		MessageId::Configuration_Rate,
		numTries,
		timeout
	));
}

UBXRequestStatus GNSS::updateDataRate(
	unsigned short numTries,
	unsigned int timeout
) {
	UBXMessage* setDataRate = new UBXMessage();

	setDataRate->msgId = MessageId::Configuration_Rate;

	// measurement rate (in ms)
	setDataRate->payload[0] = highByte((uint16_t) dataRate);
	setDataRate->payload[1] = lowByte((uint16_t) dataRate);

	// navigation rate, cannot be changed
	setDataRate->payload[2] = 0x01;
	setDataRate->payload[3] = 0x00;

	// reference time (0: UTC, 1: GPS)
	setDataRate->payload[4] = 0x01;
	setDataRate->payload[5] = 0x00;
	setDataRate->payloadLength = 6;

	calcChecksum(setDataRate);

	#ifdef GNSS_DEBUG
		Serial.print("Setting Data Rate... ");
	#endif

	return trySendUBXWithACK(setDataRate, numTries, timeout);
}

void GNSS::sendConfiguration(void)
{
	#ifdef GNSS_DEBUG
		Serial.println("Configuring u-Blox GNSS initial state...");
	#endif

	//Generate the configuration string for Navigation Mode
	UBXMessage* setNavMsg = new UBXMessage();
	setNavMsg->msgId = MessageId::Configuration_Navigation;

	// parameters mask
	setNavMsg->payload[0] = 0xFF;
	setNavMsg->payload[1] = 0xFF;

	setNavMsg->payload[2] = (byte) navigationMode;

	// fixMode
	setNavMsg->payload[3] = 0x03;

	// fixedAlt
	setNavMsg->payload[4] = 0x00;
	setNavMsg->payload[5] = 0x00;
	setNavMsg->payload[6] = 0x00;
	setNavMsg->payload[7] = 0x00;

	// fixedAltVar
	setNavMsg->payload[8] = 0x10;
	setNavMsg->payload[9] = 0x27;
	setNavMsg->payload[10] = 0x00;
	setNavMsg->payload[11] = 0x00;

	// minElev
	setNavMsg->payload[12] = 0x05;

	// drLimit
	setNavMsg->payload[13] = 0x00;

	// pDop
	setNavMsg->payload[14] = 0xFA;
	setNavMsg->payload[15] = 0x00;

	// tDop
	setNavMsg->payload[16] = 0xFA;
	setNavMsg->payload[17] = 0x00;

	// pAcc
	setNavMsg->payload[18] = 0x64;
	setNavMsg->payload[19] = 0x00;

	// tAcc
	setNavMsg->payload[20] = 0x2C;
	setNavMsg->payload[21] = 0x01;

	// staticHoldThresh
	setNavMsg->payload[22] = 0x00;

	// dgpsTimeOut
	setNavMsg->payload[23] = 0x00;

	// cnoThreshNumSVs
	setNavMsg->payload[24] = 0x00;

	// cnoThresh
	setNavMsg->payload[25] = 0x00;

	// reserved2
	setNavMsg->payload[26] = 0x00;
	setNavMsg->payload[27] = 0x00;

	// reserved3
	setNavMsg->payload[28] = 0x00;
	setNavMsg->payload[29] = 0x00;
	setNavMsg->payload[30] = 0x00;
	setNavMsg->payload[31] = 0x00;

	// reserved4
	setNavMsg->payload[32] = 0x00;
	setNavMsg->payload[33] = 0x00;
	setNavMsg->payload[34] = 0x00;
	setNavMsg->payload[35] = 0x00;
	setNavMsg->payloadLength = 36;

	calcChecksum(setNavMsg);

	#ifdef GNSS_DEBUG
		Serial.println("Setting Navigation mode...");
	#endif

	UBXRequestStatus result = trySendUBXWithACK(setNavMsg);

	#ifdef GNSS_DEBUG
		if (result != UBXRequestStatus::Success) {
			Serial.println("Navigation mode configuration failed.");
			return;
		}
	#endif

	// if (dataRate != DataRate::F1Hz) {
		// updateDataRate();
	// }

	// if (portRate != PortRate::Bauds_9600) {
		updatePortRate();
	// }

	Serial.println("Configured");
}

void GNSS::calcChecksum(UBXMessage* msg)
{
	msg->checksum[0] = highByte(msg->msgId);
	msg->checksum[1] = msg->checksum[0];
	msg->checksum[0] += lowByte(msg->msgId);
	msg->checksum[1] += msg->checksum[0];

	msg->checksum[0] += lowByte(msg->payloadLength);
	msg->checksum[1] += msg->checksum[0];
	msg->checksum[0] += highByte(msg->payloadLength);
	msg->checksum[1] += msg->checksum[0];

	for (int i = 0; i < msg->payloadLength; i++) {
		msg->checksum[0] += msg->payload[i];
		msg->checksum[1] += msg->checksum[0];
	}
}

UBXRequestStatus GNSS::trySendUBXWithACK(
	UBXMessage* msg,
	unsigned short numTries,
	unsigned int timeout
) {
	short tries = 0;
	UBXRequestStatus result;

	while (tries < numTries && result != UBXRequestStatus::Success) {
		#ifdef GNSS_DEBUG
			Serial.print("try ");
			Serial.println(tries + 1);
		#endif

		sendUBX(msg);
		result = nextUBXACK(msg, timeout);
		tries++;
	}

	#ifdef GNSS_DEBUG
		if (tries == numTries && result != UBXRequestStatus::Success) {
			Serial.println("Failed UBX message with ACK.");
		}
	#endif

	return result;
}

UBXMessage* GNSS::trySendUBX(
	UBXMessage* msg,
	MessageId expectedResponseMsgId,
	unsigned short numTries,
	unsigned int timeout
) {
	UBXMessage* result = new UBXMessage();
	result->isValid = false;
	short tries = 0;

	while (tries < numTries && !result->isValid) {
		#ifdef GNSS_DEBUG
			Serial.print("try ");
			Serial.println(tries + 1);
		#endif

		sendUBX(msg);
		result = nextUBXPacket(timeout, expectedResponseMsgId);
		if (result->isValid) {
			return result;
		}
		tries++;
	}

	#ifdef GNSS_DEBUG
		if (tries == numTries && !result->isValid) {
			Serial.print("Failed UBX message. Expecting: ");
			Serial.println(expectedResponseMsgId);
		}
	#endif

	return result;
}

void GNSS::sendUBX(UBXMessage* msg)
{
	stream->write(UBX_SYNC_1);
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println("sendUBX");
		Serial.println(UBX_SYNC_1, HEX);
	#endif

	stream->write(UBX_SYNC_2);
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(UBX_SYNC_2, HEX);
	#endif

	stream->write(highByte(msg->msgId));
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(highByte(msg->msgId), HEX);
	#endif

	stream->write(lowByte(msg->msgId));
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(lowByte(msg->msgId), HEX);
	#endif

	stream->write(lowByte(msg->payloadLength));
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(lowByte(msg->payloadLength), HEX);
	#endif

	stream->write(highByte(msg->payloadLength));
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(highByte(msg->payloadLength), HEX);
	#endif

	for (int i = 0; i < msg->payloadLength; i++)
	{
		stream->write(msg->payload[i]);
		stream->flush();
		#ifdef GNSS_DEBUG
			Serial.println(msg->payload[i], HEX);
		#endif
	}

	if (msg->checksum[0] == 0x00 && msg->checksum[1] == 0x00) {
		calcChecksum(msg);
	}

	stream->write(msg->checksum[0]);
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(msg->checksum[0], HEX);
	#endif

	stream->write(msg->checksum[1]);
	stream->flush();
	#ifdef GNSS_DEBUG
		Serial.println(msg->checksum[1], HEX);
		Serial.println("end sendUBX");
	#endif

	stream->println();
	stream->flush();
}

void GNSS::getConfiguration(void)
{
	UBXMessage* getCfg = new UBXMessage();
	getCfg->msgId = MessageId::Configuration_Port;
	sendUBX(getCfg);
}

UBXMessage* GNSS::nextUBXPacket(unsigned int timeout, MessageId expectedId)
{
	UBXMessage *packet = new UBXMessage();
	packet->isValid = false;
	uint8_t incoming_char;
	int byteIdx = 0;
	bool hasValidChecksum = true;
	uint16_t msgLength = 0;
	byte checksum[2] = { 0x00, 0x00 };
	unsigned long start = millis();
	MessageClass classId;

	while (true) {
		if (millis() - start > timeout) {
			Serial.println("Timeout");
			Serial.println(timeout);
			packet->isValid = false;
			return packet;
		}

		if (stream->available()) {
			incoming_char = stream->read();
			Serial.println(incoming_char, HEX);

			if (!packet->isValid) {
				byteIdx = 0;

				if (incoming_char == UBX_SYNC_1) {
					Serial.println("Incoming packet");
					packet->isValid = true;
					hasValidChecksum = true;
					checksum[0] = 0x00;
					checksum[1] = 0x00;
					classId = NULL;
					memset(packet->payload, 0x00, UBX_MSG_PAYLOAD_SIZE);
					byteIdx++;
				}

				continue;
			}

			if (byteIdx == 1) {
				Serial.println("byte 1");
				packet->isValid = incoming_char == UBX_SYNC_2;
				byteIdx++;
			} else if (byteIdx == 2) {
				Serial.println("byte 2");
				classId = (MessageClass) incoming_char;
				checksum[0] = incoming_char;
				checksum[1] = checksum[0];
				byteIdx++;
			} else if (byteIdx == 3) {
				Serial.println("byte 3");
				packet->msgId = (MessageId)(classId << 8 | incoming_char);
				packet->isValid = expectedId == MessageId::None
					|| packet->msgId == expectedId;
				if (packet->isValid) {
					checksum[0] += incoming_char;
					checksum[1] += checksum[0];
					byteIdx++;
				}
			} else if (byteIdx == 4) {
				Serial.println("byte 4");
				packet->payloadLength = incoming_char;
				checksum[0] += incoming_char;
				checksum[1] += checksum[0];
				byteIdx++;
			} else if (byteIdx == 5) {
				Serial.println("byte 5");
				packet->payloadLength += incoming_char << 8;
				checksum[0] += incoming_char;
				checksum[1] += checksum[0];

				Serial.print("payloadLength: ");
				Serial.println(packet->payloadLength);
				packet->isValid &= packet->payloadLength <= UBX_MSG_PAYLOAD_SIZE;
				byteIdx++;
			} else if (byteIdx >= 6 && byteIdx < 6 + packet->payloadLength) {
				Serial.println("byte 6");
				if (byteIdx < UBX_MSG_PAYLOAD_SIZE) {
					packet->payload[byteIdx - 6] = incoming_char;
					checksum[0] += incoming_char;
					checksum[1] += checksum[0];
					byteIdx++;
				} else {
					Serial.println("UBX packet buffer too short");
					packet->isValid = false;
				}
			} else if (byteIdx == 6 + packet->payloadLength) {
				Serial.println("byte 7");
				packet->checksum[0] = incoming_char;
				byteIdx++;
			} else if (byteIdx == 6 + packet->payloadLength + 1) {
				Serial.println("byte 8");
				packet->checksum[1] = incoming_char;
				hasValidChecksum = packet->msgId == MessageId::Navigation_PosVT
					|| (checksum[0] == packet->checksum[0]
						&& checksum[1] == packet->checksum[1]
					);
				packet->isValid &= hasValidChecksum;

				#ifdef GNSS_DEBUG
					Serial.print("RECV: ");
					Serial.print(packet->checksum[0], HEX);
					Serial.println(packet->checksum[1], HEX);

					Serial.print("CALC: ");
					Serial.print(checksum[0], HEX);
					Serial.println(checksum[1], HEX);
				#endif

				if (packet->isValid) {
					#ifdef GNSS_DEBUG
						Serial.println("Parsing packet...");
					#endif

					return parseUBXPacket(packet);
				}
			}
		}
	}

	return packet;
}

UBXRequestStatus GNSS::nextUBXACK(UBXMessage* msg, unsigned int timeout)
{
	UBXAck *ack;
	double start = (double) millis();
	double end = start + timeout;
	double now = start;

	while (end - now > 0) {
		ack = static_cast<UBXAck*>(nextUBXPacket(end - now, MessageId::ACK_ACK));

		Serial.println("ACK received");
		Serial.println(ack->isValid);
		Serial.println(ack->incomingMsgId, HEX);
		Serial.println(msg->msgId, HEX);

		if (ack->isValid
			&& ack->incomingMsgId == msg->msgId
		) {
			#ifdef GNSS_DEBUG
				Serial.println("ACK !");
			#endif

			return UBXRequestStatus::Success;
		}

		now = millis();
	}

	#ifdef GNSS_DEBUG
		Serial.println("NACK !");
	#endif

	return UBXRequestStatus::Timeout;
}

UBXMessage* GNSS::parseUBXPacket(UBXMessage* msg)
{
	bool successfull_parsing = false;

	switch (highByte(msg->msgId))
	{
		case MessageClass::ACK:
			return parseUBX_ACK(msg);
		case MessageClass::Aiding:
			return parseUBX_Aiding(msg);
		case MessageClass::Navigation:
			return parseUBX_Navigation(msg);
		case MessageClass::Configuration:
			return parseUBX_Configuration(msg);
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

UBXAck* GNSS::parseUBX_ACK(UBXMessage* msg)
{
	return parseUBX_ACK(static_cast<UBXAck*>(msg));
}

UBXAck* GNSS::parseUBX_ACK(UBXAck* msg)
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

UBXMessage* GNSS::parseUBX_Aiding(UBXMessage* msg)
{
	switch (msg->msgId)
	{
		case MessageId::Aiding_Almanach:
			return parseUBX_AidingAlmanach(msg);
		case MessageId::Aiding_AlmanachPlus:
			return parseUBX_AidingAlmanachPlus(msg);
		case MessageId::Aiding_AOP:
			return parseUBX_AidingAOP(msg);
		case MessageId::Aiding_Ephemeris:
			return parseUBX_AidingEphemeris(msg);
		case MessageId::Aiding_HealthUTCIonosphere:
			return parseUBX_AidingHealthUTCIonosphere(msg);
		case MessageId::Aiding_Init:
			return parseUBX_AidingInit(msg);
		default:
			break;
	}

	return msg;
}

UBXMessage* GNSS::parseUBX_Navigation(UBXMessage* msg)
{
	switch (msg->msgId)
	{
		case MessageId::Navigation_AOPStatus:
			return parseUBX_NavigationAOPStatus(msg);
		case MessageId::Navigation_Clock:
			return parseUBX_NavigationClock(msg);
		case MessageId::Navigation_DGPS:
			return parseUBX_NavigationDGPS(msg);
		case MessageId::Navigation_DOP:
			return parseUBX_NavigationDOP(msg);
		case MessageId::Navigation_PosECEF:
			return parseUBX_NavigationPosECEF(msg);
		case MessageId::Navigation_PosLLH:
			return parseUBX_NavigationPosLLH(msg);
		case MessageId::Navigation_PosVT:
			return parseUBX_NavigationPosVT(msg);
		case MessageId::Navigation_SBAS:
			return parseUBX_NavigationSBAS(msg);
		case MessageId::Navigation_SOL:
			return parseUBX_NavigationSOL(msg);
		case MessageId::Navigation_Status:
			return parseUBX_NavigationStatus(msg);
		case MessageId::Navigation_SpaceVehiculeInfo:
			return parseUBX_NavigationSpaceVehiculeInfo(msg);
		case MessageId::Navigation_TimeGPS:
			return parseUBX_NavigationTimeGPS(msg);
		case MessageId::Navigation_TimeUTC:
			return parseUBX_NavigationTimeUTC(msg);
		case MessageId::Navigation_VelECEF:
			return parseUBX_NavigationVelECEF(msg);
		case MessageId::Navigation_VelNED:
			return parseUBX_NavigationVelNED(msg);
		default:
			break;
	}

	return msg;
}

UBXMessage* GNSS::parseUBX_Configuration(UBXMessage* msg)
{
	switch (msg->msgId)
	{
		case MessageId::Configuration_Rate:
			return parseUBX_ConfigurationRate(msg);
		default:
			break;
	}

	return msg;
}

AidingAlmanach* GNSS::parseUBX_AidingAlmanach(UBXMessage* msg)
{
	return parseUBX_AidingAlmanach(static_cast<AidingAlmanach*>(msg));
}

AidingAlmanach* GNSS::parseUBX_AidingAlmanach(AidingAlmanach* msg)
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

AidingAlmanachPlus* GNSS::parseUBX_AidingAlmanachPlus(UBXMessage* msg)
{
	return parseUBX_AidingAlmanachPlus(static_cast<AidingAlmanachPlus*>(msg));
}

AidingAlmanachPlus* GNSS::parseUBX_AidingAlmanachPlus(AidingAlmanachPlus* msg)
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

AidingAOP* GNSS::parseUBX_AidingAOP(UBXMessage* msg)
{
	return parseUBX_AidingAOP(static_cast<AidingAOP*>(msg));
}

AidingAOP* GNSS::parseUBX_AidingAOP(AidingAOP* msg)
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

AidingEphemeris* GNSS::parseUBX_AidingEphemeris(UBXMessage* msg)
{
	return parseUBX_AidingEphemeris(static_cast<AidingEphemeris*>(msg));
}

AidingEphemeris* GNSS::parseUBX_AidingEphemeris(AidingEphemeris* msg)
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

AidingHealthUTCIonosphere* GNSS::parseUBX_AidingHealthUTCIonosphere(
	UBXMessage* msg
) {
	return parseUBX_AidingHealthUTCIonosphere(
		static_cast<AidingHealthUTCIonosphere*>(msg)
	);
}

AidingHealthUTCIonosphere* GNSS::parseUBX_AidingHealthUTCIonosphere(
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

AidingInit* GNSS::parseUBX_AidingInit(
	UBXMessage* msg
) {
	return parseUBX_AidingInit(
		static_cast<AidingInit*>(msg)
	);
}

AidingInit* GNSS::parseUBX_AidingInit(
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

NavigationAOPStatus* GNSS::parseUBX_NavigationAOPStatus(UBXMessage* msg)
{
	return parseUBX_NavigationAOPStatus(static_cast<NavigationAOPStatus*>(msg));
}

NavigationAOPStatus* GNSS::parseUBX_NavigationAOPStatus(NavigationAOPStatus* msg)
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

NavigationClock* GNSS::parseUBX_NavigationClock(UBXMessage* msg)
{
	return parseUBX_NavigationClock(static_cast<NavigationClock*>(msg));
}

NavigationClock* GNSS::parseUBX_NavigationClock(NavigationClock* msg)
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

NavigationDGPS* GNSS::parseUBX_NavigationDGPS(UBXMessage* msg)
{
	return parseUBX_NavigationDGPS(static_cast<NavigationDGPS*>(msg));
}

NavigationDGPS* GNSS::parseUBX_NavigationDGPS(NavigationDGPS* msg)
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

NavigationDOP* GNSS::parseUBX_NavigationDOP(UBXMessage* msg)
{
	return parseUBX_NavigationDOP(static_cast<NavigationDOP*>(msg));
}

NavigationDOP* GNSS::parseUBX_NavigationDOP(NavigationDOP* msg)
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

NavigationPosECEF* GNSS::parseUBX_NavigationPosECEF(UBXMessage* msg)
{
	return parseUBX_NavigationPosECEF(static_cast<NavigationPosECEF*>(msg));
}

NavigationPosECEF* GNSS::parseUBX_NavigationPosECEF(NavigationPosECEF* msg)
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


NavigationPosLLH* GNSS::parseUBX_NavigationPosLLH(UBXMessage* msg)
{
	return parseUBX_NavigationPosLLH(static_cast<NavigationPosLLH*>(msg));
}

NavigationPosLLH* GNSS::parseUBX_NavigationPosLLH(NavigationPosLLH* msg)
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

NavigationPosVT* GNSS::parseUBX_NavigationPosVT(UBXMessage* msg)
{
	return parseUBX_NavigationPosVT(static_cast<NavigationPosVT*>(msg));
}

NavigationPosVT* GNSS::parseUBX_NavigationPosVT(NavigationPosVT* msg)
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

NavigationSBAS* GNSS::parseUBX_NavigationSBAS(UBXMessage* msg)
{
	return parseUBX_NavigationSBAS(static_cast<NavigationSBAS*>(msg));
}

NavigationSBAS* GNSS::parseUBX_NavigationSBAS(NavigationSBAS* msg)
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

NavigationSOL* GNSS::parseUBX_NavigationSOL(UBXMessage* msg)
{
	return parseUBX_NavigationSOL(static_cast<NavigationSOL*>(msg));
}

NavigationSOL* GNSS::parseUBX_NavigationSOL(NavigationSOL* msg)
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

NavigationStatus* GNSS::parseUBX_NavigationStatus(UBXMessage* msg)
{
	return parseUBX_NavigationStatus(static_cast<NavigationStatus*>(msg));
}

NavigationStatus* GNSS::parseUBX_NavigationStatus(NavigationStatus* msg)
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

NavigationSpaceVehiculeInfo* GNSS::parseUBX_NavigationSpaceVehiculeInfo(
	UBXMessage* msg
) {
	return parseUBX_NavigationSpaceVehiculeInfo(
		static_cast<NavigationSpaceVehiculeInfo*>(msg)
	);
}

NavigationSpaceVehiculeInfo* GNSS::parseUBX_NavigationSpaceVehiculeInfo(
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

NavigationTimeGPS* GNSS::parseUBX_NavigationTimeGPS(UBXMessage* msg)
{
	return parseUBX_NavigationTimeGPS(static_cast<NavigationTimeGPS*>(msg));
}

NavigationTimeGPS* GNSS::parseUBX_NavigationTimeGPS(NavigationTimeGPS* msg)
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

NavigationTimeUTC* GNSS::parseUBX_NavigationTimeUTC(UBXMessage* msg)
{
	return parseUBX_NavigationTimeUTC(static_cast<NavigationTimeUTC*>(msg));
}

NavigationTimeUTC* GNSS::parseUBX_NavigationTimeUTC(NavigationTimeUTC* msg)
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

NavigationVelECEF* GNSS::parseUBX_NavigationVelECEF(UBXMessage* msg)
{
	return parseUBX_NavigationVelECEF(static_cast<NavigationVelECEF*>(msg));
}

NavigationVelECEF* GNSS::parseUBX_NavigationVelECEF(NavigationVelECEF* msg)
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

NavigationVelNED* GNSS::parseUBX_NavigationVelNED(UBXMessage* msg)
{
	return parseUBX_NavigationVelNED(static_cast<NavigationVelNED*>(msg));
}

NavigationVelNED* GNSS::parseUBX_NavigationVelNED(NavigationVelNED* msg)
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

ConfigurationRate* GNSS::parseUBX_ConfigurationRate(UBXMessage* msg)
{
	return parseUBX_ConfigurationRate(static_cast<ConfigurationRate*>(msg));
}

ConfigurationRate* GNSS::parseUBX_ConfigurationRate(ConfigurationRate* msg)
{
	msg->isValid &= msg->payloadLength == 6;

	if (msg->isValid) {
		msg->measRate = extractU2(0, msg->payload);
		msg->navRate = extractU2(2, msg->payload);
		msg->timeRef = extractU2(4, msg->payload);
	}

	return msg;
}

uint8_t GNSS::extractU1(uint8_t startIdx, byte* msgData)
{
  return msgData[startIdx] & 0xFF;
}

int8_t GNSS::extractI1(uint8_t startIdx, byte* msgData)
{
	union // Use a union to convert from uint32_t to int32_t
  {
      uint8_t unsignedLong;
      int8_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU1(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

byte GNSS::extractX1(uint8_t startIdx, byte* msgData)
{
  return msgData[startIdx] & 0xFF;
}

uint16_t GNSS::extractU2(uint8_t startIdx, byte* msgData)
{
  uint16_t val = 0;

  val |= (uint16_t)msgData[startIdx] & 0xFF;
  val |= (uint16_t)msgData[startIdx + 1] << 8;

  return val;
}

int16_t GNSS::extractI2(uint8_t startIdx, byte* msgData)
{
	union // Use a union to convert from uint32_t to int32_t
  {
      uint16_t unsignedLong;
      int16_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU2(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

uint16_t GNSS::extractX2(uint8_t startIdx, byte* msgData)
{
	return extractU2(startIdx, msgData);
}

uint32_t GNSS::extractU4(uint8_t startIdx, byte* msgData)
{
  uint32_t val = 0;

  val |= (uint32_t)msgData[startIdx] & 0xFF;
  val |= (uint32_t)msgData[startIdx + 1] << 8;
  val |= (uint32_t)msgData[startIdx + 2] << 16;
  val |= (uint32_t)msgData[startIdx + 3] << 24;

  return val;
}

//Just so there is no ambiguity about whether a uint32_t will cast to a int32_t correctly...
int32_t GNSS::extractI4(uint8_t startIdx, byte* msgData)
{
  union // Use a union to convert from uint32_t to int32_t
  {
      uint32_t unsignedLong;
      int32_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU4(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

uint32_t GNSS::extractX4(uint8_t startIdx, byte* msgData)
{
  return extractU4(startIdx, msgData);
}

uint32_t GNSS::extractR4(uint8_t startIdx, byte* msgData)
{
  return extractU4(startIdx, msgData);
}

uint64_t GNSS::extractU8(uint8_t startIdx, byte* msgData)
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

int64_t GNSS::extractI8(uint8_t startIdx, byte* msgData)
{
  union // Use a union to convert from uint32_t to int32_t
  {
      uint64_t unsignedLong;
      int64_t signedLong;
  } unsignedSigned;

  unsignedSigned.unsignedLong = extractU8(startIdx, msgData);

  return (unsignedSigned.signedLong);
}

uint64_t GNSS::extractR8(uint8_t startIdx, byte* msgData)
{
  return extractU8(startIdx, msgData);
}
