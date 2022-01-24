#include "GNSS.h"

GNSSConfiguration::GNSSConfiguration(UBXClient *c) {
	client = c;
}

ConfigurationAntenna* GNSSConfiguration::getAntenna() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_Antenna;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting antenna configuration... ");
	#endif

	return static_cast<ConfigurationAntenna*>(client->trySend(
		getMsg,
		MessageId::Configuration_Antenna
	));
}

void GNSSConfiguration::sendCommand(
  uint32_t clearMask,
  uint32_t saveMask,
  uint32_t loadMask
) {
	UBXMessage* cmd = new UBXMessage();
	cmd->msgId = MessageId::Configuration_Configuration;
	cmd->payloadLength = 12;
	cmd->payload[0] = clearMask & 0xFF;
	cmd->payload[1] = clearMask << 8;
	cmd->payload[2] = clearMask << 16;
	cmd->payload[3] = clearMask << 24;
	cmd->payload[4] = saveMask & 0xFF;
	cmd->payload[5] = saveMask << 8;
	cmd->payload[6] = saveMask << 16;
	cmd->payload[7] = saveMask << 24;
	cmd->payload[8] = loadMask & 0xFF;
	cmd->payload[9] = loadMask << 8;
	cmd->payload[10] = loadMask << 16;
	cmd->payload[11] = loadMask << 24;

	#ifdef GNSS_DEBUG
		Serial.print("Sending antenna configuration command... ");
	#endif

	client->trySend(
		cmd,
		MessageId::Configuration_Configuration
	);
}

void GNSSConfiguration::sendCommand(
  uint32_t clearMask,
  uint32_t saveMask,
  uint32_t loadMask,
  byte deviceMask
) {
	UBXMessage* cmd = new UBXMessage();
	cmd->msgId = MessageId::Configuration_Configuration;
	cmd->payloadLength = 13;
	cmd->payload[0] = clearMask & 0xFF;
	cmd->payload[1] = clearMask << 8;
	cmd->payload[2] = clearMask << 16;
	cmd->payload[3] = clearMask << 24;
	cmd->payload[4] = saveMask & 0xFF;
	cmd->payload[5] = saveMask << 8;
	cmd->payload[6] = saveMask << 16;
	cmd->payload[7] = saveMask << 24;
	cmd->payload[8] = loadMask & 0xFF;
	cmd->payload[9] = loadMask << 8;
	cmd->payload[10] = loadMask << 16;
	cmd->payload[11] = loadMask << 24;
	cmd->payload[12] = deviceMask;

	#ifdef GNSS_DEBUG
		Serial.print("Sending antenna configuration command... ");
	#endif

	client->trySend(
		cmd,
		MessageId::Configuration_Configuration
	);
}

ConfigurationDatum* GNSSConfiguration::getDatum() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_Datum;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting datum configuration... ");
	#endif

	return static_cast<ConfigurationDatum*>(client->trySend(
		getMsg,
		MessageId::Configuration_Datum
	));
}

ConfigurationGNSS* GNSSConfiguration::getGNSS() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_GlobalNavigationSatelliteSystem;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting GNSS configuration... ");
	#endif

	return static_cast<ConfigurationGNSS*>(client->trySend(
		getMsg,
		MessageId::Configuration_GlobalNavigationSatelliteSystem
	));
}

ConfigurationInformation* GNSSConfiguration::getInformation() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_Information;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting GNSS protocols configuration... ");
	#endif

	return static_cast<ConfigurationInformation*>(client->trySend(
		getMsg,
		MessageId::Configuration_Information
	));
}

ConfigurationInformation* GNSSConfiguration::getInformation(
	GNSSProtocol protocolId
) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_Information;
	getMsg->payloadLength = 1;
	getMsg->payload[0] = (uint8_t) protocolId;

	#ifdef GNSS_DEBUG
		Serial.print("Getting GNSS protocol configuration... ");
	#endif

	return static_cast<ConfigurationInformation*>(client->trySend(
		getMsg,
		MessageId::Configuration_Information
	));
}

ConfigurationInterferenceMonitor* GNSSConfiguration::getInterferenceMonitor() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_InterferenceMonitor;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting jamming/interference monitor configuration... ");
	#endif

	return static_cast<ConfigurationInterferenceMonitor*>(client->trySend(
		getMsg,
		MessageId::Configuration_InterferenceMonitor
	));
}

ConfigurationLogFilter* GNSSConfiguration::getLogFilter() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_LogFilter;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting log filter configuration... ");
	#endif

	return static_cast<ConfigurationLogFilter*>(client->trySend(
		getMsg,
		MessageId::Configuration_LogFilter
	));
}

uint8_t GNSSConfiguration::getMsgRate(MessageId msgId) {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_Messaging;
	getMsg->payloadLength = 2;
	getMsg->payload[0] = highByte(msgId); // class id
	getMsg->payload[1] = lowByte(msgId); // msg id

	#ifdef GNSS_DEBUG
		Serial.print("Getting message rate... ");
	#endif

	ConfigurationMessaging *result = static_cast<ConfigurationMessaging*>(
		client->trySend(
			getMsg,
			MessageId::Configuration_Messaging
		)
	);

	result->isValid &= result->msgId == msgId;

	return result->rate;
}

ConfigurationNavigation* GNSSConfiguration::getNavigation() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_Navigation;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation configuration... ");
	#endif

	return static_cast<ConfigurationNavigation*>(
		client->trySend(
			getMsg,
			MessageId::Configuration_Navigation
		)
	);
}

ConfigurationNavigationExpert* GNSSConfiguration::getNavigationExpert() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Configuration_NavigationExpert;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting expert navigation configuration... ");
	#endif

	return static_cast<ConfigurationNavigationExpert*>(
		client->trySend(
			getMsg,
			MessageId::Configuration_NavigationExpert
		)
	);
}

ConfigurationRate* GNSSConfiguration::getRate() {
	UBXMessage* getDataRate = new UBXMessage();
	getDataRate->msgId = MessageId::Configuration_Rate;
	getDataRate->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting Data Rate... ");
	#endif

	return static_cast<ConfigurationRate*>(client->trySend(
		getDataRate,
		MessageId::Configuration_Rate
	));
}

UBXRequestStatus GNSSConfiguration::setRate(DataRate dataRate) {
	UBXMessage* setDataRate = new UBXMessage();

	setDataRate->msgId = MessageId::Configuration_Rate;

	// measurement rate (in ms)
	setDataRate->payload[0] = lowByte((uint16_t) dataRate);
	setDataRate->payload[1] = highByte((uint16_t) dataRate);

	// navigation rate, cannot be changed
	setDataRate->payload[2] = 0x01;
	setDataRate->payload[3] = 0x00;

	// reference time (0: UTC, 1: GPS)
	setDataRate->payload[4] = 0x01;
	setDataRate->payload[5] = 0x00;

	setDataRate->payloadLength = 6;

	#ifdef GNSS_DEBUG
		Serial.print("Setting Data Rate... ");
	#endif

	return client->trySendWithACK(setDataRate);
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

	#ifdef GNSS_DEBUG
		Serial.print("Enabling Message ");
		Serial.println(msgId, HEX);
	#endif

	return client->trySendWithACK(enableMsg);
}

UBXRequestStatus GNSSConfiguration::setPortRate(PortRate portRate) {
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

	#ifdef GNSS_DEBUG
		Serial.print("Setting Port Baud Rate... ");
	#endif

	return client->trySendWithACK(setPortRate);
}
