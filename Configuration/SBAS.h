#ifndef SBAS_SCANMODE_MIN_PRN
  #define SBAS_SCANMODE_MIN_PRN 120
#endif

#ifndef SBAS_SCANMODE2_MIN_PRN
  #define SBAS_SCANMODE2_MIN_PRN 152
#endif

#ifndef SBAS_SCANMODE_MAX_PRN
  #define SBAS_SCANMODE_MAX_PRN 159
#endif

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

    bool isSBASEnabled() {
      return bool(mode & 0x1);
    }

    bool isSBASTestModeEnabled() {
      return bool(mode & 0x2);
    }

    bool useGEORangingSource() {
      return bool(usage & 0x1);
    }

    bool useDifferentialCorrections() {
      return bool(usage & 0x2);
    }

    bool useIntegrityInformation() {
      return bool(usage & 0x4);
    }

    bool scanModePRN(uint8_t prn) {
      if (prn < SBAS_SCANMODE_MIN_PRN
        || prn >= SBAS_SCANMODE_MAX_PRN
      ) {
        return false;
      }

      if (prn < SBAS_SCANMODE2_MIN_PRN) {
        return bool(scanmode1 & (0x1 << (prn - SBAS_SCANMODE_MIN_PRN)));
      }

      return bool(scanmode2 & (0x1 << (prn - SBAS_SCANMODE2_MIN_PRN)));
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationSBAS"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("mode: 0x"));
      stream->println(mode, HEX);

      stream->print(F("Is SBAS enabled ? : "));
      stream->println(isSBASEnabled());

      stream->print(F("Is SBAS test mode enabled ? : "));
      stream->println(isSBASTestModeEnabled());

      stream->print(F("usage: 0x"));
      stream->println(usage, HEX);

      stream->print(F("Use GEO ranging source ? : "));
      stream->println(useGEORangingSource());

      stream->print(F("Use differential corrections ? : "));
      stream->println(useDifferentialCorrections());

      stream->print(F("Use integrity information ? : "));
      stream->println(useIntegrityInformation());

      stream->print(F("maxSBAS: "));
      stream->println(maxSBAS);

      stream->print(F("scanmode1: 0x"));
      stream->println(scanmode1);

      stream->print(F("scanmode2: 0x"));
      stream->println(scanmode2);

      for (uint8_t i = SBAS_SCANMODE_MIN_PRN; i < SBAS_SCANMODE_MAX_PRN; i++) {
        stream->print("Scan for PRN ");
        stream->print(i);
        stream->print(" ? : ");
        stream->println(scanModePRN(i));
      }

      stream->println();
    }
};
