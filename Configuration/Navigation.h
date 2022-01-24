class ConfigurationNavigation : public UBXMessage
{
  public:
    uint16_t mask;
    NavigationMode dynModel;
    GNSSFixType fixMode;
    double fixedAlt;
    double fixedAltVar;
    int8_t minElev;
    uint8_t drLimit;
    double pDOP;
    double tDOP;
    uint16_t pAcc;
    uint16_t tAcc;
    uint8_t staticHoldThresh;
    uint8_t dgpsTimeOut;
    uint8_t cnoThreshNumSVs;
    uint8_t cnoThresh;

    ConfigurationNavigation() {}

    ConfigurationNavigation(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationNavigation() {}
};
