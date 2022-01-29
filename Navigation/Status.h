class NavigationStatus : public UBXMessage {
  public:
    uint32_t iTOW;
    GNSSFixType gpsFix;
    byte flags;
    byte fixStat;
    byte flags2;
    uint32_t ttff;
    uint32_t msss;

    NavigationStatus() {
      msgId = MessageId::Navigation_Status;
    }

    NavigationStatus(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationStatus() {}
};
