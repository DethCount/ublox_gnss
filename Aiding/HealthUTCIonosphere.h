class AidingHealthUTCIonosphere : public UBXMessage {
  public:
    uint32_t health;
    uint64_t utcA0;
    uint64_t utcA1;
    int32_t utcTOW;
    int16_t utcWNT;
    int16_t utcLS;
    int16_t utcWNF;
    int16_t utcDN;
    int16_t utcLSF;
    int16_t utcSpare;
    uint32_t klobA0;
    uint32_t klobA1;
    uint32_t klobA2;
    uint32_t klobA3;
    uint32_t klobB0;
    uint32_t klobB1;
    uint32_t klobB2;
    uint32_t klobB3;
    uint32_t flags;

  	AidingHealthUTCIonosphere() {
      msgId = MessageId::Aiding_HealthUTCIonosphere;
    }

  	AidingHealthUTCIonosphere(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
  	}

    virtual ~AidingHealthUTCIonosphere() {}

    bool isHealthValid() {
      return bool(flags & 0x1);
    }

    bool isUTCValid() {
      return bool(flags & 0x2);
    }

    bool isKlobValid() {
      return bool(flags & 0x4);
    }

    virtual void print(Stream* stream) {
      stream->println(F("AidingHealthUTCIonosphere"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("health: "));
      stream->println(health);

      stream->print(F("utcA0: "));
      stream->print(uint32_t(utcA0 >> 32));
      stream->print(F(" "));
      stream->println(uint32_t(utcA0));

      stream->print(F("utcA1: "));
      stream->print(uint32_t(utcA1 >> 32));
      stream->print(F(" "));
      stream->println(uint32_t(utcA1));

      stream->print(F("utcTOW: "));
      stream->println(utcTOW);

      stream->print(F("utcWNT: "));
      stream->println(utcWNT);

      stream->print(F("utcLS: "));
      stream->println(utcLS);

      stream->print(F("utcWNF: "));
      stream->println(utcWNF);

      stream->print(F("utcDN: "));
      stream->println(utcDN);

      stream->print(F("utcLSF: "));
      stream->println(utcLSF);

      stream->print(F("utcSpare: "));
      stream->println(utcSpare);

      stream->print(F("klobA0: "));
      stream->println(klobA0);

      stream->print(F("klobA1: "));
      stream->println(klobA1);

      stream->print(F("klobA2: "));
      stream->println(klobA2);

      stream->print(F("klobA3: "));
      stream->println(klobA3);

      stream->print(F("klobB0: "));
      stream->println(klobB0);

      stream->print(F("klobB1: "));
      stream->println(klobB1);

      stream->print(F("klobB2: "));
      stream->println(klobB2);

      stream->print(F("klobB3: "));
      stream->println(klobB3);

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is health valid ? : "));
      stream->println(isHealthValid());

      stream->print(F("Is UTC vaid ? : "));
      stream->println(isUTCValid());

      stream->print(F("Is klob valid ? : "));
      stream->println(isKlobValid());

      stream->println();
    }
};
