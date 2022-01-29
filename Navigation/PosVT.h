class NavigationPosVT : public UBXMessage {
  public:
    uint32_t iTOW;
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    byte valid;
    uint32_t tAcc;
    int32_t nano;
    GNSSFixType fixType;
    byte flags;
    uint8_t numSV;
    double longitude;
    double latitude;
    int32_t height;
    int32_t hMSL; // elevation above sea level
    uint32_t hAcc;
    uint32_t vAcc;
    double velocityNorth;
    double velocityEast;
    double velocityDown;
    double groundSpeed;
    double heading;
    uint32_t sAcc;
    double headingAcc;
    double pDOP;

    NavigationPosVT() {
      msgId = MessageId::Navigation_PosVT;
    }

    NavigationPosVT(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationPosVT() {}
};
