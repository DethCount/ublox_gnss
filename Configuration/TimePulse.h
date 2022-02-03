class ConfigurationTimePulse : public UBXMessage {
  public:
    uint8_t tpIdx;
    int16_t antCableDelay;
    int16_t rfGroupDelay;
    uint32_t freqPeriod;
    uint32_t freqPeriodLock;
    uint32_t pulseLenRatio;
    uint32_t pulseLenRatioLock;
    int32_t userConfigDelay;
    uint32_t flags;

    ConfigurationTimePulse() {
      msgId = MessageId::Configuration_TimePulse;
    }

    ConfigurationTimePulse(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationTimePulse() {}

    bool isFreq() {
      return bool(flags & 0x08);
    }

    bool isLength() {
      return bool(flags & 0x10);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationTimePulse"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("tpIdx: "));
      stream->println(tpIdx);

      stream->print(F("antCableDelay: "));
      stream->print(antCableDelay);
      stream->println(F("ns"));

      stream->print(F("rfGroupDelay: "));
      stream->print(rfGroupDelay);
      stream->println(F("ns"));

      bool isF = isFreq();

      stream->print(F("freqPeriod: "));
      stream->print(freqPeriod);
      stream->println(isF ? F("Hz") : F("us"));

      stream->print(F("freqPeriodLock: "));
      stream->print(freqPeriodLock);
      stream->println(isF ? F("Hz") : F("us"));

      bool isL = isLength();

      stream->print(F("pulseLenRatio: "));
      stream->print(pulseLenRatio);
      stream->println(isL ? F("us") : F("2^-32"));

      stream->print(F("pulseLenRatioLock: "));
      stream->print(pulseLenRatioLock);
      stream->println(isL ? F("us") : F("2^-32"));

      stream->print(F("userConfigDelay: "));
      stream->print(userConfigDelay);
      stream->println(F("ns"));

      stream->print(F("flags: "));
      stream->print(flags, HEX);

      stream->println();
    }
};
