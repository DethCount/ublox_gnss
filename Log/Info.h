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

    bool isRecording() {
      return bool(status & 0x8);
    }

    bool isInactive() {
      return bool(status & 0x10);
    }

    bool isCircular() {
      return bool(status & 0x20);
    }

    virtual void print(Stream* stream) {
      stream->println(F("LogInfo"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Message version: "));
      stream->println(version);

      stream->print(F("Filestore capacity: "));
      stream->print(filestoreCapacity);
      stream->println(F("bytes"));

      stream->print(F("Current max log size: "));
      stream->print(currentMaxLogSize);
      stream->println(F("bytes"));

      stream->print(F("Current log size: "));
      stream->print(currentLogSize);
      stream->println(F("bytes"));

      stream->print(F("Number of entries: "));
      stream->println(entryCount);

      stream->print(F("Oldest entry UTC year: "));
      stream->println(oldestYear);

      stream->print(F("Oldest entry UTC month: "));
      stream->println(oldestMonth);

      stream->print(F("Oldest entry UTC day: "));
      stream->println(oldestDay);

      stream->print(F("Oldest entry UTC hour: "));
      stream->println(oldestHour);

      stream->print(F("Oldest entry UTC minute: "));
      stream->println(oldestMinute);

      stream->print(F("Oldest entry UTC second: "));
      stream->println(oldestSecond);

      stream->print(F("Newest entry UTC year: "));
      stream->println(newestYear);

      stream->print(F("Newest entry UTC month: "));
      stream->println(newestMonth);

      stream->print(F("Newest entry UTC day: "));
      stream->println(newestDay);

      stream->print(F("Newest entry UTC hour: "));
      stream->println(newestHour);

      stream->print(F("Newest entry UTC minute: "));
      stream->println(newestMinute);

      stream->print(F("Newest entry UTC second: "));
      stream->println(newestSecond);

      stream->print(F("Status: 0x"));
      stream->println(status, HEX);

      stream->print(F("Is recording ? : "));
      stream->println(isRecording());

      stream->print(F("Is inactive ? : "));
      stream->println(isInactive());

      stream->print(F("Is circular ? : "));
      stream->println(isCircular());

      stream->println();
    }
};
