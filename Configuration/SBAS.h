class ConfigurationSBAS : public UBXMessage {
  public:
    byte mode;
    byte usage;
    uint8_t maxSBAS;
    uint32_t scanmode1;
    byte scanmode2;

    ConfigurationSBAS() {
      msgId = MessageId::Configuration_SatelliteBasedAugmentationSystems;
    }

    ConfigurationSBAS(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationSBAS() {}
};
