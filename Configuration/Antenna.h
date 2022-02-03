class ConfigurationAntenna : public UBXMessage {
  public:
    uint16_t flags;
    uint16_t pins;

    ConfigurationAntenna() {
      msgId = MessageId::Configuration_Antenna;
    }

    ConfigurationAntenna(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationAntenna() {}

    virtual void print(Stream *stream) {
      stream->println(F("ConfigurationAntenna"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("flags: "));
      stream->println(flags, BIN);

      stream->print(F("pins: "));
      stream->println(pins, BIN);

      stream->println();
    }
};
