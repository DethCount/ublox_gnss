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

    ConfigurationUSB(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationUSB() {}
};
