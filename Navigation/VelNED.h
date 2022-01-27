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

    NavigationVelNED(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationVelNED() {}
};
