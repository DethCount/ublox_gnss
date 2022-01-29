class NavigationTimeGPS : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    int8_t leapS;
    byte valid;
    uint32_t tAcc;

    NavigationTimeGPS() {
      msgId = MessageId::Navigation_TimeGPS;
    }

    NavigationTimeGPS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationTimeGPS() {}
};
