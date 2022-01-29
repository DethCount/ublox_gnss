class ReceiverManagerRaw : public UBXMessage {
  public:
    int32_t rcvTow;
    int16_t week;
    uint8_t numSV;

    ReceiverManagerRawSpaceVehicule* SVs[GNSS_MAX_SVID];

    ReceiverManagerRaw() {
      msgId = MessageId::ReceiverManager_Raw;
    }

    ReceiverManagerRaw(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ReceiverManagerRaw() {}
};
