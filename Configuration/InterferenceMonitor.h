class ConfigurationInterferenceMonitor : public UBXMessage {
  public:
    uint32_t config;
    uint32_t config2;

    ConfigurationInterferenceMonitor() {
      msgId = MessageId::Configuration_InterferenceMonitor;
    }

    ConfigurationInterferenceMonitor(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationInterferenceMonitor() {}
};
