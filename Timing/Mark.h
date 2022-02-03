class TimingMark : public UBXMessage {
  public:
    uint8_t ch;
    byte flags;
    uint16_t count;
    uint16_t wnR;
    uint16_t wnF;
    uint32_t towMsR;
    uint32_t towSubMsR;
    uint32_t towMsF;
    uint32_t towSubMsF;
    uint32_t accEst;

    TimingMark() {
      msgId = MessageId::Timing_Mark;
    }

    TimingMark(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~TimingMark() {}

    bool isInRunningMode() {
      return bool(flags & 0x1);
    }

    bool isStopped() {
      return bool(flags & 0x2);
    }

    bool isNewFallingEdgeDetected() {
      return bool(flags & 0x4);
    }

    GNSSTimeBase getTimeBase() {
      return (GNSSTimeBase) uint8_t((flags >> 3) & 0x3);
    }

    bool isUTCAvailable() {
      return bool(flags & 0x20);
    }

    bool isTimeValid() {
      return bool(flags & 0x40);
    }

    bool isNewRisingEdgeDetected() {
      return bool(flags & 0x80);
    }

    virtual void print(Stream* stream) {
      stream->println(F("TimingMark"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Channel number: "));
      stream->println(ch);

      stream->print(F("Flags: "));
      stream->println(flags, HEX);

      stream->print(F("Is in running mode ? : "));
      stream->println(isInRunningMode());

      stream->print(F("Is stopped ? : "));
      stream->println(isStopped());

      stream->print(F("Is new falling edge detected ? : "));
      stream->println(isNewFallingEdgeDetected());

      stream->print(F("Time base : "));
      stream->println(uint8_t(getTimeBase()));

      stream->print(F("Is UTC available ? : "));
      stream->println(isUTCAvailable());

      stream->print(F("Is time valid ? : "));
      stream->println(isTimeValid());

      stream->print(F("Is new rising edge detected ? : "));
      stream->println(isNewRisingEdgeDetected());

      stream->print(F("Rising edge counter value: "));
      stream->println(count);

      stream->print(F("Week number of last rising edge: "));
      stream->println(wnR);

      stream->print(F("Week number of last falling edge: "));
      stream->println(wnF);

      stream->print(F("Time of week of rising edge: "));
      stream->print(towMsR);
      stream->println(F("ms"));

      stream->print(F("nanoseconds of time of week of rising edge: "));
      stream->print(towSubMsR);
      stream->println(F("ns"));

      stream->print(F("Time of week of falling edge: "));
      stream->print(towMsF);
      stream->println(F("ms"));

      stream->print(F("nanoseconds of time of week of falling edge: "));
      stream->print(towSubMsF);
      stream->println(F("ns"));

      stream->print(F("Accuracy estimate: "));
      stream->print(accEst);
      stream->println(F("ns"));

      stream->println();
    }
};
