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

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerEphemeris"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Hand-Over Word: "));
      stream->println(how);

      if (how != 0) {
        subframe1->print(stream);
        subframe2->print(stream);
        subframe3->print(stream);
      }

      stream->println();
    }
};
