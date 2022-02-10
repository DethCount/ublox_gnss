class ReceiverManagerSpaceVehicule : public UBXMessage {
  public:
    uint8_t svid;
    byte svFlag;
    int16_t azim;
    int8_t elev;
    byte age;

    ReceiverManagerSpaceVehicule() {}

    virtual ~ReceiverManagerSpaceVehicule() {}

    uint8_t getURAIndex() {
      return svFlag & 0xF;
    }

    bool isHealthy() {
      return svFlag & 0x10;
    }

    bool isEphemerisValid() {
      return svFlag & 0x20;
    }

    bool isAlmanachValid() {
      return svFlag & 0x40;
    }

    bool isAvailable() {
      return !bool(svFlag & 0x80);
    }

    uint8_t getAlmanachAge() {
      return age & 0xF;
    }

    uint8_t getEphemerisAge() {
      return (age >> 4) & 0xF;
    }

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerSpaceVehicule"));

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Flags: 0x"));
      stream->println(svFlag, HEX);

      stream->print(F("URA Index: "));
      stream->println(getURAIndex());

      stream->print(F("Is healthy ? : "));
      stream->println(isHealthy());

      stream->print(F("Is ephemeris valid ? : "));
      stream->println(isEphemerisValid());

      stream->print(F("Is almanach valid ? : "));
      stream->println(isAlmanachValid());

      stream->print(F("Is available ? : "));
      stream->println(isAvailable());

      stream->print(F("Azimuth: "));
      stream->print(azim);
      stream->println(F("°"));

      stream->print(F("Elevation: "));
      stream->print(elev);
      stream->println(F("°"));

      stream->print(F("Age: 0x"));
      stream->print(age, HEX);

      stream->print(F("Age of almanach offset by 4: "));
      stream->print(getAlmanachAge());
      stream->println(F("days"));

      stream->print(F("Age of ephemeris offset by 4: "));
      stream->print(getEphemerisAge());
      stream->println(F("days"));

      stream->println();
    }
};
