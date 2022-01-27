class ConfigurationTimePulse : public UBXMessage {
  public:
    uint8_t tpIdx;
    int16_t antCableDelay;
    int16_t rfGroupDelay;
    uint32_t freqPeriod;
    uint32_t freqPeriodLock;
    uint32_t pulseLenRatio;
    uint32_t pulseLenRatioLock;
    int32_t userConfigDelay;
    uint32_t flags;

    ConfigurationTimePulse() {
      msgId = MessageId::Configuration_TimePulse;
    }

    ConfigurationTimePulse(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationTimePulse() {}
};
