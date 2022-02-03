class NavigationClock : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t clkB;
    int32_t clkD;
    uint32_t tAcc;
    uint32_t fAcc;

    NavigationClock() {
      msgId = MessageId::Navigation_Clock;
    }

    NavigationClock(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationClock() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationClock"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Clock bias: "));
      stream->print(clkB);
      stream->println(F("ns"));

      stream->print(F("Clock drift: "));
      stream->print(clkD);
      stream->println(F("ns/s"));

      stream->print(F("Time accuracy estimate: "));
      stream->print(tAcc);
      stream->println(F("ns"));

      stream->print(F("Frequency accuracy estimate: "));
      stream->print(fAcc);
      stream->println(F("ps/s"));

      stream->println();
    }
};
