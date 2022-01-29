class NavigationPosLLH : public UBXMessage {
  public:
    uint32_t iTOW;
    double longitude;
    double latitude;
    int32_t height;
    int32_t hMSL; // elevation above sea level
    uint32_t hAcc;
    uint32_t vAcc;

    NavigationPosLLH() {
      msgId = MessageId::Navigation_PosLLH;
    }

    NavigationPosLLH(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationPosLLH() {}
};
