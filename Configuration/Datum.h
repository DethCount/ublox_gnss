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

    ConfigurationDatum(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationDatum() {}
};
