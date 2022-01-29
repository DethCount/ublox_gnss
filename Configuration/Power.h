class ConfigurationPower : public UBXMessage {
  public:
    uint8_t version;
    uint32_t flags;
    uint32_t updatePeriod;
    uint32_t searchPeriod;
    uint32_t gridOffset;
    uint16_t onTime;
    uint16_t minAcqTime;

    ConfigurationPower() {
      msgId = MessageId::Configuration_Power;
    }

    ConfigurationPower(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationPower() {}
};
