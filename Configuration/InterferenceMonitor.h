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

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationInterferenceMonitor"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("config: "));
      stream->println(config);

      stream->print(F("config2: "));
      stream->println(config2);

      stream->println();
    }
};
