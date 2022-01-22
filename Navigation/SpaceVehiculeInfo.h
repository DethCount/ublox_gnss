class NavigationSpaceVehicule {
  public:
    uint8_t chn;
    uint8_t svid;
    byte flags;
    byte quality;
    uint8_t cno;
    int8_t elev;
    int16_t azim;
    int32_t prRes;

    NavigationSpaceVehicule() {}

    virtual ~NavigationSpaceVehicule() {}
};

class NavigationSpaceVehiculeInfo : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t numCh;
    byte globalFlags;
    // reserved2 U2
    NavigationSpaceVehicule* spaceVehicules[SVINFO_MAX_ITEMS];

    NavigationSpaceVehiculeInfo(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationSpaceVehiculeInfo() {}
};
