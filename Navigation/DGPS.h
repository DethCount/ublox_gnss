enum struct DGPSStatus : uint8_t {
  None = 0x00,
  PRAndPRR = 0x01
};

class NavigationDGPS : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t age;
    int baseId;
    int baseHealth;
    uint8_t numCh;
    DGPSStatus status;
    NavigationDGPSChannel* channels[GNSS_MAX_SVID];

    NavigationDGPS() {
      msgId = MessageId::Navigation_DGPS;
    }

    NavigationDGPS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationDGPS() {}
};
