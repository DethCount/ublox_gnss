class NavigationPosECEF : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;

    NavigationPosECEF(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationPosECEF() {}
};
