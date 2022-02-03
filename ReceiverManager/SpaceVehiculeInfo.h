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

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerSpaceVehiculeInfo"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Local week number: "));
      stream->println(week);

      stream->print(F("Number of visible space vehicules: "));
      stream->println(numVisibleSV);

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
