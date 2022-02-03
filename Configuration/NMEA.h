class ConfigurationNMEA : public UBXMessage {
  public:
    byte filter;
    uint8_t nmeaVersion;
    uint8_t numSV;
    byte flags;
    uint32_t gnssToFilter;
    uint8_t svNumbering;
    uint8_t mainTalkerId;
    uint8_t gsvTalkerId;

    ConfigurationNMEA() {
      msgId = MessageId::Configuration_NationalMarineElectronicsAssociation;
    }

    ConfigurationNMEA(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationNMEA() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationNMEA"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("filter: "));
      stream->println(filter, HEX);

      stream->print(F("nmeaVersion: "));
      stream->println(nmeaVersion);

      stream->print(F("numSV: "));
      stream->println(numSV);

      stream->print(F("flags: "));
      stream->println(flags, HEX);

      stream->print(F("gnssToFilter: "));
      stream->println(gnssToFilter, HEX);

      stream->print(F("svNumbering: "));
      stream->println(svNumbering);

      stream->print(F("mainTalkerId: "));
      stream->println(mainTalkerId);

      stream->print(F("gsvTalkerId: "));
      stream->println(gsvTalkerId);

      stream->println();
    }
};
