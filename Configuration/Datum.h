class ConfigurationDatum : public UBXMessage {
  public:
    static const uint8_t NAME_SIZE = 6;

    uint16_t datumNum;
    char datumName[NAME_SIZE];
    uint64_t majA;
    uint64_t flat;
    uint32_t dX;
    uint32_t dY;
    uint32_t dZ;
    uint32_t rotX;
    uint32_t rotY;
    uint32_t rotZ;
    uint32_t scale;

    ConfigurationDatum() {
      msgId = MessageId::Configuration_Datum;
    }

    ConfigurationDatum(UBXMessage *msg) : ConfigurationDatum() {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationDatum() {
      delete datumName;
    }

    virtual void print(Stream *stream) {
      stream->println(F("ConfigurationDatum"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("datumNum: "));
      stream->println(datumNum);

      stream->print(F("datumName: "));
      stream->println(datumName);

      stream->print(F("majA: "));
      stream->print(uint32_t(majA >> 32));
      stream->print(F(" "));
      stream->print(uint32_t(majA));
      stream->println(F("m"));

      stream->print(F("flat: "));
      stream->print(uint32_t(flat >> 32));
      stream->print(F(" "));
      stream->println(uint32_t(flat));

      stream->print(F("dX: "));
      stream->print(dX);
      stream->println(F("m"));

      stream->print(F("dY: "));
      stream->print(dY);
      stream->println(F("m"));

      stream->print(F("dZ: "));
      stream->print(dZ);
      stream->println(F("m"));

      stream->print(F("rotX: "));
      stream->print(rotX);
      stream->println(F("s"));

      stream->print(F("rotY: "));
      stream->print(rotY);
      stream->println(F("s"));

      stream->print(F("rotZ: "));
      stream->print(rotZ);
      stream->println(F("s"));

      stream->print(F("scale: "));
      stream->print(scale);
      stream->println(F("ppm"));

      stream->println();
    }
};
