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

    virtual void print(Stream* stream) {
      stream->println(F("AidingAOP"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("dataSize: "));
      stream->println(dataSize);

      for (uint8_t i = 0; i < dataSize; i++) {
        stream->print(F("data["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(data[i]);
      }

      stream->println();
    }
};
