class ConfigurationNMEA : public UBXMessage {
  public:
    byte filter;
    uint8_t nmeaVersion;
    uint8_t numSV;
    byte flags;
    uint32_t gnssToFilter;
    uint8_t svNumbering;
    uint8_t mainTalkerId;
    uint8_t gsvTalkerId;

    ConfigurationNMEA() {
      msgId = MessageId::Configuration_NationalMarineElectronicsAssociation;
    }

    ConfigurationNMEA(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationNMEA() {}
};
