class NavigationTimeUTC : public UBXMessage {
  public:
    uint32_t iTOW;
    uint32_t tAcc;
    int32_t nano;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    byte flags;

    NavigationTimeUTC() {
      msgId = MessageId::Navigation_TimeUTC;
    }

    NavigationTimeUTC(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationTimeUTC() {}
};
