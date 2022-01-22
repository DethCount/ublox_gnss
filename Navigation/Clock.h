class NavigationClock : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t clkB;
    int32_t clkD;
    uint32_t tAcc;
    uint32_t fAcc;

    NavigationClock(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationClock() {}
};
