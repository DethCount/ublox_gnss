class GPSSubframe1 : public GPSSubframe  {
  public:
    uint16_t getWeekNumber() { // WN
      return ((uint16_t)(words[2] >> 20)) & 0x3FF;
    }

    uint8_t getUserRangeAccuracyIndex() { // URA Index
      return ((uint8_t)(words[2] >> 14)) & 0xF;
    }

    uint8_t getSpaceVehiculeHealth() { // SV health
      return ((uint8_t)(words[2] >> 8)) & 0x3F;
    }

    uint16_t getIssueOfDataClock() { // IODC
      return ((((uint16_t)(words[2] >> 6)) & 0x3) << 8)
        | ((uint16_t)(words[7] >> 22) & 0xFF);
    }

    uint8_t getTelemetryGroupDelayDifferential() { // T(gd)
      return ((uint8_t)(words[6] >> 6)) & 0xFF;
    }

    uint16_t getTimeOfClock() { // t(oc)
      return ((uint16_t)(words[7] >> 6)) & 0xFFFF;
    }

    uint32_t getSVClockBiasCorrectionCoefficient() { // a(f0)
      return (words[9] >> 8) & 0x3FFFFF;
    }

    uint16_t getSVClockDriftCorrectionCoefficient() { // a(f1)
      return (uint16_t)(words[8] >> 6);
    }

    uint8_t getSVClockDriftRateCorrectionCoefficient() { // a(f2)
      return (uint8_t)(words[8] >> 22);
    }
};
