class NavigationSBASItem {
  public:
    uint8_t svid;
    byte flags;
    byte udre;
    SBASSystem svSys;
    byte svService;
    // reserved1 U1
    int16_t prc;
    // reserved2 U2
    int16_t ic;

    NavigationSBASItem() {}

    virtual ~NavigationSBASItem() {}

    bool hasRangingService() {
      return bool(svService & 0x1);
    }

    bool hasCorrectionsService() {
      return bool(svService & 0x2);
    }

    bool hasIntegrityService() {
      return bool(svService & 0x4);
    }

    bool hasTestmodeService() {
      return bool(svService & 0x8);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationSBASItem"));

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Monitoring status: 0x"));
      stream->println(udre, HEX);

      stream->print(F("SBAS system: 0x"));
      stream->println(uint8_t(svSys), HEX);

      stream->print(F("Service: 0x"));
      stream->println(svService, HEX);

      stream->print(F("Ranging service: "));
      stream->println(hasRangingService());

      stream->print(F("Corrections service: "));
      stream->println(hasCorrectionsService());

      stream->print(F("Integrity service: "));
      stream->println(hasIntegrityService());

      stream->print(F("Testmode service: "));
      stream->println(hasTestmodeService());

      stream->print(F("Pseudorange correction: "));
      stream->print(prc);
      stream->println(F("cm"));

      stream->print(F("Ionosphere correction: "));
      stream->print(ic);
      stream->println(F("cm"));

      stream->println();
    }
};
