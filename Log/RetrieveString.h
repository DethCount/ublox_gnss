class LogRetrieveString : public UBXMessage {
  public:
    uint32_t entryIndex;
    uint8_t version;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t byteCount;
    uint16_t bytes[UBXPacket::PAYLOAD_SIZE];

    LogRetrieveString() {
      msgId = MessageId::Log_RetrieveString;
    }

    LogRetrieveString(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~LogRetrieveString() {}
};
