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

    bool isTimePulseEnabled() {
      return bool(flags & 0x1);
    }

    bool isGPSSyncEnabled() {
      return bool(flags & 0x2);
    }

    bool isConfigurationFrequencyPeriodLockEnabled() {
      return bool(flags & 0x4);
    }

    bool isFreq() {
      return bool(flags & 0x08);
    }

    bool isLength() {
      return bool(flags & 0x10);
    }

    bool isAlignedToTOW() {
      return bool(flags & 0x20);
    }

    bool isRisingPulse() {
      return bool(flags & 0x40);
    }

    bool useGPSTimegrid() {
      return bool(flags & 0x80);
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

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is time pulse enabled ? : "));
      stream->println(isTimePulseEnabled());

      stream->print(F("Is GPS synchronisation enabled ? : "));
      stream->println(isGPSSyncEnabled());

      stream->print(F("Use configuration frequency/period lock ? : "));
      stream->println(isConfigurationFrequencyPeriodLockEnabled());

      stream->print(F("Use frequencies (in Hz) in configuration instead of period (in us) ? : "));
      stream->println(isFreq());

      stream->print(F("Use pulse length in configuration (us) instead of duty cycles (2^-32 scale) ? : "));
      stream->println(isLength());

      stream->print(F("Align pulse to top of second (period time must be integer fraction of 1s) ? : "));
      stream->println(isAlignedToTOW());

      stream->print(F("Pulse polarity : rising edge (at top of second) ? : "));
      stream->println(isRisingPulse());

      stream->print(F("Use GPS timegrid instead of UTC ? : "));
      stream->println(useGPSTimegrid());

      stream->println();
    }
};
