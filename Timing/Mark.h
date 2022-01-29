class TimingMark : public UBXMessage {
  public:
    uint8_t ch;
    byte flags;
    uint16_t count;
    uint16_t wnR;
    uint16_t wnF;
    uint32_t towMsR;
    uint32_t towSubMsR;
    uint32_t towMsF;
    uint32_t towSubMsF;
    uint32_t accEst;

    TimingMark() {
      msgId = MessageId::Timing_Mark;
    }

    TimingMark(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~TimingMark() {}
};
