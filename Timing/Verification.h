class TimingVerification : public UBXMessage {
  public:
    int32_t iTOW;
    int32_t frac;
    int32_t deltaMs;
    int32_t deltaNs;
    uint16_t wno;
    byte flags;

    TimingVerification() {
      msgId = MessageId::Timing_Verification;
    }

    TimingVerification(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    GNSSAidingTimeSource getAidingTimeSource() {
      return (GNSSAidingTimeSource) uint8_t(flags & 0x7);
    }

    virtual ~TimingVerification() {}

    virtual void print(Stream* stream) {
      stream->println(F("TimingVerification"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GNSS Time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("GNSS nanoseconds of time of week: "));
      stream->print(frac);
      stream->println(F("ns"));

      stream->print(F("Delta time (local time - GNSS time): "));
      stream->print(deltaMs);
      stream->println(F("ms"));

      stream->print(F("Delta nanoseconds (local time - GNSS time): "));
      stream->print(deltaNs);
      stream->println(F("ns"));

      stream->print(F("GNSS Week number: "));
      stream->println(wno);

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Aiding time source: 0x"));
      stream->println(uint8_t(getAidingTimeSource()), HEX);

      stream->println();
    }
};
