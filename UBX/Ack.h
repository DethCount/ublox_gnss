class UBXAck : public UBXMessage {
  public:
    MessageId incomingMsgId;

    UBXAck() {
      isValid = false;
      msgId = MessageId::None;
      payloadLength = 0;
      incomingMsgId = MessageId::None;
    }

    UBXAck(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~UBXAck() {}
};
