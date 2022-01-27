class NavigationStatus : public UBXMessage {
  public:
    uint32_t iTOW;
    GNSSFixType gpsFix;
    byte flags;
    byte fixStat;
    byte flags2;
    uint32_t ttff;
    uint32_t msss;

    NavigationStatus(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationStatus() {}
};
