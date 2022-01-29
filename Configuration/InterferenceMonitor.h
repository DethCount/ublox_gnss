class ConfigurationInterferenceMonitor : public UBXMessage {
  public:
    uint32_t config;
    uint32_t config2;

    ConfigurationInterferenceMonitor() {
      msgId = MessageId::Configuration_InterferenceMonitor;
    }

    ConfigurationInterferenceMonitor(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationInterferenceMonitor() {}
};
