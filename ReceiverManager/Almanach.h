class ReceiverManagerAlmanach : public UBXMessage {
  public:
    uint32_t svid;
    uint32_t week;
    GPSSubframe *subframe;

    ReceiverManagerAlmanach() {
      msgId = MessageId::ReceiverManager_Almanach;
    }

    ReceiverManagerAlmanach(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ReceiverManagerAlmanach() {}
};
