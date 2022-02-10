class NavigationStatus : public UBXMessage {
  public:
    uint32_t iTOW;
    GNSSFixType gpsFix;
    byte flags;
    byte flags2;
    byte fixStat;
    uint32_t ttff;
    uint32_t msss;

    NavigationStatus() {
      msgId = MessageId::Navigation_Status;
    }

    NavigationStatus(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationStatus() {}

    bool isGNSSFixOk() {
      return bool(flags & 0x1);
    }

    bool isDifferentialCorrectionAvailable() {
      return bool(flags & 0x2);
    }

    bool isWeekNumberValid() {
      return bool(flags & 0x4);
    }

    bool isTimeOfWeekValid() {
      return bool(flags & 0x8);
    }

    PowerSaveModeStatus getPowerSaveModeStatus() {
      return (PowerSaveModeStatus) uint8_t(flags2 & 0x3);
    }

    bool isDGPSInputEnabled() {
      return bool(fixStat & 0x1);
    }

    MapMatchingStatus getMapMatchingStatus() {
      return (MapMatchingStatus) uint8_t(fixStat & 0xC0);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationStatus"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("GNSS fix type: 0x"));
      stream->println(uint8_t(gpsFix), HEX);

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is GNSS fix Ok ? : "));
      stream->println(isGNSSFixOk());

      stream->print(F("Is differential correction available ? : "));
      stream->println(isDifferentialCorrectionAvailable());

      stream->print(F("Is week number valid ? : "));
      stream->println(isWeekNumberValid());

      stream->print(F("Is time of week valid ? : "));
      stream->println(isTimeOfWeekValid());

      stream->print(F("Flags 2: 0x"));
      stream->println(flags2, HEX);

      stream->print(F("Power save mode status: 0x"));
      stream->println(uint8_t(getPowerSaveModeStatus()), HEX);

      stream->print(F("GNSS fix stat: 0x"));
      stream->println(fixStat, HEX);

      stream->print(F("is PR+PRR Correction enabled as DGPS input ? : "));
      stream->println(isDGPSInputEnabled());

      stream->print(F("Map matching status : 0x"));
      stream->println(uint8_t(getMapMatchingStatus()), HEX);

      stream->print(F("Time To First Fix: "));
      stream->print(ttff);
      stream->println(F("ms"));

      stream->print(F("Time since startup / reset: "));
      stream->print(msss);
      stream->println(F("ms"));

      stream->println();
    }
};
