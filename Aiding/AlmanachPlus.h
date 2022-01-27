class AidingAlmanachPlus : public UBXMessage {
  public:
    static const uint16_t MAX_DATA_SIZE = 0x0FFF;

  	uint8_t idSize;
    uint8_t type;
    uint16_t ofs;
    uint16_t size;
    uint16_t fileId;
    uint16_t dataSize;
    uint8_t id1;
    uint8_t id2;
    uint16_t id3;
    uint16_t dataPayloadOffsetStart;

    AidingAlmanachPlus() {}

    AidingAlmanachPlus(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~AidingAlmanachPlus() {}
};
