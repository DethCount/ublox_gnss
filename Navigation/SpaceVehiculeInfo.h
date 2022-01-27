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
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationSpaceVehiculeInfo() {}
};
