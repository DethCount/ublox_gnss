class AidingInit : public UBXMessage {
  public:
    int32_t ecefXOrLat;
    int32_t ecefYOrLon;
    int32_t ecefZOrAlt;
    uint32_t posAcc;
    uint16_t tmCfg;
    uint16_t wnoOrDate;
    uint32_t towOrTime;
    int32_t towNs;
    uint32_t tAccMs;
    uint32_t tAccNs;
    int32_t clkDOrFreq;
    uint32_t clkDAccOrFreqAcc;
    uint32_t flags;

  	AidingInit() {
      msgId = MessageId::Aiding_Init;
    }

  	AidingInit(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
  	}

    bool isLLA() {
      return bool(flags & 0x020);
    }

    bool isUTC() {
      return bool(flags & 0x0400);
    }

    bool isClockDrift() {
      return bool(flags & 0x4);
    }

    bool isClockDriftFrequency() {
      return bool(flags & 0x10);
    }

    virtual ~AidingInit() {}

    virtual void print(Stream* stream) {
      stream->println(F("AidingInit"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      if (isLLA()) {
        stream->print(F("Latitude: "));
        stream->print(ecefXOrLat);
        stream->println(F("° * 1e-7"));

        stream->print(F("Longitude: "));
        stream->print(ecefYOrLon);
        stream->println(F("° * 1e-7"));

        stream->print(F("Altitude: "));
        stream->print(ecefZOrAlt);
        stream->println(F("cm"));
      } else {
        stream->print(F("ecef X: "));
        stream->print(ecefXOrLat);
        stream->println(F("cm"));

        stream->print(F("ecef Y: "));
        stream->print(ecefYOrLon);
        stream->println(F("cm"));

        stream->print(F("ecef Z: "));
        stream->print(ecefZOrAlt);
        stream->println(F("cm"));
      }

      stream->print(F("Position accuracy: "));
      stream->print(posAcc);
      stream->println(F("cm"));

      stream->print(F("Time mark configuration: "));
      stream->println(tmCfg);

      if (isUTC()) {
        stream->print(F("Date: "));
        stream->print(wnoOrDate);
        stream->println(F("YYMM"));

        stream->print(F("Time: "));
        stream->print(towOrTime);
        stream->println(F("DDHHMMSS"));
      } else {
        stream->print(F("WNO: "));
        stream->print(wnoOrDate);
        stream->println(F("weeks"));

        stream->print(F("TOW: "));
        stream->print(towOrTime);
        stream->println(F("ms"));
      }

      stream->print(F("TOW (ns part): "));
      stream->print(towNs);
      stream->println(F("ns"));

      stream->print(F("Time accuracy (ms part): "));
      stream->print(tAccMs);
      stream->println(F("ms"));

      stream->print(F("Time accuracy (ns part): "));
      stream->print(tAccNs);
      stream->println(F("ns"));

      if (isClockDrift()) {
        stream->print(F("Clock drift: "));
        stream->print(clkDOrFreq);
        stream->println(F("ns/s"));

        stream->print(F("Clock drift accuracy: "));
        stream->print(clkDAccOrFreqAcc);
        stream->println(F("ns/s"));
      }

      if (isClockDriftFrequency()) {
        stream->print(F("Clock drift frequency: "));
        stream->print(clkDOrFreq);
        stream->println(F("Hz * 1e-2"));

        stream->print(F("Clock drift frequency accuracy: "));
        stream->print(clkDAccOrFreqAcc);
        stream->println(F("ppb"));
      }

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is Longitude / Latitude / Altitude ? : "));
      stream->println(isLLA());

      stream->print(F("Is clock drift ? : "));
      stream->println(isClockDrift());

      stream->print(F("Is clock drift frequency ? : "));
      stream->println(isClockDriftFrequency());

      stream->println();
    }
};
