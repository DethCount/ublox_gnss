class AidingAOP : public UBXMessage {
  public:
    static const uint16_t MAX_DATA_SIZE = 203;

  	uint8_t svid;
  	uint8_t dataSize;
    uint8_t data[MAX_DATA_SIZE];

    AidingAOP() {
      msgId = MessageId::Aiding_AOP;
    }

    AidingAOP(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~AidingAOP() {}
};
