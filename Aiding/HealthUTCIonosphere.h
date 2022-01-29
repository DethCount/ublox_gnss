class AidingHealthUTCIonosphere : public UBXMessage {
  public:
    uint32_t health;
    uint64_t utcA0;
    uint64_t utcA1;
    int32_t utcTOW;
    int16_t utcWNT;
    int16_t utcLS;
    int16_t utcWNF;
    int16_t utcDN;
    int16_t utcLSF;
    int16_t utcSpare;
    uint32_t klobA0;
    uint32_t klobA1;
    uint32_t klobA2;
    uint32_t klobA3;
    uint32_t klobB0;
    uint32_t klobB1;
    uint32_t klobB2;
    uint32_t klobB3;
    uint32_t flags;

  	AidingHealthUTCIonosphere() {
      msgId = MessageId::Aiding_HealthUTCIonosphere;
    }

  	AidingHealthUTCIonosphere(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
  	}

    virtual ~AidingHealthUTCIonosphere() {}
};
