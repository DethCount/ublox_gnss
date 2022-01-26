class LogRetrievePosition : public UBXMessage {
  public:
    uint32_t entryIndex;
    double lon;
    double lat;
    int32_t hMSL;
    uint32_t hAcc;
    uint32_t gSpeed;
    uint32_t heading;
    uint8_t version;
    GNSSFixType fixType;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t numSV;

    LogRetrievePosition() {
      msgId = MessageId::Log_RetrievePosition;
    }

    LogRetrievePosition(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~LogRetrievePosition() {}
};
