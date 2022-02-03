class NavigationTimeGPS : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    int8_t leapS;
    byte valid;
    uint32_t tAcc;

    NavigationTimeGPS() {
      msgId = MessageId::Navigation_TimeGPS;
    }

    NavigationTimeGPS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    bool isTimeOfWeekValid() {
      return bool(valid & 0x1);
    }

    bool isWeekNumberValid() {
      return bool(valid & 0x2);
    }

    bool isLeapSecondsValid() {
      return bool(valid & 0x4);
    }

    virtual ~NavigationTimeGPS() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationTimeGPS"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("GPS nanoseconds: "));
      stream->print(fTOW);
      stream->println(F("ns"));

      stream->print(F("GPS week number: "));
      stream->println(week);

      stream->print(F("GPS leap seconds: "));
      stream->print(leapS);
      stream->println(F("s"));

      stream->print(F("Validity flags: "));
      stream->println(valid);

      stream->print(F("Is time of week valid ? : "));
      stream->println(isTimeOfWeekValid());

      stream->print(F("Is week number valid ? : "));
      stream->println(isWeekNumberValid());

      stream->print(F("Is leap seconds valid ? : "));
      stream->println(isLeapSecondsValid());

      stream->print(F("Time accuracy estimate: "));
      stream->print(tAcc);
      stream->println(F("ns"));

      stream->println();
    }
};
