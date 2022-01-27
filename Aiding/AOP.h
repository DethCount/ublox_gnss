class AidingAOP : public UBXMessage {
  public:
    static const uint16_t MAX_DATA_SIZE = 203;

  	uint8_t svid;
  	uint8_t dataSize;
    uint8_t dataPayloadOffsetStart;

    AidingAOP() {}

    AidingAOP(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~AidingAOP() {}
};
