class NavigationSBAS : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t geo;
    SBASMode mode;
    SBASSystem sys;
    byte service;
    uint8_t cnt;
    // reserved0 U1[3]
    NavigationSBASItem* items[GNSS_MAX_SVID];

    NavigationSBAS() {
      msgId = MessageId::Navigation_SBAS;
    }

    NavigationSBAS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationSBAS() {}
};
