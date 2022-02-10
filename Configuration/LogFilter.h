class ConfigurationLogFilter : public UBXMessage {
  public:
    uint8_t version;
    byte flags;
    uint16_t minInterval;
    uint16_t timeThreshold;
    uint16_t speedThreshold;
    uint32_t positionThreshold;

    ConfigurationLogFilter() {
      msgId = MessageId::Configuration_LogFilter;
    }

    ConfigurationLogFilter(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationLogFilter() {}

    bool isRecordingEnabled() {
      return bool(flags & 0x1);
    }

    bool isSinglePositionPerWakeUpEnabled() {
      return bool(flags & 0x2);
    }

    bool applyAllFilterSettings() {
      return bool(flags & 0x4);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationLogFilter"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("version: "));
      stream->println(version);

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is recording enabled: "));
      stream->println(isRecordingEnabled());

      stream->print(F("Record a single position on each Power Save Mode wake up period ? : "));
      stream->println(isSinglePositionPerWakeUpEnabled());

      stream->print(F("Update all settings ? : "));
      stream->println(applyAllFilterSettings());

      stream->print(F("minInterval: "));
      stream->print(minInterval);
      stream->println(F("s"));

      stream->print(F("timeThreshold: "));
      stream->print(timeThreshold);
      stream->println(F("s"));

      stream->print(F("speedThreshold: "));
      stream->print(speedThreshold);
      stream->println(F("m/s"));

      stream->print(F("positionThreshold: "));
      stream->print(speedThreshold);
      stream->println(F("m"));

      stream->println();
    }
};
