class NavigationSOL : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t fTOW;
    int16_t week;
    GNSSFixType gpsFix;
    byte flags;
    int32_t ecefX;
    int32_t ecefY;
    int32_t ecefZ;
    uint32_t pAcc;
    int32_t ecefVX;
    int32_t ecefVY;
    int32_t ecefVZ;
    uint32_t sAcc;
    double pDOP;
    // reserved1 U1
    uint8_t numSV;
    // reserved2 U4

    NavigationSOL() {
      msgId = MessageId::Navigation_SOL;
    }

    NavigationSOL(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationSOL() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationSOL"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("GPS nanoseconds: "));
      stream->print(fTOW);
      stream->println(F("ns"));

      stream->print(F("GPS week number: "));
      stream->println(week);

      stream->print(F("GPS fix type: "));
      stream->println(uint8_t(gpsFix));

      stream->print(F("Flags: "));
      stream->println(flags, HEX);

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

      stream->print(F("Position dillution of precision: "));
      stream->println(pDOP);

      stream->print(F("Number of space vehicules used: "));
      stream->println(numSV, HEX);

      stream->println();
    }
};
