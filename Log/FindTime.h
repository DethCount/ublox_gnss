class LogFindTime : public UBXMessage {
  public:
    uint8_t version;
    uint8_t type;
    uint32_t entryNumber;

    LogFindTime() {
      msgId = MessageId::Log_FindTime;
    }

    LogFindTime(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~LogFindTime() {}
};
