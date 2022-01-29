class NavigationPosECEF : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;

    NavigationPosECEF() {
      msgId = MessageId::Navigation_PosECEF;
    }

    NavigationPosECEF(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationPosECEF() {}
};
