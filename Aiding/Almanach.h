class AidingAlmanach : public UBXMessage {
  public:
    static const uint8_t MAX_NB_DWORD = 8;

    uint32_t svid;
    uint32_t week;
    uint8_t subframeId;
    GPSSubframe* subframe;

    AidingAlmanach() {
      msgId = MessageId::Aiding_Almanach;
    }

    AidingAlmanach(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~AidingAlmanach() {}

    virtual void print(Stream* stream) {
      stream->println(F("AidingAlmanach"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("week: "));
      stream->println(week);

      if (week != 0) {
        subframe->print(stream);
      }

      stream->println();
    }
};
