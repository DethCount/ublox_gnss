class NavigationSpaceVehiculeInfo : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t numCh;
    byte globalFlags;
    // reserved2 U2
    NavigationSpaceVehicule* spaceVehicules[GNSS_MAX_SVID];

    NavigationSpaceVehiculeInfo() {
      msgId = MessageId::Navigation_SpaceVehiculeInfo;
    }

    NavigationSpaceVehiculeInfo(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationSpaceVehiculeInfo() {}
};
