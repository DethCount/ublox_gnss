class GNSSConfiguration {
  private:
    UBXClient *client;

  public:
    GNSSConfiguration(UBXClient *c);

    ConfigurationAntenna* getAntenna();

    void sendCommand(
      uint32_t clearMask,
      uint32_t saveMask,
      uint32_t loadMask
    );

    void sendCommand(
      uint32_t clearMask,
      uint32_t saveMask,
      uint32_t loadMask,
      byte deviceMask
    );

    ConfigurationDatum* getDatum();

    ConfigurationRate* getRate();

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

    UBXRequestStatus setPortRate(PortRate portRate);

    UBXRequestStatus setDataRate(DataRate dataRate);
};
