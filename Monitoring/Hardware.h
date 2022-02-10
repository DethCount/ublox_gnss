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

    bool isRTCCalibrated() {
      return bool(flags & 0x1);
    }

    bool isSafeBootModeActive() {
      return bool(flags & 0x2);
    }

    GNSSJammingStatus getJammingState() {
      return (GNSSJammingStatus)((flags >> 2) & 0x3);
    }

    void print(Stream *stream) {
      stream->println(F("MonitoringHardware: "));

      if (!isValid) {
        stream->println(F("Invalid"));
        return;
      }

      stream->print(F("pinSel: 0x"));
      stream->println(pinSel, HEX);

      stream->print(F("pinBank: 0x"));
      stream->println(pinBank, HEX);

      stream->print(F("pinDir: 0x"));
      stream->println(pinDir, HEX);

      stream->print(F("pinVal: 0x"));
      stream->println(pinVal, HEX);

      stream->print(F("noisePerMS: "));
      stream->println(noisePerMS);

      stream->print(F("agcCnt: "));
      stream->println(agcCnt);

      stream->print(F("aStatus: 0x"));
      stream->println((uint8_t)aStatus, HEX);

      stream->print(F("aPower: 0x"));
      stream->println((uint8_t)aPower, HEX);

      stream->print(F("Flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is RTC calibrated ? : "));
      stream->println(isRTCCalibrated());

      stream->print(F("Jamming state : 0x"));
      stream->println(uint8_t(getJammingState()), HEX);

      stream->print(F("usedMask: 0x"));
      stream->println(usedMask, HEX);

      for(int i = 0; i < sizeof(VP); i++) {
        stream->print(F("VP["));
        stream->print(i);
        stream->print(F("]: 0x"));
        stream->println(VP[i], HEX);
      }

      stream->print(F("CW Jamming indicator, scaled (0x0 = no CW jamming, 0xFFFF = strong CW jamming): 0x"));
      stream->println(jamInd, HEX);

      stream->print(F("pinIrq: b"));
      stream->println(pinIrq, BIN);

      stream->print(F("pullHigh: 0x"));
      stream->println(pullHigh, HEX);

      stream->print(F("pullLow: 0x"));
      stream->println(pullLow, HEX);

      stream->println();
    }
};
