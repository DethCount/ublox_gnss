class ConfigurationAntenna : public UBXMessage {
  public:
    uint16_t flags;
    uint16_t pins;

    ConfigurationAntenna() {
      msgId = MessageId::Configuration_Antenna;
    }

    ConfigurationAntenna(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationAntenna() {}
};
