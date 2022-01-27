class GPSSubframe2 : public GPSSubframe  {
  public:
    uint8_t getIssueOfDataEphemeris() { // IODE
      return (uint8_t)(words[2] >> 22);
    }

    uint16_t getOrbitRadiusCorrectionSine() { // C(rs)
      return (uint16_t)(words[2] >> 6);
    }

    uint16_t getMeanMotionDifferenceFromComputedValue() { // delta n
      return (uint16_t)(words[3] >> 14);
    }

    uint32_t getMeanAnomalyAtReferenceTime() { // M(0)
      return (((words[3] >> 6) & 0xFF) << 24)
        | ((words[4] >> 6) & 0xFFFFFF);
    }

    uint16_t getLatitudeCorrectionCosine() { // C(UC)
      return (uint16_t)(words[5] >> 14);
    }

    uint16_t getLatitudeCorrectionSine() { // C(US)
      return (uint16_t)(words[7] >> 14);
    }

    uint32_t getExcentricity() { // e
      return (((words[5] >> 6) & 0xFF) << 24)
        | ((words[6] >> 6) 0xFFFFFF);
    }

    uint32_t getSemiMajorAxisSqrt() { // sqrt(A)
      return (((words[7] >> 6) & 0xFF) << 24)
        | ((words[8] >> 6) 0xFFFFFF);
    }

    uint16_t getTimeOfEphemeris() { // t(oe)
      return (uint16_t)(words[9] >> 14);
    }

    bool getFitIntervalFlag() {
      return (words[9] >> 13) & 0x1 == 0x1;
    }

    uint8_t getAgeOfDataOffset() { // AODO
      return ((uint8_t)(words[9] >> 8)) & 0x1F;
    }
};
