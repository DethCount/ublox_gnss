class ConfigurationReceiver : public UBXMessage {
  public:
    LowPowerMode lpMode;

    ConfigurationReceiver() {
      msgId = MessageId::Configuration_Receiver;
    }

    ConfigurationReceiver(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationReceiver() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationReceiver"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("lpMode: "));
      stream->println(uint8_t(lpMode));

      stream->println();
    }
};
