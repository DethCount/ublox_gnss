class UBXParser {
  public:
    UBXMessage* parse(UBXPacket* packet);

    UBXAck* parseACK(UBXPacket* packet);
    UBXMessage* parseAiding(UBXPacket* packet);
    UBXMessage* parseNavigation(UBXPacket* packet);
    UBXMessage* parseConfiguration(UBXPacket* packet);
    UBXMessage* parseInformation(UBXPacket* packet);
    UBXMessage* parseLog(UBXPacket* packet);
    UBXMessage* parseMonitoring(UBXPacket* packet);
    UBXMessage* parseReceiverManager(UBXPacket* packet);
    UBXMessage* parseTiming(UBXPacket* packet);

    AidingAlmanach* parseAidingAlmanach(UBXPacket* packet);
    AidingAlmanachPlus* parseAidingAlmanachPlus(UBXPacket* packet);
    AidingAOP* parseAidingAOP(UBXPacket* packet);
    AidingEphemeris* parseAidingEphemeris(UBXPacket* packet);
    AidingHealthUTCIonosphere* parseAidingHealthUTCIonosphere(
      UBXPacket* packet
    );
    AidingInit* parseAidingInit(UBXPacket* packet);

    NavigationAOPStatus* parseNavigationAOPStatus(UBXPacket* packet);
    NavigationClock* parseNavigationClock(UBXPacket* packet);
    NavigationDGPS* parseNavigationDGPS(UBXPacket* packet);
    NavigationDOP* parseNavigationDOP(UBXPacket* packet);
    NavigationPosECEF* parseNavigationPosECEF(UBXPacket* packet);
    NavigationPosLLH* parseNavigationPosLLH(UBXPacket* packet);
    NavigationPosVT* parseNavigationPosVT(UBXPacket* packet);
    NavigationSBAS* parseNavigationSBAS(UBXPacket* packet);
    NavigationSOL* parseNavigationSOL(UBXPacket* packet);
    NavigationStatus* parseNavigationStatus(UBXPacket* packet);
    NavigationSpaceVehiculeInfo* parseNavigationSpaceVehiculeInfo(
      UBXPacket* packet
    );
    NavigationTimeGPS* parseNavigationTimeGPS(UBXPacket* packet);
    NavigationTimeUTC* parseNavigationTimeUTC(UBXPacket* packet);
    NavigationVelECEF* parseNavigationVelECEF(UBXPacket* packet);
    NavigationVelNED* parseNavigationVelNED(UBXPacket* packet);

    ConfigurationAntenna* parseConfigurationAntenna(UBXPacket* packet);
    ConfigurationDatum* parseConfigurationDatum(UBXPacket* packet);
    ConfigurationGNSS* parseConfigurationGNSS(UBXPacket* packet);
    ConfigurationInformation* parseConfigurationInformation(
      UBXPacket* packet,
      uint16_t startIdx = 0
    );
    ConfigurationInterferenceMonitor* parseConfigurationInterferenceMonitor(
      UBXPacket* packet
    );
    ConfigurationLogFilter* parseConfigurationLogFilter(UBXPacket* packet);
    ConfigurationMessaging* parseConfigurationMessaging(UBXPacket* packet);
    ConfigurationNavigation* parseConfigurationNavigation(UBXPacket* packet);
    ConfigurationNavigationExpert* parseConfigurationNavigationExpert(
      UBXPacket* packet
    );
    ConfigurationNMEA* parseConfigurationNMEA(UBXPacket* packet);
    ConfigurationPort* parseConfigurationPort(
      UBXPacket* packet,
      uint16_t startIdx = 0
    );
    ConfigurationPower* parseConfigurationPower(UBXPacket* packet);
    ConfigurationRate* parseConfigurationRate(UBXPacket* packet);
    ConfigurationRemoteInventory* parseConfigurationRemoteInventory(
      UBXPacket* packet
    );
    ConfigurationReceiver* parseConfigurationReceiver(UBXPacket* packet);
    ConfigurationSBAS* parseConfigurationSBAS(UBXPacket* packet);
    ConfigurationTimePulse* parseConfigurationTimePulse(UBXPacket* packet);
    ConfigurationUSB* parseConfigurationUSB(UBXPacket* packet);

    InformationDebug* parseInformationDebug(UBXPacket* packet);
    InformationError* parseInformationError(UBXPacket* packet);
    InformationNotice* parseInformationNotice(UBXPacket* packet);
    InformationTest* parseInformationTest(UBXPacket* packet);
    InformationWarning* parseInformationWarning(UBXPacket* packet);

    LogFindTime* parseLogFindTime(UBXPacket* packet);
    LogInfo* parseLogInfo(UBXPacket* packet);
    LogRetrievePosition* parseLogRetrievePosition(UBXPacket* packet);
    LogRetrieveString* parseLogRetrieveString(UBXPacket* packet);

    MonitoringHardwareExtended* parseMonitoringHardwareExtended(
      UBXPacket* packet
    );
    MonitoringHardware* parseMonitoringHardware(UBXPacket* packet);
    MonitoringIO* parseMonitoringIO(UBXPacket* packet, uint16_t startIdx = 0);
    MonitoringMsgParseProcess* parseMonitoringMsgParseProcess(UBXPacket* packet);
    MonitoringReceiver* parseMonitoringReceiver(UBXPacket* packet);
    MonitoringReceiverBuffer* parseMonitoringReceiverBuffer(UBXPacket* packet);
    MonitoringTransmitterBuffer* parseMonitoringTransmitterBuffer(
      UBXPacket* packet
    );
    MonitoringVersion* parseMonitoringVersion(UBXPacket* packet);

    ReceiverManagerAlmanach* parseReceiverManagerAlmanach(UBXPacket* packet);
    ReceiverManagerEphemeris* parseReceiverManagerEphemeris(UBXPacket* packet);
    ReceiverManagerRaw* parseReceiverManagerRaw(UBXPacket* packet);
    ReceiverManagerSubframe* parseReceiverManagerSubframe(UBXPacket* packet);
    ReceiverManagerSpaceVehiculeInfo* parseReceiverManagerSpaceVehiculeInfo(
      UBXPacket* packet
    );

    TimingMark* parseTimingMark(UBXPacket* packet);
    TimingPulse* parseTimingPulse(UBXPacket* packet);
    TimingVerification* parseTimingVerification(UBXPacket* packet);

    uint8_t extractU1(uint8_t startIdx, byte* msgData);
    int8_t extractI1(uint8_t startIdx, byte* msgData);
    byte extractX1(uint8_t startIdx, byte* msgData);

    uint16_t extractU2(uint8_t startIdx, byte* msgData);
    int16_t extractI2(uint8_t startIdx, byte* msgData);
    uint16_t extractX2(uint8_t startIdx, byte* msgData);

    uint32_t extractU4(uint8_t startIdx, byte* msgData);
    int32_t extractI4(uint8_t startIdx, byte* msgData);
    uint32_t extractX4(uint8_t startIdx, byte* msgData);
    uint32_t extractR4(uint8_t startIdx, byte* msgData);

    uint64_t extractU8(uint8_t startIdx, byte* msgData);
    int64_t extractI8(uint8_t startIdx, byte* msgData);
    uint64_t extractR8(uint8_t startIdx, byte* msgData);

    char extractCH(uint8_t startIdx, byte* msgData);
    void extractCH(uint8_t startIdx, byte* msgData, int length, char* out);
};
