class ConfigurationMessaging : public UBXMessage {
  public:
    MessageClass msgClass;
    MessageId msgId;
    uint8_t rate;

    ConfigurationMessaging() {
      msgId = MessageId::Configuration_Messaging;
    }

    ConfigurationMessaging(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationMessaging() {}
};
