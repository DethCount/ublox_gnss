class GPSSubframe2 : public GPSSubframe  {
  public:
    uint8_t getIssueOfDataEphemeris() { // IODE
      return (uint8_t)(words[0] >> 16);
    }

    uint16_t getOrbitRadiusCorrectionSine() { // C(rs)
      return (uint16_t)words[0];
    }

    uint16_t getMeanMotionDifferenceFromComputedValue() { // delta n
      return (uint16_t)(words[1] >> 8);
    }

    uint32_t getMeanAnomalyAtReferenceTime() { // M(0)
      return ((words[1] & 0xFF) << 24)
        | (words[2] & 0xFFFFFF);
    }

    uint16_t getLatitudeCorrectionCosine() { // C(UC)
      return (uint16_t)(words[3] >> 8);
    }

    uint16_t getLatitudeCorrectionSine() { // C(US)
      return (uint16_t)(words[5] >> 8);
    }

    uint32_t getEccentricity() { // e
      return ((words[3] & 0xFF) << 24)
        | (words[4] & 0xFFFFFF);
    }

    uint32_t getSemiMajorAxisSqrt() { // sqrt(A)
      return ((words[5] & 0xFF) << 24)
        | (words[6] & 0xFFFFFF);
    }

    uint16_t getTimeOfEphemeris() { // t(oe)
      return (uint16_t)(words[7] >> 8);
    }

    bool getFitIntervalFlag() {
      return ((words[7] >> 7) & 0x1) == 0x1;
    }

    uint8_t getAgeOfDataOffset() { // AODO
      return ((uint8_t)(words[7] >> 2)) & 0x1F;
    }
};
