class TimingPulse : public UBXMessage {
  public:
    uint32_t towMs;
    uint32_t towSubMs;
    int32_t qErr;
    uint16_t week;
    byte flags;

    TimingPulse() {
      msgId = MessageId::Timing_Pulse;
    }

    TimingPulse(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~TimingPulse() {}

    GNSSTimeBase2 getTimeBase() {
      return (GNSSTimeBase2) uint8_t(flags & 0x1);
    }

    bool isUTCAvailable() {
      return bool(flags & 0x2);
    }

    virtual void print(Stream* stream) {
      stream->println(F("TimingPulse"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Time of week according to time base: "));
      stream->print(towMs);
      stream->println(F("ms"));

      stream->print(F("nanoseconds of time of week  according to time base: "));
      stream->print(towSubMs);
      stream->println(F("ns"));

      stream->print(F("Quantization error of time pulse: "));
      stream->print(qErr);
      stream->println(F("ps"));

      stream->print(F("Week number according to time base: "));
      stream->println(week);

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Time base: 0x"));
      stream->println(uint8_t(getTimeBase()), HEX);

      stream->print(F("Is UTC available: "));
      stream->println(isUTCAvailable());

      stream->println();
    }
};
