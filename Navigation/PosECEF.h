class NavigationPosECEF : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;

    NavigationPosECEF() {
      msgId = MessageId::Navigation_PosECEF;
    }

    NavigationPosECEF(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationPosECEF() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationPosECEF"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Earth-centered Earth-fixed X: "));
      stream->print(ecefX);
      stream->println("cm");

      stream->print(F("Earth-centered Earth-fixed Y: "));
      stream->print(ecefY);
      stream->println("cm");

      stream->print(F("Earth-centered Earth-fixed Z: "));
      stream->print(ecefZ);
      stream->println("cm");

      stream->print(F("Position accuracy estimate: "));
      stream->print(pAcc);
      stream->println("cm");

      stream->println();
    }
};
