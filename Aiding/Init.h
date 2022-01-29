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

    virtual ~AidingInit() {}
};
