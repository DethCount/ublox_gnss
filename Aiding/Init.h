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

  	AidingInit() {}

  	AidingInit(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
  	}

    virtual ~AidingInit() {}
};
