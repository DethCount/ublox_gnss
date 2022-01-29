class LogInfo : public UBXMessage {
  public:
    uint8_t version;
    uint32_t filestoreCapacity;
    uint32_t currentMaxLogSize;
    uint32_t currentLogSize;
    uint32_t entryCount;
    uint16_t oldestYear;
    uint8_t oldestMonth;
    uint8_t oldestDay;
    uint8_t oldestHour;
    uint8_t oldestMinute;
    uint8_t oldestSecond;
    uint16_t newestYear;
    uint8_t newestMonth;
    uint8_t newestDay;
    uint8_t newestHour;
    uint8_t newestMinute;
    uint8_t newestSecond;
    byte status;

    LogInfo() {
      msgId = MessageId::Log_Info;
    }

    LogInfo(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~LogInfo() {}
};
