class ConfigurationPower : public UBXMessage {
  public:
    uint8_t version;
    uint32_t flags;
    uint32_t updatePeriod;
    uint32_t searchPeriod;
    uint32_t gridOffset;
    uint16_t onTime;
    uint16_t minAcqTime;

    ConfigurationPower() {
      msgId = MessageId::Configuration_Power;
    }

    ConfigurationPower(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationPower() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationPower"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("version: "));
      stream->println(version);

      stream->print(F("flags: "));
      stream->println(flags, HEX);

      stream->print(F("updatePeriod: "));
      stream->print(updatePeriod);
      stream->println(F("ms"));

      stream->print(F("searchPeriod: "));
      stream->print(searchPeriod);
      stream->println(F("ms"));

      stream->print(F("gridOffset: "));
      stream->print(gridOffset);
      stream->println(F("ms"));

      stream->print(F("onTime: "));
      stream->print(onTime);
      stream->println(F("s"));

      stream->print(F("minAcqTime: "));
      stream->print(minAcqTime);
      stream->println(F("s"));

      stream->println();
    }
};
