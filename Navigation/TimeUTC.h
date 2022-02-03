class NavigationTimeUTC : public UBXMessage {
  public:
    uint32_t iTOW;
    uint32_t tAcc;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    int32_t nano;
    byte valid;

    NavigationTimeUTC() {
      msgId = MessageId::Navigation_TimeUTC;
    }

    NavigationTimeUTC(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationTimeUTC() {}

    bool isTimeOfWeekValid() {
      return bool(valid & 0x1);
    }

    bool isWeekNumberValid() {
      return bool(valid & 0x2);
    }

    bool isUTCValid() {
      return bool(valid & 0x4);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationTimeUTC"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Time accuracy estimate: "));
      stream->print(tAcc);
      stream->println("s");

      stream->print(F("UTC Year: "));
      stream->println(year);

      stream->print(F("UTC Month of year: "));
      stream->println(month);

      stream->print(F("UTC Day of month: "));
      stream->println(day);

      stream->print(F("UTC Hour of day: "));
      stream->println(hour);

      stream->print(F("UTC Minute of hour: "));
      stream->println(hour);

      stream->print(F("UTC Second of minute: "));
      stream->println(second);

      stream->print(F("UTC Nanosecond of second: "));
      stream->println(nano);

      stream->print(F("Validity flags: "));
      stream->println(valid, HEX);

      stream->print(F("Is time of week valid ? : "));
      stream->println(isTimeOfWeekValid());

      stream->print(F("Is week number valid ? : "));
      stream->println(isWeekNumberValid());

      stream->print(F("Is UTC valid ? : "));
      stream->println(isUTCValid());

      stream->println();
    }
};
