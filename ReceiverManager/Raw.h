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

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerRaw"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Local time of week: "));
      stream->println(rcvTow);

      stream->print(F("Local week number: "));
      stream->println(week);

      stream->print(F("Number of space vehicules: "));
      stream->println(numSV);

      for (uint8_t i = 0; i < numSV; i++) {
        stream->print(F("SVs["));
        stream->print(i);
        stream->print(F("]: "));
        SVs[i]->print(stream);
      }

      stream->println();
    }
};
