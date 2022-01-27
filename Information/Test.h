class InformationTest : public UBXMessage {
  public:
    InformationTest() {
      msgId = MessageId::Information_Test;
    }

    InformationTest(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~InformationTest() {}
};
