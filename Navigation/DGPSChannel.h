class NavigationDGPSChannel {
  public:
    uint8_t svid;
    byte flags;
    uint16_t ageC;
    uint32_t prc;
    uint32_t prrc;

    NavigationDGPSChannel() {}

    virtual ~NavigationDGPSChannel() {}

    uint8_t getChannel() {
      return flags & 0xF;
    }

    bool isUsed() {
      return bool(flags & 0x10);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationDGPSChannel"));

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Channel number: "));
      stream->println(getChannel());

      stream->print(F("Is DGPS channel used ? : "));
      stream->println(isUsed());

      stream->print(F("Age of latest correction data: "));
      stream->print(ageC);
      stream->println(F("ms"));

      stream->print(F("Pseudorange correction: "));
      stream->print(prc);
      stream->println(F("m"));

      stream->print(F("Pseudorange rate correction: "));
      stream->print(prrc);
      stream->println(F("m/s"));

      stream->println();
    }
};
