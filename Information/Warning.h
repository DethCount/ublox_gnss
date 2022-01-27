class InformationWarning : public UBXMessage {
  public:
    InformationWarning() {
      msgId = MessageId::Information_Warning;
    }

    InformationWarning(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~InformationWarning() {}
};
