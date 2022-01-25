class UBXParser {
  public:
    UBXMessage* parse(UBXMessage* msg);

    UBXAck* parseACK(UBXMessage* msg);
    UBXAck* parseACK(UBXAck* msg);

    UBXMessage* parseAiding(UBXMessage* msg);
    UBXMessage* parseNavigation(UBXMessage* msg);
    UBXMessage* parseConfiguration(UBXMessage* msg);
    UBXMessage* parseInformation(UBXMessage* msg);

    AidingAlmanach* parseAidingAlmanach(UBXMessage* msg);
    AidingAlmanach* parseAidingAlmanach(AidingAlmanach* msg);

    AidingAlmanachPlus* parseAidingAlmanachPlus(UBXMessage* msg);
    AidingAlmanachPlus* parseAidingAlmanachPlus(AidingAlmanachPlus* msg);

    AidingAOP* parseAidingAOP(UBXMessage* msg);
    AidingAOP* parseAidingAOP(AidingAOP* msg);

    AidingEphemeris* parseAidingEphemeris(UBXMessage* msg);
    AidingEphemeris* parseAidingEphemeris(AidingEphemeris* msg);

    AidingHealthUTCIonosphere* parseAidingHealthUTCIonosphere(
      UBXMessage* msg
    );
    AidingHealthUTCIonosphere* parseAidingHealthUTCIonosphere(
      AidingHealthUTCIonosphere* msg
    );

    AidingInit* parseAidingInit(UBXMessage* msg);
    AidingInit* parseAidingInit(AidingInit* msg);

    NavigationAOPStatus* parseNavigationAOPStatus(UBXMessage* msg);
    NavigationAOPStatus* parseNavigationAOPStatus(NavigationAOPStatus* msg);

    NavigationClock* parseNavigationClock(UBXMessage* msg);
    NavigationClock* parseNavigationClock(NavigationClock* msg);

    NavigationDGPS* parseNavigationDGPS(UBXMessage* msg);
    NavigationDGPS* parseNavigationDGPS(NavigationDGPS* msg);

    NavigationDOP* parseNavigationDOP(UBXMessage* msg);
    NavigationDOP* parseNavigationDOP(NavigationDOP* msg);

    NavigationPosECEF* parseNavigationPosECEF(UBXMessage* msg);
    NavigationPosECEF* parseNavigationPosECEF(NavigationPosECEF* msg);

    NavigationPosLLH* parseNavigationPosLLH(UBXMessage* msg);
    NavigationPosLLH* parseNavigationPosLLH(NavigationPosLLH* msg);

    NavigationPosVT* parseNavigationPosVT(UBXMessage* msg);
    NavigationPosVT* parseNavigationPosVT(NavigationPosVT* msg);

    NavigationSBAS* parseNavigationSBAS(UBXMessage* msg);
    NavigationSBAS* parseNavigationSBAS(NavigationSBAS* msg);

    NavigationSOL* parseNavigationSOL(UBXMessage* msg);
    NavigationSOL* parseNavigationSOL(NavigationSOL* msg);

    NavigationStatus* parseNavigationStatus(UBXMessage* msg);
    NavigationStatus* parseNavigationStatus(NavigationStatus* msg);

    NavigationSpaceVehiculeInfo* parseNavigationSpaceVehiculeInfo(
      UBXMessage* msg
    );
    NavigationSpaceVehiculeInfo* parseNavigationSpaceVehiculeInfo(
      NavigationSpaceVehiculeInfo* msg
    );

    NavigationTimeGPS* parseNavigationTimeGPS(UBXMessage* msg);
    NavigationTimeGPS* parseNavigationTimeGPS(NavigationTimeGPS* msg);

    NavigationTimeUTC* parseNavigationTimeUTC(UBXMessage* msg);
    NavigationTimeUTC* parseNavigationTimeUTC(NavigationTimeUTC* msg);

    NavigationVelECEF* parseNavigationVelECEF(UBXMessage* msg);
    NavigationVelECEF* parseNavigationVelECEF(NavigationVelECEF* msg);

    NavigationVelNED* parseNavigationVelNED(UBXMessage* msg);
    NavigationVelNED* parseNavigationVelNED(NavigationVelNED* msg);

    ConfigurationAntenna* parseConfigurationAntenna(UBXMessage* msg);
    ConfigurationAntenna* parseConfigurationAntenna(
      ConfigurationAntenna* msg
    );

    ConfigurationDatum* parseConfigurationDatum(UBXMessage* msg);
    ConfigurationDatum* parseConfigurationDatum(ConfigurationDatum* msg);

    ConfigurationGNSS* parseConfigurationGNSS(UBXMessage* msg);
    ConfigurationGNSS* parseConfigurationGNSS(ConfigurationGNSS* msg);

    ConfigurationInformation* parseConfigurationInformation(
      UBXMessage* msg,
      uint16_t startIdx = 0
    );
    ConfigurationInformation* parseConfigurationInformation(
      ConfigurationInformation* msg,
      uint16_t startIdx = 0
    );

    ConfigurationInterferenceMonitor* parseConfigurationInterferenceMonitor(
      UBXMessage* msg
    );
    ConfigurationInterferenceMonitor* parseConfigurationInterferenceMonitor(
      ConfigurationInterferenceMonitor* msg
    );

    ConfigurationLogFilter* parseConfigurationLogFilter(UBXMessage* msg);
    ConfigurationLogFilter* parseConfigurationLogFilter(
      ConfigurationLogFilter* msg
    );

    ConfigurationMessaging* parseConfigurationMessaging(UBXMessage* msg);
    ConfigurationMessaging* parseConfigurationMessaging(
      ConfigurationMessaging* msg
    );

    ConfigurationNavigation* parseConfigurationNavigation(UBXMessage* msg);
    ConfigurationNavigation* parseConfigurationNavigation(
      ConfigurationNavigation* msg
    );

    ConfigurationNavigationExpert* parseConfigurationNavigationExpert(
      UBXMessage* msg
    );
    ConfigurationNavigationExpert* parseConfigurationNavigationExpert(
      ConfigurationNavigationExpert* msg
    );

    ConfigurationNMEA* parseConfigurationNMEA(UBXMessage* msg);
    ConfigurationNMEA* parseConfigurationNMEA(ConfigurationNMEA* msg);

    ConfigurationPort* parseConfigurationPort(
      UBXMessage* msg,
      uint16_t startIdx = 0
    );
    ConfigurationPort* parseConfigurationPort(
      ConfigurationPort* msg,
      uint16_t startIdx = 0
    );

    ConfigurationPower* parseConfigurationPower(UBXMessage* msg);
    ConfigurationPower* parseConfigurationPower(ConfigurationPower* msg);

    ConfigurationRate* parseConfigurationRate(UBXMessage* msg);
    ConfigurationRate* parseConfigurationRate(ConfigurationRate* msg);

    ConfigurationRemoteInventory* parseConfigurationRemoteInventory(
      UBXMessage* msg
    );
    ConfigurationRemoteInventory* parseConfigurationRemoteInventory(
      ConfigurationRemoteInventory* msg
    );

    ConfigurationReceiver* parseConfigurationReceiver(UBXMessage* msg);
    ConfigurationReceiver* parseConfigurationReceiver(
      ConfigurationReceiver* msg
    );

    ConfigurationSBAS* parseConfigurationSBAS(UBXMessage* msg);
    ConfigurationSBAS* parseConfigurationSBAS(ConfigurationSBAS* msg);

    ConfigurationTimePulse* parseConfigurationTimePulse(UBXMessage* msg);
    ConfigurationTimePulse* parseConfigurationTimePulse(
      ConfigurationTimePulse* msg
    );

    ConfigurationUSB* parseConfigurationUSB(UBXMessage* msg);
    ConfigurationUSB* parseConfigurationUSB(ConfigurationUSB* msg);

    InformationDebug* parseInformationDebug(UBXMessage* msg);
    InformationDebug* parseInformationDebug(InformationDebug* msg);

    InformationError* parseInformationError(UBXMessage* msg);
    InformationError* parseInformationError(InformationError* msg);

    InformationNotice* parseInformationNotice(UBXMessage* msg);
    InformationNotice* parseInformationNotice(InformationNotice* msg);

    InformationTest* parseInformationTest(UBXMessage* msg);
    InformationTest* parseInformationTest(InformationTest* msg);

    InformationWarning* parseInformationWarning(UBXMessage* msg);
    InformationWarning* parseInformationWarning(InformationWarning* msg);

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
