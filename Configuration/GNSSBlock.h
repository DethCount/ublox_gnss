class ConfigurationGNSSBlock {
  public:
    uint8_t gnssId;
    uint8_t resTrkCh;
    uint8_t maxTrkCh;
    uint32_t flags;

    ConfigurationGNSSBlock() {}

    virtual ~ConfigurationGNSSBlock() {}
};
