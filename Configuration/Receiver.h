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
};
