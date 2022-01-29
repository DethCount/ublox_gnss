class ReceiverManagerEphemeris : public UBXMessage {
  public:
    uint32_t svid;
    uint32_t how;
    GPSSubframe1 *subframe1;
    GPSSubframe2 *subframe2;
    GPSSubframe3 *subframe3;

    ReceiverManagerEphemeris() {
      msgId = MessageId::ReceiverManager_Ephemeris;
    }

    ReceiverManagerEphemeris(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ReceiverManagerEphemeris() {}
};
