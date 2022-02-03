class ConfigurationMessaging : public UBXMessage {
  public:
    MessageClass cfgMsgClass;
    MessageId cfgMsgId;
    uint8_t portRate[GNSS_NB_PORTS];

    ConfigurationMessaging() {
      msgId = MessageId::Configuration_Messaging;
    }

    ConfigurationMessaging(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationMessaging() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationMessaging"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      if (cfgMsgClass != MessageClass::None) {
        stream->print(F("cfgMsgClass: "));
        stream->println((uint8_t)cfgMsgClass);
      }

      if (cfgMsgId != MessageId::None) {
        stream->print(F("cfgMsgId: "));
        stream->print(highByte((uint16_t)cfgMsgId));
        stream->print(F(" "));
        stream->println(lowByte((uint16_t)cfgMsgId));
      }

      for (uint8_t i = 0; i < GNSS_NB_PORTS; i++) {
        stream->print(F("portRate["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(portRate[i]);
      }

      stream->println();
    }
};
