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

    uint8_t getMsgRate(MessageId msgId);
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
};
