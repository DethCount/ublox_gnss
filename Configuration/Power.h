class ConfigurationPower : public UBXMessage {
  public:
    uint8_t version;
    uint32_t flags;
    uint32_t updatePeriod;
    uint32_t searchPeriod;
    uint32_t gridOffset;
    uint16_t onTime;
    uint16_t minAcqTime;

    ConfigurationPower() {
      msgId = MessageId::Configuration_Power;
    }

    ConfigurationPower(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationPower() {}

    uint8_t getExternalInteruptPin() {
      return uint8_t(flags & 0x10);
    }

    bool isExternalInteruptWakeUpEnabled() {
      return bool(flags & 0x20);
    }

    bool isExternalInteruptBackUpEnabled() {
      return bool(flags & 0x40);
    }

    bool isLimitPeakEnabled() {
      return bool(flags & 0x100);
    }

    bool waitForTimeFixBeforeStartingOnTime() {
      return bool(flags & 0x400);
    }

    bool updateRealTimeClock() {
      return bool(flags & 0x800);
    }

    bool updateEphemeris() {
      return bool(flags & 0x1000);
    }

    bool doNotEnterInactiveForSearch() {
      return bool(flags & 0x10000);
    }

    bool isCyclicTrackingModeEnabled() {
      return bool(flags & 0x20000);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationPower"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("version: "));
      stream->println(version);

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is External Interupt wake up enabled ? : "));
      stream->println(isExternalInteruptWakeUpEnabled());

      stream->print(F("Is External Interupt back up enabled ? : "));
      stream->println(isExternalInteruptBackUpEnabled());

      stream->print(F("Is limit peak enabled ?: "));
      stream->println(isLimitPeakEnabled());

      stream->print(F("Do wait for time fix before starting on-time ? : "));
      stream->println(waitForTimeFixBeforeStartingOnTime());

      stream->print(F("Do wait for time fix before starting on-time ? : "));
      stream->println(waitForTimeFixBeforeStartingOnTime());

      stream->print(F("Update Real Time Clock ? : "));
      stream->println(updateRealTimeClock());

      stream->print(F("Update ephemeris ? : "));
      stream->println(updateEphemeris());

      stream->print(F("Do not enter inactive-for-search state ? : "));
      stream->println(doNotEnterInactiveForSearch());

      stream->print(F("Is cyclic tracking operation enabled ? : "));
      stream->println(isCyclicTrackingModeEnabled());

      stream->print(F("updatePeriod: "));
      stream->print(updatePeriod);
      stream->println(F("ms"));

      stream->print(F("searchPeriod: "));
      stream->print(searchPeriod);
      stream->println(F("ms"));

      stream->print(F("gridOffset: "));
      stream->print(gridOffset);
      stream->println(F("ms"));

      stream->print(F("onTime: "));
      stream->print(onTime);
      stream->println(F("s"));

      stream->print(F("minAcqTime: "));
      stream->print(minAcqTime);
      stream->println(F("s"));

      stream->println();
    }
};
