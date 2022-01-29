class UBXAck : public UBXMessage {
  public:
    MessageId incomingMsgId;

    UBXAck() {
      isValid = false;
      msgId = MessageId::None;
      incomingMsgId = MessageId::None;
    }

    UBXAck(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~UBXAck() {}
};
