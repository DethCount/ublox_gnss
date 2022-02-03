class ConfigurationRate : public UBXMessage {
  public:
    DataRate measRate;
    uint16_t navRate;
    GNSSReferenceTime timeRef;

    ConfigurationRate() {
      msgId = MessageId::Configuration_Rate;
    }

    ConfigurationRate(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationRate() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationRate"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("measRate: "));
      stream->print(uint16_t(measRate));
      stream->println(F("ms"));

      stream->print(F("navRate: "));
      stream->print(navRate);
      stream->println(F("cycles"));

      stream->print(F("timeRef: "));
      stream->println(uint16_t(timeRef));

      stream->println();
    }
};
