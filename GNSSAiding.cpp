#include "GNSS.h"

GNSSAiding::GNSSAiding(UBXClient *c) {
  client = c;
}

AidingAlmanach* GNSSAiding::getAlmanach() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Almanach;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach... ");
	#endif

	return static_cast<AidingAlmanach*>(client->trySend(
		getMsg,
		MessageId::Aiding_Almanach
	));
}

AidingAlmanach* GNSSAiding::getAlmanach(uint8_t svid) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Almanach;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = svid;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach... ");
	#endif

	return static_cast<AidingAlmanach*>(client->trySend(
		getMsg,
		MessageId::Aiding_Almanach
	));
}

AidingAlmanachPlus* GNSSAiding::getAlmanachPlus(
  uint8_t idSize,
  uint8_t type,
  uint16_t ofs,
  uint16_t size,
  uint16_t fileId,
  uint16_t dataSize,
  uint8_t id1,
  uint8_t id2,
  uint16_t id3
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_AlmanachPlus;
	getMsg->payloadLength = 16;
	getMsg->payload[0] = idSize;
	getMsg->payload[1] = type;
	getMsg->payload[2] = lowByte(ofs);
	getMsg->payload[3] = highByte(ofs);
	getMsg->payload[4] = lowByte(size);
	getMsg->payload[5] = highByte(size);
	getMsg->payload[6] = lowByte(fileId);
	getMsg->payload[7] = highByte(fileId);
	getMsg->payload[8] = lowByte(dataSize);
	getMsg->payload[9] = highByte(dataSize);
	getMsg->payload[10] = id1;
	getMsg->payload[11] = id2;
	getMsg->payload[12] = id3 & 0xFF;
	getMsg->payload[13] = (id3 >> 8) & 0xFF;
	getMsg->payload[14] = (id3 >> 16) & 0xFF;
	getMsg->payload[15] = (id3 >> 24) & 0xFF;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach plus... ");
	#endif

	return static_cast<AidingAlmanachPlus*>(client->trySend(
		getMsg,
		MessageId::Aiding_AlmanachPlus
	));
}

AidingAOP* GNSSAiding::getAOP() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_AOP;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding AOP... ");
	#endif

	return static_cast<AidingAOP*>(client->trySend(
		getMsg,
		MessageId::Aiding_AOP
	));
}

AidingAOP* GNSSAiding::getAOP(uint8_t svid) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_AOP;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = svid;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding AOP for given svid... ");
	#endif

	return static_cast<AidingAOP*>(client->trySend(
		getMsg,
		MessageId::Aiding_AOP
	));
}

void GNSSAiding::getData() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Data;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print(
			"Requesting aiding data... Expecting AID-INI, AID-HUI, AID-EPH and AID-ALM messages."
		);
	#endif

	client->trySend(
		getMsg,
		MessageId::Aiding_Data
	);
}

AidingEphemeris* GNSSAiding::getEphemeris() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Ephemeris;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding ephemeris... ");
	#endif

	return static_cast<AidingEphemeris*>(client->trySend(
		getMsg,
		MessageId::Aiding_Ephemeris
	));
}

AidingEphemeris* GNSSAiding::getEphemeris(uint8_t svid) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Ephemeris;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = svid;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding ephemeris for given svid... ");
	#endif

	return static_cast<AidingEphemeris*>(client->trySend(
		getMsg,
		MessageId::Aiding_Ephemeris
	));
}

AidingHealthUTCIonosphere* GNSSAiding::getHealthUTCIonosphere() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_HealthUTCIonosphere;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding health, UTC and ionosphere... ");
	#endif

	return static_cast<AidingHealthUTCIonosphere*>(client->trySend(
		getMsg,
		MessageId::Aiding_HealthUTCIonosphere
	));
}

AidingInit* GNSSAiding::getInit() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Init;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding initial data... ");
	#endif

	return static_cast<AidingInit*>(client->trySend(
		getMsg,
		MessageId::Aiding_Init
	));
}

void GNSSAiding::requestAll() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Aiding_Request;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Request aiding data...");
	#endif

	client->trySend(
		getMsg,
		MessageId::Aiding_Request
	);
}
