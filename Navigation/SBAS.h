class NavigationSBAS : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t geo;
    SBASMode mode;
    SBASSystem sys;
    byte service;
    uint8_t cnt;
    // reserved0 U1[3]
    NavigationSBASItem* items[GNSS_MAX_SVID];

    NavigationSBAS() {
      msgId = MessageId::Navigation_SBAS;
    }

    NavigationSBAS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationSBAS() {}

    bool hasRangingService() {
      return bool(service & 0x1);
    }

    bool hasCorrectionsService() {
      return bool(service & 0x2);
    }

    bool hasIntegrityService() {
      return bool(service & 0x4);
    }

    bool hasTestmodeService() {
      return bool(service & 0x8);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationSBAS"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(
        F("PRN Number of the GEO where correction and integrity data is used from: ")
      );
      stream->println(geo);

      stream->print(F("SBAS mode: "));
      stream->println(uint8_t(mode));

      stream->print(F("SBAS system: "));
      stream->println(uint8_t(sys));

      stream->print(F("Service: "));
      stream->println(service, HEX);

      stream->print(F("Ranging service: "));
      stream->println(hasRangingService());

      stream->print(F("Corrections service: "));
      stream->println(hasCorrectionsService());

      stream->print(F("Integrity service: "));
      stream->println(hasIntegrityService());

      stream->print(F("Testmode service: "));
      stream->println(hasTestmodeService());

      stream->print(F("Number of space vehicules data: "));
      stream->println(cnt);

      for (uint8_t i = 0; i < cnt; i++) {
        stream->print(F("items["));
        stream->print(i);
        stream->println(F("]: "));
        items[i]->print(stream);
      }

      stream->println();
    }
};
