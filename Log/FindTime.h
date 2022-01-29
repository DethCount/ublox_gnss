class LogFindTime : public UBXMessage {
  public:
    uint8_t version;
    uint8_t type;
    uint32_t entryNumber;

    LogFindTime() {
      msgId = MessageId::Log_FindTime;
    }

    LogFindTime(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~LogFindTime() {}
};
