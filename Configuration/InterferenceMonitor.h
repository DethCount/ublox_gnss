class ConfigurationInterferenceMonitor : public UBXMessage
{
  public:
    uint32_t config;
    uint32_t config2;

    ConfigurationInterferenceMonitor() {}

    ConfigurationInterferenceMonitor(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationInterferenceMonitor() {}
};
