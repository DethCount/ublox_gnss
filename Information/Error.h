class InformationError : public UBXMessage {
  public:
    InformationError() {
      msgId = MessageId::Information_Error;
    }

    InformationError(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~InformationError() {}
};
