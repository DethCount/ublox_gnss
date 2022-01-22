enum struct SBASMode : uint8_t {
  Disabled = 0x00,
  EnabledIntegrity = 0x01,
  EnabledTestmode = 0x03
};

enum struct SBASSystem : int8_t {
  Unknown = -1,
  WAAS = 0,
  EGNOS = 1,
  MSAS = 2,
  GPS = 16
};

class NavigationSBASItem {
  public:
    uint8_t svid;
    byte flags;
    byte udre;
    SBASSystem svSys;
    byte svService;
    // reserved1 U1
    int16_t prc;
    // reserved2 U2
    int16_t ic;

    NavigationSBASItem() {}

    virtual ~NavigationSBASItem() {}
};

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
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationSBAS() {}
};
