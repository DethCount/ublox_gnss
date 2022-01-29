class NavigationSOL : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    GNSSFixType gpsFix;
    byte flags;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;
    int32_t ecefVX;
    int32_t ecefVY;
    int32_t ecefVZ;
    uint32_t sAcc;
    double pDOP;
    // reserved1 U1
    uint8_t numSV;
    // reserved2 U4

    NavigationSOL() {
      msgId = MessageId::Navigation_SOL;
    }

    NavigationSOL(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationSOL() {}
};
