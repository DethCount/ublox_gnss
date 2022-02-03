class LogRetrievePosition : public UBXMessage {
  public:
    uint32_t entryIndex;
    double lon;
    double lat;
    int32_t hMSL;
    uint32_t hAcc;
    uint32_t groundSpeed;
    uint32_t heading;
    uint8_t version;
    GNSSFixType fixType;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t numSV;

    LogRetrievePosition() {
      msgId = MessageId::Log_RetrievePosition;
    }

    LogRetrievePosition(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~LogRetrievePosition() {}

    virtual void print(Stream* stream) {
      stream->println(F("LogRetrievePosition"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Entry index: "));
      stream->println(entryIndex);

      stream->print(F("Longitude: "));
      stream->print(lon);
      stream->println(F("°"));

      stream->print(F("Latitude: "));
      stream->print(lat);
      stream->println(F("°"));

      stream->print(F("Height above mean sea level: "));
      stream->print(hMSL);
      stream->println(F("mm"));

      stream->print(F("Horizontal accuracy estimate: "));
      stream->print(hAcc);
      stream->println(F("mm"));

      stream->print(F("Ground speed (2-D): "));
      stream->print(groundSpeed);
      stream->println(F("mm/s"));

      stream->print(F("Heading: "));
      stream->print(heading);
      stream->println(F("°"));

      stream->print(F("Message version: "));
      stream->println(version);

      stream->print(F("GNSS fix type: "));
      stream->println(uint8_t(fixType));

      stream->print(F("UTC year: "));
      stream->println(year);

      stream->print(F("UTC month: "));
      stream->println(month);

      stream->print(F("UTC day: "));
      stream->println(day);

      stream->print(F("UTC hour: "));
      stream->println(hour);

      stream->print(F("UTC minute: "));
      stream->println(minute);

      stream->print(F("UTC second: "));
      stream->println(second);

      stream->print(F("Number of space vehicules used: "));
      stream->println(numSV);

      stream->println();
    }
};
