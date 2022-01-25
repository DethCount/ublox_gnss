class ConfigurationReceiver : public UBXMessage {
  public:
    LowPowerMode lpMode;

    ConfigurationReceiver() {
      msgId = MessageId::Configuration_Receiver;
    }

    ConfigurationReceiver(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationReceiver() {}
};
