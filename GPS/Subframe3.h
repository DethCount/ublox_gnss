class GPSSubframe3 : public GPSSubframe  {
  public:
    GPSSubframe3(bool raw = false) : GPSSubframe(raw) {}

    uint16_t getInclinationCorrectionCosine() { // C(iC)
      return (uint16_t)(words[raw ? 2 : 0] >> 8);
    }

    uint16_t getInclinationCorrectionSine() { // C(iS)
      return (uint16_t)(words[raw ? 4 : 2] >> 8);
    }

    uint16_t getOrbitRadiusCorrectionCosine() { // C(rC)
      return (uint16_t)(words[raw ? 6 : 4] >> 8);
    }

    // OMEGA(0)
    uint32_t getLongitudeOfAscendingNodeOfOrbitPlaneAtWeeklyEpoch() {
      return ((words[raw ? 2 : 0] & 0xFF) << 24)
        | (words[raw ? 3 : 1] & 0xFFFFFF);
    }

    uint32_t getArgumentOfPerigee() { // omega
      return ((words[raw ? 7 : 5] & 0xFF) << 24)
        | (words[raw ? 8 : 6] & 0xFFFFFF);
    }

    uint32_t getRateOfRightAscension() { // OMEGA DOT
      return words[raw ? 7 : 5] & 0xFFFFFF;
    }

    uint32_t getInclinationAngleAtReferenceTime() { // i(0)
      return ((words[raw ? 4 : 2] & 0xFF) << 24)
        | (words[raw ? 5 : 3] & 0xFFFFFF);
    }

    uint16_t getRateOfInclinationAngle() { // IDOT
      return (uint16_t)(words[raw ? 9 : 7] >> 2) & 0x3FFF;
    }

    uint8_t getIssueOfDataEphemeris() { // IODE
      return (uint8_t)(words[raw ? 9 : 7] >> 16);
    }

    virtual void print(Stream* stream) {
      GPSSubframe::print(stream, "GPSSubframe3");

      stream->print(F("Inclinaition correction cosine (C(iC)): "));
      stream->println(getInclinationCorrectionCosine());

      stream->print(F("Inclinaition correction sine (C(iS)): "));
      stream->println(getInclinationCorrectionSine());

      stream->print(F("Orbit radius correction cosine (C(rC)): "));
      stream->println(getOrbitRadiusCorrectionCosine());

      stream->print(
        F("Longitude of ascending node of orbit plane at weekly epoch (OMEGA(0)): ")
      );
      stream->println(getLongitudeOfAscendingNodeOfOrbitPlaneAtWeeklyEpoch());

      stream->print(F("Rate of right ascension (OMEGA DOT): "));
      stream->println(getRateOfRightAscension());

      stream->print(F("Argument of perigee (omega): "));
      stream->println(getArgumentOfPerigee());

      stream->print(F("Inclination angle at reference time (i(0)): "));
      stream->println(getInclinationAngleAtReferenceTime());

      stream->print(F("Rate of inclination angle (IDOT): "));
      stream->println(getRateOfInclinationAngle());

      stream->print(F("Issue of data - ephemeris (IODE): "));
      stream->println(getIssueOfDataEphemeris());

      stream->println();
    }
};
