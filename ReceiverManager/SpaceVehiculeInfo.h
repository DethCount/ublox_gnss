class ReceiverManagerSpaceVehiculeInfo : public UBXMessage {
  public:
    uint32_t iTOW;
    int16_t week;
    uint8_t numVisibleSV;
    uint8_t numSV;

    ReceiverManagerSpaceVehicule* SVs[GNSS_MAX_SVID];

    ReceiverManagerSpaceVehiculeInfo() {
      msgId = MessageId::ReceiverManager_SVStatus;
    }

    ReceiverManagerSpaceVehiculeInfo(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ReceiverManagerSpaceVehiculeInfo() {}
};
