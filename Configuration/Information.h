class ConfigurationInformation : public UBXMessage
{
  public:
    static const uint8_t MAX_NB_MSG_CLASS = 6;
    GNSSProtocol protocolId;
    byte infMsgMask[MAX_NB_MSG_CLASS];
    ConfigurationInformation* next;

    ConfigurationInformation() {}

    ConfigurationInformation(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationInformation() {}
};
