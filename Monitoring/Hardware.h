class MonitoringHardware : public UBXMessage {
  public:
    static const uint8_t NB_PINS = 17;

    uint32_t pinSel;
    uint32_t pinBank;
    uint32_t pinDir;
    uint32_t pinVal;
    uint16_t noisePerMS;
    uint16_t agcCnt;
    AntennaSupervisorStatus aStatus;
    AntennaPowerStatus aPower;
    byte flags;
    uint32_t usedMask;
    uint8_t VP[NB_PINS];
    uint8_t jamInd;
    uint32_t pinIrq;
    uint32_t pullHigh;
    uint32_t pullLow;

    MonitoringHardware() {
      msgId = MessageId::Monitoring_Hardware;
    }

    MonitoringHardware(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringHardware() {
      delete VP;
    }

    void print(Stream *stream) {
      stream->println(F("MonitoringHardware: "));

      if (!isValid) {
        stream->println(F("Invalid"));
        return;
      }

      stream->print(F("pinSel: "));
      stream->println(pinSel, HEX);

      stream->print(F("pinBank: "));
      stream->println(pinBank, HEX);

      stream->print(F("pinDir: "));
      stream->println(pinDir, HEX);

      stream->print(F("pinVal: "));
      stream->println(pinVal, HEX);

      stream->print(F("noisePerMS: "));
      stream->println(noisePerMS);

      stream->print(F("agcCnt: "));
      stream->println(agcCnt);

      stream->print(F("aStatus: "));
      stream->println((uint8_t)aStatus, HEX);

      stream->print(F("aPower: "));
      stream->println((uint8_t)aPower, HEX);

      stream->print(F("flags: "));
      stream->println(flags, HEX);

      stream->print(F("usedMask: "));
      stream->println(usedMask, HEX);

      for(int i = 0; i < sizeof(VP); i++) {
        stream->print(F("VP["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(VP[i], HEX);
      }

      stream->print(F("jamInd: "));
      stream->println(jamInd, HEX);

      stream->print(F("pinIrq: "));
      stream->println(pinIrq, BIN);

      stream->print(F("pullHigh: "));
      stream->println(pullHigh, HEX);

      stream->print(F("pullLow: "));
      stream->println(pullLow, HEX);

      stream->println();
    }
};
