class ConfigurationRate : public UBXMessage {
  public:
    DataRate measRate;
    uint16_t navRate;
    GNSSReferenceTime timeRef;

    ConfigurationRate() {
      msgId = MessageId::Configuration_Rate;
    }

    ConfigurationRate(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationRate() {}
};
