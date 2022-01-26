class InformationDebug : public UBXMessage {
  public:
    InformationDebug() {
      msgId = MessageId::Information_Debug;
    }

    InformationDebug(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~InformationDebug() {}
};
