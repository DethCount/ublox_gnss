class GNSSConfiguration {
  private:
    UBXClient *client;

  public:
    GNSSConfiguration(UBXClient *c);

    ConfigurationAntenna* getAntenna();

    void reset(uint16_t navBbrMask, ConfigurationResetMode resetMode);

    void execCommand(
      uint32_t clearMask,
      uint32_t saveMask,
      uint32_t loadMask
    );

    void execCommand(
      uint32_t clearMask,
      uint32_t saveMask,
      uint32_t loadMask,
      byte deviceMask
    );

    ConfigurationDatum* getDatum();

    ConfigurationGNSS* getGNSS();

    ConfigurationInformation* getInformation();
    ConfigurationInformation* getInformation(GNSSProtocol protocolId);

    ConfigurationInterferenceMonitor* getInterferenceMonitor();

    ConfigurationLogFilter* getLogFilter();

    ConfigurationMessaging* getMsgRate(MessageId msgId);
    UBXRequestStatus enableMessage(
      uint16_t msgId,
      bool changePort = false,
      byte port1 = 0x00,
      byte port2 = 0x00,
      byte port3 = 0x00,
      byte port4 = 0x00,
      byte port5 = 0x00,
      byte port6 = 0x00
    );

    ConfigurationNavigation* getNavigation();

    ConfigurationNavigationExpert* getNavigationExpert();

    ConfigurationNMEA* getNMEA();

    ConfigurationPort* getPort();
    ConfigurationPort* getPort(PortId portId);
    UBXRequestStatus setPortRate(PortRate portRate);

    ConfigurationPower* getPower();

    ConfigurationRate* getRate();
    UBXRequestStatus setRate(
      DataRate dataRate,
      GNSSReferenceTime timeRef = GNSSReferenceTime::GPS
    );

    ConfigurationRemoteInventory* getRemoteInventory();

    ConfigurationReceiver* getReceiver();

    ConfigurationSBAS* getSBAS();

    ConfigurationTimePulse* getTimePulse();
    ConfigurationTimePulse* getTimePulse(uint8_t tpIdx);

    ConfigurationUSB* getUSB();

    void GNSSConfiguration::print(Stream* stream);
    void GNSSConfiguration::printAntenna(Stream* stream);
    void GNSSConfiguration::printDatum(Stream* stream);
    void GNSSConfiguration::printGNSS(Stream* stream);
    void GNSSConfiguration::printInformation(
      Stream* stream,
      GNSSProtocol protocolId
    );
    void GNSSConfiguration::printInterferenceMonitor(Stream* stream);
    void GNSSConfiguration::printLogFilter(Stream* stream);
    void GNSSConfiguration::printMsgRate(Stream* stream, MessageId msgId);
    void GNSSConfiguration::printNavigation(Stream* stream);
    void GNSSConfiguration::printNavigationExpert(Stream* stream);
    void GNSSConfiguration::printNMEA(Stream* stream);
    void GNSSConfiguration::printPort(Stream* stream);
    void GNSSConfiguration::printPort(Stream* stream, PortId portId);
    void GNSSConfiguration::printPower(Stream* stream);
    void GNSSConfiguration::printRate(Stream* stream);
    void GNSSConfiguration::printReceiver(Stream* stream);
    void GNSSConfiguration::printRemoteInventory(Stream* stream);
    void GNSSConfiguration::printSBAS(Stream* stream);
    void GNSSConfiguration::printTimePulse(Stream* stream);
    void GNSSConfiguration::printTimePulse(Stream* stream, uint8_t tpIdx);
    void GNSSConfiguration::printUSB(Stream* stream);
};
