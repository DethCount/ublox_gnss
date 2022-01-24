#include "GNSS.h"

GNSSNavigation::GNSSNavigation(UBXClient *c) {
	client = c;
}

NavigationAOPStatus* GNSSNavigation::getAOPStatus() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_AOPStatus;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation AOP status... ");
	#endif

	return static_cast<NavigationAOPStatus*>(client->trySend(
		getMsg,
		MessageId::Navigation_AOPStatus
	));
}

NavigationClock* GNSSNavigation::getClock() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_Clock;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation clock... ");
	#endif

	return static_cast<NavigationClock*>(client->trySend(
		getMsg,
		MessageId::Navigation_Clock
	));
}

NavigationDGPS* GNSSNavigation::getDGPS() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_DGPS;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation DGPS... ");
	#endif

	return static_cast<NavigationDGPS*>(client->trySend(
		getMsg,
		MessageId::Navigation_DGPS
	));
}

NavigationDOP* GNSSNavigation::getDOP() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_DOP;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation DOP... ");
	#endif

	return static_cast<NavigationDOP*>(client->trySend(
		getMsg,
		MessageId::Navigation_DOP
	));
}

NavigationPosECEF* GNSSNavigation::getPosECEF() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_PosECEF;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation ECEF position... ");
	#endif

	return static_cast<NavigationPosECEF*>(client->trySend(
		getMsg,
		MessageId::Navigation_PosECEF
	));
}

NavigationPosLLH* GNSSNavigation::getPosLLH() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_PosLLH;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation LLH position... ");
	#endif

	return static_cast<NavigationPosLLH*>(client->trySend(
		getMsg,
		MessageId::Navigation_PosLLH
	));
}

NavigationPosVT* GNSSNavigation::getPosVT() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_PosVT;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation position velocity and time... ");
	#endif

	return static_cast<NavigationPosVT*>(client->trySend(
		getMsg,
		MessageId::Navigation_PosVT
	));
}

NavigationSBAS* GNSSNavigation::getSBAS() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_SBAS;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation SBAS... ");
	#endif

	return static_cast<NavigationSBAS*>(client->trySend(
		getMsg,
		MessageId::Navigation_SBAS
	));
}

NavigationSOL* GNSSNavigation::getSOL() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_SOL;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation SOL... ");
	#endif

	return static_cast<NavigationSOL*>(client->trySend(
		getMsg,
		MessageId::Navigation_SOL
	));
}

NavigationStatus* GNSSNavigation::getStatus() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_Status;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation status... ");
	#endif

	return static_cast<NavigationStatus*>(client->trySend(
		getMsg,
		MessageId::Navigation_Status
	));
}

NavigationSpaceVehiculeInfo* GNSSNavigation::getSpaceVehiculeInfo() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_SpaceVehiculeInfo;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation space vehicule information... ");
	#endif

	return static_cast<NavigationSpaceVehiculeInfo*>(client->trySend(
		getMsg,
		MessageId::Navigation_SpaceVehiculeInfo
	));
}

NavigationTimeGPS* GNSSNavigation::getTimeGPS() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_TimeGPS;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation GPS time... ");
	#endif

	return static_cast<NavigationTimeGPS*>(client->trySend(
		getMsg,
		MessageId::Navigation_TimeGPS
	));
}

NavigationTimeUTC* GNSSNavigation::getTimeUTC() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_TimeUTC;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation UTC time... ");
	#endif

	return static_cast<NavigationTimeUTC*>(client->trySend(
		getMsg,
		MessageId::Navigation_TimeUTC
	));
}

NavigationVelECEF* GNSSNavigation::getVelECEF() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_VelECEF;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation ECEF velocity... ");
	#endif

	return static_cast<NavigationVelECEF*>(client->trySend(
		getMsg,
		MessageId::Navigation_VelECEF
	));
}

NavigationVelNED* GNSSNavigation::getVelNED() {
	UBXMessage* getMsg = new UBXMessage();
	getMsg->msgId = MessageId::Navigation_VelNED;
	getMsg->payloadLength = 0;

	#ifdef GNSS_DEBUG
		Serial.print("Getting navigation NED velocity... ");
	#endif

	return static_cast<NavigationVelNED*>(client->trySend(
		getMsg,
		MessageId::Navigation_VelNED
	));
}
