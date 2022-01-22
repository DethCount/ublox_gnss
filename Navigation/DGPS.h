enum struct DGPSStatus : uint8_t {
  None = 0x00,
  PRAndPRR = 0x01
};


class NavigationDGPSChannel {
  public:
    uint8_t svid;
    byte flags;
    uint16_t ageC;
    uint32_t prc;
    uint32_t prrc;

    NavigationDGPSChannel() {}

    virtual ~NavigationDGPSChannel() {}
};

class NavigationDGPS : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t age;
    int baseId;
    int baseHealth;
    uint8_t numCh;
    DGPSStatus status;
    NavigationDGPSChannel* channels[DGPS_MAX_CHANNELS];

    NavigationDGPS(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationDGPS() {}
};
