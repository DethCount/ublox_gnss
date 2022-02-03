class NavigationVelECEF : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t ecefVX;
    int32_t ecefVY;
    int32_t ecefVZ;
    uint32_t sAcc;

    NavigationVelECEF() {
      msgId = MessageId::Navigation_VelECEF;
    }

    NavigationVelECEF(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationVelECEF() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationVelECEF"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Earth-centered Earth-fixed X velocity: "));
      stream->print(ecefVX);
      stream->println("cm/s");

      stream->print(F("Earth-centered Earth-fixed Y velocity: "));
      stream->print(ecefVY);
      stream->println("cm/s");

      stream->print(F("Earth-centered Earth-fixed Z velocity: "));
      stream->print(ecefVZ);
      stream->println("cm/s");

      stream->print(F("Speed accuracy estimate: "));
      stream->print(sAcc);
      stream->println("cm/s");

      stream->println();
    }
};
