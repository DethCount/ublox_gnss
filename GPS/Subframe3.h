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

    uint32_t getLongitudeOfAscendingNodeOfOrbitPlaneAtWeeklyEpoch() { // OMEGA(0)
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
};
