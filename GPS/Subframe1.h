class GPSSubframe1 : public GPSSubframe  {
  public:
    GPSSubframe1(bool raw = false) : GPSSubframe(raw) {}

    uint16_t getWeekNumber() { // WN
      return ((uint16_t)(words[raw ? 2 : 0] >> 14)) & 0x3FF;
    }

    uint8_t getUserRangeAccuracyIndex() { // URA Index
      return ((uint8_t)(words[raw ? 2 : 0] >> 8)) & 0xF;
    }

    uint16_t getUserRangeAccuracyIndexInMeters() {
      uint8_t idx = getUserRangeAccuracyIndex();
      switch (idx) {
        case 0:
          return 2.4;
        case 1:
          return 3.4;
        case 2:
          return 4.85;
        case 3:
          return 6.85;
        case 4:
          return 9.65;
        case 5:
          return 13.65;
        case 6:
          return 24;
        case 7:
          return 48;
        case 8:
          return 96;
        case 9:
          return 192;
        case 10:
          return 384;
        case 11:
          return 768;
        case 12:
          return 1536;
        case 13:
          return 3072;
        case 14:
          return 6144;
      }

      return 0xFFFF;
    }

    uint8_t getSpaceVehiculeHealth() { // SV health
      return ((uint8_t)(words[raw ? 2 : 0] >> 2)) & 0x3F;
    }

    uint16_t getIssueOfDataClock() { // IODC
      return ((((uint16_t)words[raw ? 2 : 0]) & 0x3) << 8)
        | ((uint16_t)(words[raw ? 7 : 5] >> 16) & 0xFF);
    }

    uint8_t getTelemetryGroupDelayDifferential() { // T(gd)
      return ((uint8_t)words[raw ? 6 : 4]) & 0xFF;
    }

    uint16_t getTimeOfClock() { // t(oc)
      return ((uint16_t)words[raw ? 7 : 5]) & 0xFFFF;
    }

    uint32_t getSVClockBiasCorrectionCoefficient() { // a(f0)
      return (words[raw ? 9 : 7] >> 2) & 0x3FFFFF;
    }

    uint16_t getSVClockDriftCorrectionCoefficient() { // a(f1)
      return (uint16_t)words[raw ? 8 : 6];
    }

    uint8_t getSVClockDriftRateCorrectionCoefficient() { // a(f2)
      return (uint8_t)(words[raw ? 8 : 6] >> 16);
    }

    virtual void print(Stream* stream) {
      GPSSubframe::print(stream, "GPSSubframe1");

      stream->print(F("week number (WN): "));
      stream->println(getWeekNumber());

      stream->print(F("user range accuracy index (URA Index): "));
      stream->println(getUserRangeAccuracyIndex());

      stream->print(F("user range accuracy index (URA Index): "));
      stream->print(getUserRangeAccuracyIndexInMeters());
      stream->println(F("m"));

      stream->print(F("space vehicule health (SV Health): "));
      stream->println(getSpaceVehiculeHealth());

      stream->print(F("issue of data - clock (IODC): "));
      stream->println(getIssueOfDataClock());

      stream->print(F("telemetry group delay differential (T(gd)): "));
      stream->println(getTelemetryGroupDelayDifferential());

      stream->print(F("time of clock (t(oc)): "));
      stream->println(getTimeOfClock());

      stream->print(
        F("space vehicule clock bias correction coefficient (a(f0)): ")
      );
      stream->println(getSVClockBiasCorrectionCoefficient());

      stream->print(
        F("space vehicule clock drift correction coefficient (a(f1)): ")
      );
      stream->println(getSVClockDriftCorrectionCoefficient());

      stream->print(
        F("space vehicule clock drift rate correction coefficient (a(f2)): ")
      );
      stream->println(getSVClockDriftRateCorrectionCoefficient());

      stream->println();
    }
};
