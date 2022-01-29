class NavigationVelNED : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t velocityNorth;
    int32_t velocityEast;
    int32_t velocityDown;
    uint32_t speed;
    uint32_t gSpeed;
    double heading;
    uint32_t sAcc;
    double cAcc;

    NavigationVelNED() {
      msgId = MessageId::Navigation_VelNED;
    }

    NavigationVelNED(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationVelNED() {}
};
