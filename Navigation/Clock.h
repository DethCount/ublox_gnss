class NavigationClock : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t clkB;
    int32_t clkD;
    uint32_t tAcc;
    uint32_t fAcc;

    NavigationClock() {
      msgId = MessageId::Navigation_Clock;
    }

    NavigationClock(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationClock() {}
};
