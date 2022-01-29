class ConfigurationGNSS : public UBXMessage {
  public:
    static const uint8_t MAX_NB_BLOCKS = 0xFF;

    uint8_t msgVer;
    uint8_t numTrkChHw;
    uint8_t numTrkChUse;
    uint8_t numConfigBlocks;
    ConfigurationGNSSBlock* blocks[MAX_NB_BLOCKS];

    ConfigurationGNSS() {
      msgId = MessageId::Configuration_GlobalNavigationSatelliteSystem;
    }

    ConfigurationGNSS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationGNSS() {}
};
