class NavigationSpaceVehicule {
  public:
    uint8_t chn;
    uint8_t svid;
    byte flags;
    byte quality;
    uint8_t cno;
    int8_t elev;
    int16_t azim;
    int32_t prRes;

    NavigationSpaceVehicule() {}

    virtual ~NavigationSpaceVehicule() {}

    bool isSVUsedForNavigation() {
      return bool(flags & 0x1);
    }

    bool isDifferentialCorrectionAvailable() {
      return bool(flags & 0x2);
    }

    bool isOrbitDataAvailable() {
      return bool(flags & 0x4);
    }

    bool isEphemerisAvailable() {
      return bool(flags & 0x8);
    }

    bool isUnhealthy() {
      return bool(flags & 0x10);
    }

    bool isAlmanachPlusAvailable() {
      return bool(flags & 0x20);
    }

    bool isAOPAvailable() {
      return bool(flags & 0x40);
    }

    bool isSmoothedPseudorange() {
      return bool(flags & 0x40);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationSpaceVehicule"));

      stream->print(
        F("Channel number (255 for a SV not assigned to a channel): ")
      );
      stream->println(chn);

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Flags: "));
      stream->println(flags, HEX);

      stream->print(F("Is SV used for navigation ? : "));
      stream->println(isSVUsedForNavigation());

      stream->print(F("Is differential correction available ? : "));
      stream->println(isDifferentialCorrectionAvailable());

      stream->print(F("Is orbit data available ? : "));
      stream->println(isOrbitDataAvailable());

      stream->print(F("Is ephemeris available ? : "));
      stream->println(isEphemerisAvailable());

      stream->print(F("Is unhealthy ? : "));
      stream->println(isUnhealthy());

      stream->print(F("Is almanach plus available ? : "));
      stream->println(isAlmanachPlusAvailable());

      stream->print(F("Is AOP available ? : "));
      stream->println(isAOPAvailable());

      stream->print(F("Is carrier smoothed pseudorange used ? : "));
      stream->println(isSmoothedPseudorange());

      stream->print(F("Quality: "));
      stream->println(quality, HEX);

      stream->print(F("Carrier noise ratio (signal strength): "));
      stream->print(cno);
      stream->println(F("dbHz"));

      stream->print(F("Elevation: "));
      stream->print(elev);
      stream->println(F("°"));

      stream->print(F("Azimuth: "));
      stream->print(azim);
      stream->println(F("°"));

      stream->print(F("Pseudorange residual: "));
      stream->println(prRes);
      stream->println(F("cm"));

      stream->println();
    }
};
