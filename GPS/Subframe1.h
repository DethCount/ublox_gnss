class GPSSubframe1 : public GPSSubframe  {
  public:
    uint16_t getWeekNumber() { // WN
      return ((uint16_t)(words[0] >> 14)) & 0x3FF;
    }

    uint8_t getUserRangeAccuracyIndex() { // URA Index
      return ((uint8_t)(words[0] >> 8)) & 0xF;
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
      return ((uint8_t)(words[0] >> 2)) & 0x3F;
    }

    uint16_t getIssueOfDataClock() { // IODC
      return ((((uint16_t)words[0]) & 0x3) << 8)
        | ((uint16_t)(words[5] >> 16) & 0xFF);
    }

    uint8_t getTelemetryGroupDelayDifferential() { // T(gd)
      return ((uint8_t)words[4]) & 0xFF;
    }

    uint16_t getTimeOfClock() { // t(oc)
      return ((uint16_t)words[5]) & 0xFFFF;
    }

    uint32_t getSVClockBiasCorrectionCoefficient() { // a(f0)
      return (words[7] >> 2) & 0x3FFFFF;
    }

    uint16_t getSVClockDriftCorrectionCoefficient() { // a(f1)
      return (uint16_t)words[6];
    }

    uint8_t getSVClockDriftRateCorrectionCoefficient() { // a(f2)
      return (uint8_t)(words[6] >> 16);
    }
};
