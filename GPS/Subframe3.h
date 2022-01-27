class GPSSubframe3 : public GPSSubframe  {
  public:
    uint16_t getInclinationCorrectionCosine() { // C(iC)
      return (uint16_t)(words[2] >> 14);
    }

    uint16_t getInclinationCorrectionSine() { // C(iS)
      return (uint16_t)(words[4] >> 14);
    }

    uint16_t getOrbitRadiusCorrectionCosine() { // C(rC)
      return (uint16_t)(words[6] >> 14);
    }

    uint32_t getLongitudeOfAscendingNodeOfOrbitPlaneAtWeeklyEpoch() { // OMEGA(0)
      return (((words[2] >> 6) & 0xFF) << 24)
        | ((words[3] >> 6) & 0xFFFFFF);
    }

    uint32_t getArgumentOfPerigee() { // omega
      return (((words[7] >> 6) & 0xFF) << 24)
        | ((words[8] >> 6) & 0xFFFFFF);
    }

    uint32_t getRateOfRightAscension() { // OMEGA DOT
      return (words[7] >> 6) & 0xFFFFFF;
    }

    uint32_t getInclinationAngleAtReferenceTime() { // i(0)
      return (((words[4] >> 6) & 0xFF) << 24)
        | ((words[5] >> 6) & 0xFFFFFF);
    }

    uint16_t getRateOfInclinationAngle() { // IDOT
      return (uint16_t)(words[9] >> 8) & 0x3FFF;
    }

    uint8_t getIssueOfDataEphemeris() { // IODE
      return (uint8_t)(words[9] >> 22);
    }
};
