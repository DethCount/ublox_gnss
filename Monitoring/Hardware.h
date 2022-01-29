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

    virtual ~MonitoringHardware() {}
};
