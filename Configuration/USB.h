class ConfigurationUSB : public UBXMessage {
  public:
    static const uint8_t VENDOR_NAME_SIZE = 32;
    static const uint8_t PRODUCT_NAME_SIZE = 32;
    static const uint8_t SERIAL_NUMBER_SIZE = 32;

    uint16_t vendorId;
    uint16_t productId;
    uint16_t powerConsumption;
    uint16_t flags;
    char vendorString[VENDOR_NAME_SIZE];
    char productString[PRODUCT_NAME_SIZE];
    char serialNumber[SERIAL_NUMBER_SIZE];


    ConfigurationUSB() {
      msgId = MessageId::Configuration_USB;
    }

    ConfigurationUSB(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationUSB() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationUSB"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("vendorId: "));
      stream->println(vendorId);

      stream->print(F("productId: "));
      stream->println(productId);

      stream->print(F("powerConsumption: "));
      stream->println(powerConsumption);

      stream->print(F("flags: "));
      stream->println(flags, HEX);

      stream->print(F("vendorString: "));
      stream->println(vendorString);

      stream->print(F("productString: "));
      stream->println(productString);

      stream->print(F("serialNumber: "));
      stream->println(serialNumber);

      stream->println();
    }
};
