class ConfigurationMessaging : public UBXMessage
{
  public:
    MessageClass msgClass;
    MessageId msgId;
    uint8_t rate;

    ConfigurationMessaging() {}

    ConfigurationMessaging(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationMessaging() {}
};
