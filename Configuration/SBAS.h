class ConfigurationSBAS : public UBXMessage {
  public:
    byte mode;
    byte usage;
    uint8_t maxSBAS;
    uint32_t scanmode1;
    byte scanmode2;

    ConfigurationSBAS() {
      msgId = MessageId::Configuration_SatelliteBasedAugmentationSystems;
    }

    ConfigurationSBAS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationSBAS() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationSBAS"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("mode: "));
      stream->println(mode, HEX);

      stream->print(F("usage: "));
      stream->println(usage, HEX);

      stream->print(F("maxSBAS: "));
      stream->println(maxSBAS);

      stream->print(F("scanmode1: "));
      stream->println(scanmode1);

      stream->print(F("scanmode2: "));
      stream->println(scanmode2);

      stream->println();
    }
};
