class NavigationVelECEF : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t ecefVX;
    int32_t ecefVY;
    int32_t ecefVZ;
    uint32_t sAcc;

    NavigationVelECEF() {
      msgId = MessageId::Navigation_VelECEF;
    }

    NavigationVelECEF(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationVelECEF() {}
};
