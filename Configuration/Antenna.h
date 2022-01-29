class ConfigurationAntenna : public UBXMessage {
  public:
    uint16_t flags;
    uint16_t pins;

    ConfigurationAntenna() {
      msgId = MessageId::Configuration_Antenna;
    }

    ConfigurationAntenna(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationAntenna() {}
};
