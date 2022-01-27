class GPSSubframe3 : public GPSSubframe  {
  public:
    uint16_t getInclinationCorrectionCosine() { // C(iC)
      return (uint16_t)(words[0] >> 8);
    }

    uint16_t getInclinationCorrectionSine() { // C(iS)
      return (uint16_t)(words[2] >> 8);
    }

    uint16_t getOrbitRadiusCorrectionCosine() { // C(rC)
      return (uint16_t)(words[4] >> 8);
    }

    uint32_t getLongitudeOfAscendingNodeOfOrbitPlaneAtWeeklyEpoch() { // OMEGA(0)
      return ((words[0] & 0xFF) << 24)
        | (words[1] & 0xFFFFFF);
    }

    uint32_t getArgumentOfPerigee() { // omega
      return ((words[5] & 0xFF) << 24)
        | (words[6] & 0xFFFFFF);
    }

    uint32_t getRateOfRightAscension() { // OMEGA DOT
      return words[5] & 0xFFFFFF;
    }

    uint32_t getInclinationAngleAtReferenceTime() { // i(0)
      return ((words[2] & 0xFF) << 24)
        | (words[3] & 0xFFFFFF);
    }

    uint16_t getRateOfInclinationAngle() { // IDOT
      return (uint16_t)(words[7] >> 2) & 0x3FFF;
    }

    uint8_t getIssueOfDataEphemeris() { // IODE
      return (uint8_t)(words[7] >> 16);
    }
};
