#include "GNSS.h"

GNSSConfiguration::GNSSConfiguration(UBXClient *c) {
	client = c;
}

ConfigurationAntenna* GNSSConfiguration::getAntenna() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Antenna;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting antenna configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Antenna
	);
}

void GNSSConfiguration::reset(
	uint16_t navBbrMask,
	ConfigurationResetMode resetMode
) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Reset;
	packet->payloadLength = 4;
	packet->payload[0] = ((uint16_t) navBbrMask) & 0xFF;
	packet->payload[1] = ((uint16_t) navBbrMask) << 8;
	packet->payload[2] = (uint8_t) resetMode;
	packet->payload[3] = 0x00; // reserved1

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Sending configuration reset command... "));
	#endif

	client->trySend(
		packet,
		MessageId::Configuration_Configuration
	);
}

void GNSSConfiguration::execCommand(
  uint32_t clearMask,
  uint32_t saveMask,
  uint32_t loadMask
) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Configuration;
	packet->payloadLength = 12;
	packet->payload[0] = clearMask & 0xFF;
	packet->payload[1] = clearMask << 8;
	packet->payload[2] = clearMask << 16;
	packet->payload[3] = clearMask << 24;
	packet->payload[4] = saveMask & 0xFF;
	packet->payload[5] = saveMask << 8;
	packet->payload[6] = saveMask << 16;
	packet->payload[7] = saveMask << 24;
	packet->payload[8] = loadMask & 0xFF;
	packet->payload[9] = loadMask << 8;
	packet->payload[10] = loadMask << 16;
	packet->payload[11] = loadMask << 24;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Sending configuration command... "));
	#endif

	client->trySend(
		packet,
		MessageId::Configuration_Configuration
	);
}

void GNSSConfiguration::execCommand(
  uint32_t clearMask,
  uint32_t saveMask,
  uint32_t loadMask,
  byte deviceMask
) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Configuration;
	packet->payloadLength = 13;
	packet->payload[0] = clearMask & 0xFF;
	packet->payload[1] = clearMask << 8;
	packet->payload[2] = clearMask << 16;
	packet->payload[3] = clearMask << 24;
	packet->payload[4] = saveMask & 0xFF;
	packet->payload[5] = saveMask << 8;
	packet->payload[6] = saveMask << 16;
	packet->payload[7] = saveMask << 24;
	packet->payload[8] = loadMask & 0xFF;
	packet->payload[9] = loadMask << 8;
	packet->payload[10] = loadMask << 16;
	packet->payload[11] = loadMask << 24;
	packet->payload[12] = deviceMask;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Sending antenna configuration command... "));
	#endif

	client->trySend(
		packet,
		MessageId::Configuration_Configuration
	);
}

ConfigurationDatum* GNSSConfiguration::getDatum() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Datum;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting datum configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Datum
	);
}

ConfigurationGNSS* GNSSConfiguration::getGNSS() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_GlobalNavigationSatelliteSystem;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting GNSS configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_GlobalNavigationSatelliteSystem
	);
}

ConfigurationInformation* GNSSConfiguration::getInformation() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Information;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting GNSS protocols configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Information
	);
}

ConfigurationInformation* GNSSConfiguration::getInformation(
	GNSSProtocol protocolId
) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Information;
	packet->payloadLength = 1;
	packet->payload[0] = (uint8_t) protocolId;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting GNSS protocol configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Information
	);
}

ConfigurationInterferenceMonitor* GNSSConfiguration::getInterferenceMonitor() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_InterferenceMonitor;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting jamming/interference monitor configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_InterferenceMonitor
	);
}

ConfigurationLogFilter* GNSSConfiguration::getLogFilter() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_LogFilter;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting log filter configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_LogFilter
	);
}

ConfigurationMessaging* GNSSConfiguration::getMsgRate(MessageId msgId) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Messaging;
	packet->payloadLength = 2;
	packet->payload[0] = highByte((uint16_t)msgId); // class id
	packet->payload[1] = lowByte((uint16_t)msgId); // msg id

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting message rate... "));
	#endif

	ConfigurationMessaging *result = client->trySend(
		packet,
		MessageId::Configuration_Messaging,
		6
	);

	return result;
}

UBXRequestStatus GNSSConfiguration::enableMessage(
	uint16_t msgId,
	bool changePort,
  byte port1,
  byte port2,
  byte port3,
  byte port4,
  byte port5,
  byte port6
) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Messaging;
	packet->payload[0] = highByte((uint16_t)msgId);
	packet->payload[1] = lowByte((uint16_t)msgId);
	packet->payload[2] = port1;
	packet->payloadLength = 3;

	if (changePort) {
		packet->payload[3] = port2;
		packet->payload[4] = port3;
		packet->payload[5] = port4;
		packet->payload[6] = port5;
		packet->payload[7] = port6;
		packet->payloadLength += 5;
	}

	#ifdef GNSS_LOG_INFO
		Serial.print(F("Enabling Message "));
		Serial.println(msgId, HEX);
	#endif

	return client->trySendWithACK(packet);
}

ConfigurationNavigation* GNSSConfiguration::getNavigation() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Navigation;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting navigation configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Navigation
	);
}

ConfigurationNavigationExpert* GNSSConfiguration::getNavigationExpert() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_NavigationExpert;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting expert navigation configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_NavigationExpert
	);
}

ConfigurationNMEA* GNSSConfiguration::getNMEA() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_NationalMarineElectronicsAssociation;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting NMEA configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_NationalMarineElectronicsAssociation
	);
}

ConfigurationPort* GNSSConfiguration::getPort() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Port;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting port configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Port
	);
}

ConfigurationPort* GNSSConfiguration::getPort(PortId portId) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Port;
	packet->payloadLength = 1;
	packet->payload[0] = (uint8_t) portId;

	#ifdef GNSS_LOG_INFO
		Serial.println(
			F("Getting port configuration for given port identifier... ")
		);
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Port
	);
}

UBXRequestStatus GNSSConfiguration::setPortRate(PortRate portRate) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Port;

	packet->payload[0] = (uint8_t) PortId::UART; // port ID

	packet->payload[1] = 0x00; // reserved

	// TX Ready PIN
	packet->payload[2] = 0x00;
	packet->payload[3] = 0x00;

	// mode
	packet->payload[4] = 0xD0;
	packet->payload[5] = 0x08;
	packet->payload[6] = 0x00;
	packet->payload[7] = 0x00;

	packet->payload[8] = ((uint32_t) portRate) & 0xFF;
	packet->payload[9] = ((uint32_t) portRate) >> 8;
	packet->payload[10] = ((uint32_t) portRate) >> 16;
	packet->payload[11] = ((uint32_t) portRate) >> 24;

	// inProtoMask
	packet->payload[12] = 0x07;
	packet->payload[13] = 0x00;

	// outProtoMask
	packet->payload[14] = 0x03;
	packet->payload[15] = 0x00;

	// flags
	packet->payload[16] = 0x00;
	packet->payload[17] = 0x00;

	// reserved
	packet->payload[18] = 0x00;
	packet->payload[19] = 0x00;

	packet->payloadLength = 20;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Setting Port Baud Rate... "));
	#endif

	return client->trySendWithACK(packet);
}

ConfigurationPower* GNSSConfiguration::getPower() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Power;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting power management configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Power
	);
}

ConfigurationRate* GNSSConfiguration::getRate() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Rate;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting Data Rate... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Rate
	);
}

UBXRequestStatus GNSSConfiguration::setRate(
	DataRate dataRate,
	GNSSReferenceTime timeRef
) {
	UBXPacket* packet = new UBXPacket();

	packet->msgId = MessageId::Configuration_Rate;

	// measurement rate (in ms)
	packet->payload[0] = lowByte((uint16_t) dataRate);
	packet->payload[1] = highByte((uint16_t) dataRate);

	// navigation rate, cannot be changed
	packet->payload[2] = 0x01;
	packet->payload[3] = 0x00;

	// reference time (0: UTC, 1: GPS)
	packet->payload[4] = lowByte((uint16_t) timeRef);
	packet->payload[5] = highByte((uint16_t) timeRef);

	packet->payloadLength = 6;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Setting Data Rate... "));
	#endif

	return client->trySendWithACK(packet);
}

ConfigurationRemoteInventory* GNSSConfiguration::getRemoteInventory() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_RemoteInventory;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting remote inventory configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_RemoteInventory
	);
}

ConfigurationReceiver* GNSSConfiguration::getReceiver() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_Receiver;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting receiver configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_Receiver
	);
}

ConfigurationSBAS* GNSSConfiguration::getSBAS() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_SatelliteBasedAugmentationSystems;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(
			F("Getting satellite based augmentation systems configuration... ")
		);
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_SatelliteBasedAugmentationSystems
	);
}

ConfigurationTimePulse* GNSSConfiguration::getTimePulse() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_TimePulse;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(
			F("Getting time pulse configuration... ")
		);
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_TimePulse
	);
}

ConfigurationTimePulse* GNSSConfiguration::getTimePulse(uint8_t tpIdx) {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_TimePulse;
	packet->payloadLength = 1;
	packet->payload[0] = tpIdx;

	#ifdef GNSS_LOG_INFO
		Serial.println(
			F("Getting time pulse configuration at given index... ")
		);
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_TimePulse
	);
}

ConfigurationUSB* GNSSConfiguration::getUSB() {
	UBXPacket* packet = new UBXPacket();
	packet->msgId = MessageId::Configuration_USB;
	packet->payloadLength = 0;

	#ifdef GNSS_LOG_INFO
		Serial.println(F("Getting USB configuration... "));
	#endif

	return client->trySend(
		packet,
		MessageId::Configuration_USB
	);
}

void GNSSConfiguration::print(Stream* stream) {
  FREERAM_PRINT;

  printAntenna(stream);
  printDatum(stream);
  printGNSS(stream);
  printInformation(stream, GNSSProtocol::UBX);
  printInterferenceMonitor(stream);
  printLogFilter(stream);
  printMsgRate(stream, MessageId::Navigation_PosVT);
  printNavigation(stream);
  printNavigationExpert(stream);
  printNMEA(stream);
  printPort(stream);
  printPort(stream, PortId::USB);
  printPower(stream);
  printRate(stream);
  printReceiver(stream);
  printRemoteInventory(stream);
  printSBAS(stream);
  printTimePulse(stream);
  printTimePulse(stream, 1);
  printUSB(stream);

  FREERAM_PRINT;
}

void GNSSConfiguration::printAntenna(Stream* stream) {
  getAntenna()
    ->print(stream);
}

void GNSSConfiguration::printDatum(Stream* stream) {
  getDatum()
    ->print(stream);
}

void GNSSConfiguration::printGNSS(Stream* stream) {
  getGNSS()
    ->print(stream);
}

void GNSSConfiguration::printInformation(
	Stream* stream,
	GNSSProtocol protocolId
) {
  getInformation(protocolId)
    ->print(stream);
}

void GNSSConfiguration::printInterferenceMonitor(Stream* stream) {
  getInterferenceMonitor()
    ->print(stream);
}

void GNSSConfiguration::printLogFilter(Stream* stream) {
  getLogFilter()
    ->print(stream);
}

void GNSSConfiguration::printMsgRate(Stream* stream, MessageId msgId) {
  getMsgRate(msgId)
    ->print(stream);
}

void GNSSConfiguration::printNavigation(Stream* stream) {
  getNavigation()
    ->print(stream);
}

void GNSSConfiguration::printNavigationExpert(Stream* stream) {
  getNavigationExpert()
    ->print(stream);
}

void GNSSConfiguration::printNMEA(Stream* stream) {
  getNMEA()
    ->print(stream);
}

void GNSSConfiguration::printPort(Stream* stream) {
  getPort()
    ->print(stream);
}

void GNSSConfiguration::printPort(Stream* stream, PortId portId) {
  getPort(portId)
    ->print(stream);
}

void GNSSConfiguration::printPower(Stream* stream) {
  getPower()
    ->print(stream);
}

void GNSSConfiguration::printRate(Stream* stream) {
  getRate()
    ->print(stream);
}

void GNSSConfiguration::printReceiver(Stream* stream) {
  getReceiver()
    ->print(stream);
}

void GNSSConfiguration::printRemoteInventory(Stream* stream) {
  getRemoteInventory()
    ->print(stream);
}

void GNSSConfiguration::printSBAS(Stream* stream) {
  getSBAS()
    ->print(stream);
}

void GNSSConfiguration::printTimePulse(Stream* stream) {
  getTimePulse()
    ->print(stream);
}

void GNSSConfiguration::printTimePulse(Stream* stream, uint8_t tpIdx) {
  getTimePulse(tpIdx)
    ->print(stream);
}

void GNSSConfiguration::printUSB(Stream* stream) {
  getUSB()
    ->print(stream);
}

