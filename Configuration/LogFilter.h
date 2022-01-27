class ConfigurationLogFilter : public UBXMessage {
  public:
    uint8_t version;
    byte flags;
    uint16_t minInterval;
    uint16_t timeThreshold;
    uint16_t speedThreshold;
    uint32_t positionThreshold;

    ConfigurationLogFilter() {
      msgId = MessageId::Configuration_LogFilter;
    }

    ConfigurationLogFilter(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationLogFilter() {}
};
