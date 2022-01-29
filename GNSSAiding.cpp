#include "GNSS.h"

GNSSAiding::GNSSAiding(UBXClient *c) {
  client = c;
}

AidingAlmanach* GNSSAiding::getAlmanach() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Almanach;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach... ");
	#endif

	return static_cast<AidingAlmanach*>(client->trySend(
		packet,
		MessageId::Aiding_Almanach
	));
}

AidingAlmanach* GNSSAiding::getAlmanach(uint8_t svid) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Almanach;
	packet->payloadLength = 1;
	packet->payload[0] = svid;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach... ");
	#endif

	return static_cast<AidingAlmanach*>(client->trySend(
		packet,
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
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_AlmanachPlus;
	packet->payloadLength = 16;
	packet->payload[0] = idSize;
	packet->payload[1] = type;
	packet->payload[2] = lowByte(ofs);
	packet->payload[3] = highByte(ofs);
	packet->payload[4] = lowByte(size);
	packet->payload[5] = highByte(size);
	packet->payload[6] = lowByte(fileId);
	packet->payload[7] = highByte(fileId);
	packet->payload[8] = lowByte(dataSize);
	packet->payload[9] = highByte(dataSize);
	packet->payload[10] = id1;
	packet->payload[11] = id2;
	packet->payload[12] = id3 & 0xFF;
	packet->payload[13] = (id3 >> 8) & 0xFF;
	packet->payload[14] = (id3 >> 16) & 0xFF;
	packet->payload[15] = (id3 >> 24) & 0xFF;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding almanach plus... ");
	#endif

	return static_cast<AidingAlmanachPlus*>(client->trySend(
		packet,
		MessageId::Aiding_AlmanachPlus
	));
}

AidingAOP* GNSSAiding::getAOP() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_AOP;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding AOP... ");
	#endif

	return static_cast<AidingAOP*>(client->trySend(
		packet,
		MessageId::Aiding_AOP
	));
}

AidingAOP* GNSSAiding::getAOP(uint8_t svid) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_AOP;
	packet->payloadLength = 1;
	packet->payload[0] = svid;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding AOP for given svid... ");
	#endif

	return static_cast<AidingAOP*>(client->trySend(
		packet,
		MessageId::Aiding_AOP
	));
}

void GNSSAiding::getData() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Data;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print(
			"Requesting aiding data... Expecting AID-INI, AID-HUI, AID-EPH and AID-ALM messages."
		);
	#endif

	client->trySend(
		packet,
		MessageId::Aiding_Data
	);
}

AidingEphemeris* GNSSAiding::getEphemeris() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Ephemeris;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding ephemeris... ");
	#endif

	return static_cast<AidingEphemeris*>(client->trySend(
		packet,
		MessageId::Aiding_Ephemeris
	));
}

AidingEphemeris* GNSSAiding::getEphemeris(uint8_t svid) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Ephemeris;
	packet->payloadLength = 1;
	packet->payload[0] = svid;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding ephemeris for given svid... ");
	#endif

	return static_cast<AidingEphemeris*>(client->trySend(
		packet,
		MessageId::Aiding_Ephemeris
	));
}

AidingHealthUTCIonosphere* GNSSAiding::getHealthUTCIonosphere() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_HealthUTCIonosphere;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding health, UTC and ionosphere... ");
	#endif

	return static_cast<AidingHealthUTCIonosphere*>(client->trySend(
		packet,
		MessageId::Aiding_HealthUTCIonosphere
	));
}

AidingInit* GNSSAiding::getInit() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Init;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting aiding initial data... ");
	#endif

	return static_cast<AidingInit*>(client->trySend(
		packet,
		MessageId::Aiding_Init
	));
}

void GNSSAiding::requestAll() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Aiding_Request;
	packet->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Request aiding data...");
	#endif

	client->trySend(
		packet,
		MessageId::Aiding_Request
	);
}
