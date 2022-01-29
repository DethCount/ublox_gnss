class TimingPulse : public UBXMessage {
  public:
    uint32_t towMS;
    uint32_t towSubMS;
    int32_t qErr;
    uint16_t week;
    byte flags;

    TimingPulse() {
      msgId = MessageId::Timing_Pulse;
    }

    TimingPulse(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~TimingPulse() {}
};
