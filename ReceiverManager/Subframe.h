class ReceiverManagerSubframe : public UBXMessage {
  public:
    uint8_t chn;
    uint8_t svid;
    uint8_t subframeId;
    GPSSubframe* subframe;

    ReceiverManagerSubframe() {
      msgId = MessageId::ReceiverManager_SubFrameBuffer;
    }

    ReceiverManagerSubframe(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ReceiverManagerSubframe() {}

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerSpaceVehiculeInfo"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Channel number: "));
      stream->println(chn);

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Subframe id: "));
      stream->println(subframeId);

      subframe->print(stream);

      stream->println();
    }
};
