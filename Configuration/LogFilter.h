class ConfigurationLogFilter : public UBXMessage
{
  public:
    uint8_t version;
    byte flags;
    uint16_t minInterval;
    uint16_t timeThreshold;
    uint16_t speedThreshold;
    uint32_t positionThreshold;

    ConfigurationLogFilter() {}

    ConfigurationLogFilter(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationLogFilter() {}
};