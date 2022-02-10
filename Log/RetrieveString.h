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
    uint16_t bytes[UBX_PAYLOAD_SIZE];

    LogRetrieveString() {
      msgId = MessageId::Log_RetrieveString;
    }

    LogRetrieveString(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~LogRetrieveString() {}

    virtual void print(Stream* stream) {
      stream->println(F("LogRetrieveString"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Entry index: "));
      stream->println(entryIndex);

      stream->print(F("Message version: "));
      stream->println(version);

      stream->print(F("UTC year: "));
      stream->println(year);

      stream->print(F("UTC month: "));
      stream->println(month);

      stream->print(F("UTC day: "));
      stream->println(day);

      stream->print(F("UTC hour: "));
      stream->println(hour);

      stream->print(F("UTC minute: "));
      stream->println(minute);

      stream->print(F("UTC second: "));
      stream->println(second);

      stream->print(F("Number of entry bytes: "));
      stream->println(byteCount);

      for (uint16_t i = 0; i < byteCount; i++) {
        stream->print(F("bytes["));
        stream->print(i);
        stream->print(F("]: 0x"));
        stream->println(bytes[i], HEX);
      }

      stream->println();
    }
};
