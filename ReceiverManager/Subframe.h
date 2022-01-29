class ReceiverManagerSubframe : public UBXMessage {
  public:
    uint8_t chn;
    uint8_t svid;
    GPSSubframe* subframe;

    ReceiverManagerRawSpaceVehicule* SVs[GNSS_MAX_SVID];

    ReceiverManagerSubframe() {
      msgId = MessageId::ReceiverManager_SubFrameBuffer;
    }

    ReceiverManagerSubframe(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ReceiverManagerSubframe() {}
};
