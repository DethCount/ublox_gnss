class NavigationTimeGPS : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    int8_t leapS;
    byte valid;
    uint32_t tAcc;

    NavigationTimeGPS(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationTimeGPS() {}
};
