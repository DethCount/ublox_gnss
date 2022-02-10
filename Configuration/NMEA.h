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

    bool isFailedOrInvalidFixesPositionOutputEnabled() {
      return bool(filter & 0x1);
    }

    bool isInvalidFixesPositionOutputEnabled() {
      return bool(filter & 0x2);
    }

    bool isInvalidTimesTimeOutputEnabled() {
      return bool(filter & 0x4);
    }

    bool isInvalidTimesDateOutputEnabled() {
      return bool(filter & 0x8);
    }

    bool isGPSOnlyFilterEnabled() {
      return bool(filter & 0x10);
    }

    bool isCourseOverGroundFilterEnabled() {
      return bool(filter & 0x20);
    }

    bool isCompatibilityModeEnabled() {
      return bool(flags & 0x1);
    }

    bool isConsideringModeEnabled() {
      return bool(flags & 0x2);
    }

    bool isGPSReportingDisabled() {
      return bool(gnssToFilter & 0x1);
    }

    bool isSBASReportingDisabled() {
      return bool(gnssToFilter & 0x2);
    }

    bool isQZSSReportingDisabled() {
      return bool(gnssToFilter & 0x10);
    }

    bool isGLONASSReportingDisabled() {
      return bool(gnssToFilter & 0x20);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationNMEA"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("filter: 0x"));
      stream->println(filter, HEX);

      stream->print(F("Is position output for failed or invalid fixes enabled ? : "));
      stream->println(isFailedOrInvalidFixesPositionOutputEnabled());

      stream->print(F("Is position output for invalid fixes enabled ? : "));
      stream->println(isInvalidFixesPositionOutputEnabled());

      stream->print(F("Is time output for invalid times enabled ? : "));
      stream->println(isInvalidTimesTimeOutputEnabled());

      stream->print(F("Is date output for invalid times enabled ? : "));
      stream->println(isInvalidTimesDateOutputEnabled());

      stream->print(F("Restrict output to GPS satellites only ? : "));
      stream->println(isGPSOnlyFilterEnabled());

      stream->print(F("Enable Course Over Ground output even while frozen ? : "));
      stream->println(isCourseOverGroundFilterEnabled());

      stream->print(F("nmeaVersion: "));
      stream->println(nmeaVersion);

      stream->print(F("numSV: "));
      stream->println(numSV);

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is compatibility mode enabled ? : "));
      stream->println(isCompatibilityModeEnabled());

      stream->print(F("Is considering mode enabled ? : "));
      stream->println(isConsideringModeEnabled());

      stream->print(F("gnssToFilter: 0x"));
      stream->println(gnssToFilter, HEX);

      stream->print(F("Is GPS reporting disabled ? : "));
      stream->println(isGPSReportingDisabled());

      stream->print(F("Is SBAS reporting disabled ? : "));
      stream->println(isSBASReportingDisabled());

      stream->print(F("Is QZSS reporting disabled ? : "));
      stream->println(isQZSSReportingDisabled());

      stream->print(F("Is GLONASS reporting disabled ? : "));
      stream->println(isGLONASSReportingDisabled());

      stream->print(F("svNumbering: "));
      stream->println(svNumbering);

      stream->print(F("mainTalkerId: "));
      stream->println(mainTalkerId);

      stream->print(F("gsvTalkerId: "));
      stream->println(gsvTalkerId);

      stream->println();
    }
};
