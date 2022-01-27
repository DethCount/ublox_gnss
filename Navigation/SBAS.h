class NavigationSBAS : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t geo;
    SBASMode mode;
    SBASSystem sys;
    byte service;
    uint8_t cnt;
    // reserved0 U1[3]
    NavigationSBASItem* items[SBAS_MAX_ITEMS];

    NavigationSBAS(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationSBAS() {}
};
