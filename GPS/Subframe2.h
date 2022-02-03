class GPSSubframe2 : public GPSSubframe  {
  public:
    GPSSubframe2(bool raw = false) : GPSSubframe(raw) {}

    uint8_t getIssueOfDataEphemeris() { // IODE
      return (uint8_t)(words[raw ? 2 : 0] >> 16);
    }

    uint16_t getOrbitRadiusCorrectionSine() { // C(rs)
      return (uint16_t)words[raw ? 2 : 0];
    }

    uint16_t getMeanMotionDifferenceFromComputedValue() { // delta n
      return (uint16_t)(words[raw ? 3 : 1] >> 8);
    }

    uint32_t getMeanAnomalyAtReferenceTime() { // M(0)
      return ((words[raw ? 3 : 1] & 0xFF) << 24)
        | (words[raw ? 4 : 2] & 0xFFFFFF);
    }

    uint16_t getLatitudeCorrectionCosine() { // C(UC)
      return (uint16_t)(words[raw ? 5 : 3] >> 8);
    }

    uint16_t getLatitudeCorrectionSine() { // C(US)
      return (uint16_t)(words[raw ? 7 : 5] >> 8);
    }

    uint32_t getEccentricity() { // e
      return ((words[raw ? 5 : 3] & 0xFF) << 24)
        | (words[raw ? 6 : 4] & 0xFFFFFF);
    }

    uint32_t getSemiMajorAxisSqrt() { // sqrt(A)
      return ((words[raw ? 7 : 5] & 0xFF) << 24)
        | (words[raw ? 8 : 6] & 0xFFFFFF);
    }

    uint16_t getTimeOfEphemeris() { // t(oe)
      return (uint16_t)(words[raw ? 9 : 7] >> 8);
    }

    bool getFitIntervalFlag() {
      return ((words[raw ? 9 : 7] >> 7) & 0x1) == 0x1;
    }

    uint8_t getAgeOfDataOffset() { // AODO
      return ((uint8_t)(words[raw ? 9 : 7] >> 2)) & 0x1F;
    }

    virtual void print(Stream* stream) {
      GPSSubframe::print(stream, "GPSSubframe2");

      stream->print(F("Issue of data - ephemeris (IODE): "));
      stream->println(getIssueOfDataEphemeris());

      stream->print(F("Orbit correction sine (C(rs)): "));
      stream->println(getOrbitRadiusCorrectionSine());

      stream->print(
        F("Mean motion difference from computed value (delta n): ")
      );
      stream->println(getMeanMotionDifferenceFromComputedValue());

      stream->print(F("Mean anomaly at reference time (M(0)): "));
      stream->println(getMeanAnomalyAtReferenceTime());

      stream->print(F("Lattitude correction cosine (C(UC)): "));
      stream->println(getLatitudeCorrectionCosine());

      stream->print(F("Lattitude correction sine (C(US)): "));
      stream->println(getLatitudeCorrectionSine());

      stream->print(F("Eccentricity (e): "));
      stream->println(getEccentricity());

      stream->print(F("Semi-major axis square root (sqrt(A)): "));
      stream->println(getSemiMajorAxisSqrt());

      stream->print(F("Time of ephemeris (t(oe)): "));
      stream->println(getTimeOfEphemeris());

      stream->print(F("FIT interval flag: "));
      stream->println(getFitIntervalFlag());

      stream->print(F("Age of data offset (AODO): "));
      stream->println(getAgeOfDataOffset());

      stream->println();
    }
};
