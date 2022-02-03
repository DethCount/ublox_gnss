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

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerAlmanach"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Week number: "));
      stream->println(week);

      if (week != 0) {
        subframe->print(stream);
      }

      stream->println();
    }
};
