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

    virtual ~TimingVerification() {}
};
