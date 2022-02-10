class NavigationPosVT : public UBXMessage {
  public:
    uint32_t iTOW;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    byte valid;
    uint32_t tAcc;
    int32_t nano;
    GNSSFixType fixType;
    byte flags;
    uint8_t numSV;
    double longitude;
    double latitude;
    int32_t height;
    int32_t hMSL; // elevation above sea level
    uint32_t hAcc;
    uint32_t vAcc;
    double velocityNorth;
    double velocityEast;
    double velocityDown;
    double groundSpeed;
    double heading;
    uint32_t sAcc;
    double headingAcc;
    double pDOP;

    NavigationPosVT() {
      msgId = MessageId::Navigation_PosVT;
    }

    NavigationPosVT(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationPosVT() {}

    bool hasValidUTCDate() {
      return bool(valid & 0x1);
    }

    bool hasValidUTCTime() {
      return bool(valid & 0x2);
    }

    bool hasFullyResolvedUTCTime() {
      return bool(valid & 0x4);
    }

    bool isValidFix() {
      return bool(flags & 0x1);
    }

    bool hasAppliedDifferentialCorrections() {
      return bool(flags & 0x2);
    }

    PowerSaveModeStatus2 getPowerSaveModeStatus() {
      return (PowerSaveModeStatus2) (uint8_t(flags >> 2) & 0x7);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationPosVT"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

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

      stream->print(F("Validity flags: 0x"));
      stream->println(valid, HEX);

      stream->print(F("Is UTC Date valid ? : "));
      stream->println(hasValidUTCDate());

      stream->print(F("Is UTC Time valid ? : "));
      stream->println(hasValidUTCTime());

      stream->print(F("Is UTC Time fully resolved ? : "));
      stream->println(hasFullyResolvedUTCTime());

      stream->print(F("Time accuracy estimate: "));
      stream->print(tAcc);
      stream->println("s");

      stream->print(F("GNSS fix type: "));
      stream->println(uint8_t(fixType));

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is valid fix ? : "));
      stream->println(isValidFix());

      stream->print(F("Were differential solution corrections applied ? : "));
      stream->println(hasAppliedDifferentialCorrections());

      stream->print(F("Number of space vehicules used: "));
      stream->println(numSV);

      stream->print(F("Longitude: "));
      stream->print(longitude);
      stream->println("°");

      stream->print(F("Latitude: "));
      stream->print(latitude);
      stream->println("°");

      stream->print(F("Height above ellipsoid: "));
      stream->print(height);
      stream->println("mm");

      stream->print(F("Height above mean sea level: "));
      stream->print(hMSL);
      stream->println("mm");

      stream->print(F("Horizontal accuracy estimate: "));
      stream->print(hAcc);
      stream->println("mm");

      stream->print(F("Vertical accuracy estimate: "));
      stream->print(vAcc);
      stream->println("mm");

      stream->print(F("NED North velocity: "));
      stream->print(velocityNorth);
      stream->println("mm/s");

      stream->print(F("NED East velocity: "));
      stream->print(velocityEast);
      stream->println("mm/s");

      stream->print(F("NED Down velocity: "));
      stream->print(velocityDown);
      stream->println("mm/s");

      stream->print(F("Ground speed (2-D): "));
      stream->print(groundSpeed);
      stream->println("mm/s");

      stream->print(F("Heading of motion (2-D): "));
      stream->print(heading);
      stream->println("°");

      stream->print(F("Speed accuracy estimate: "));
      stream->print(sAcc);
      stream->println("mm/s");

      stream->print(F("Heading accuracy estimate: "));
      stream->print(headingAcc);
      stream->println("°");

      stream->print(F("Position dillution of precision: "));
      stream->println(pDOP);

      stream->println();
    }
};
