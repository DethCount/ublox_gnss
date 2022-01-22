class ConfigurationRate : public UBXMessage {
  public:
    uint16_t measRate;
    uint16_t navRate;
    uint16_t timeRef;

    ConfigurationRate(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    ConfigurationRate() {
      isValid = false;
      msgId = MessageId::Configuration_Rate;
      payloadLength = 0;
    }

    virtual ~ConfigurationRate() {}
};
