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

    virtual void print(Stream* stream) {
      stream->println(F("LogFindTime"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Message version: "));
      stream->println(version);

      stream->print(F("Message type: "));
      stream->println(type);

      stream->print(F("Entry number: "));
      stream->println(entryNumber);

      stream->println();
    }
};
