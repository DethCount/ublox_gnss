class ConfigurationInformation : public UBXMessage {
  public:
    static const uint8_t MAX_NB_MSG_CLASS = 6;

    GNSSProtocol protocolId;
    byte infMsgMask[MAX_NB_MSG_CLASS];
    bool hasNext;
    ConfigurationInformation* next;

    ConfigurationInformation() {
      msgId = MessageId::Configuration_Information;
    }

    ConfigurationInformation(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationInformation() {
      delete infMsgMask;
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationInformation"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("protocolId: "));
      stream->println((uint8_t)protocolId);

      for (uint8_t i = 0; i < MAX_NB_MSG_CLASS; i++) {
        stream->print(F("infMsgMask["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(infMsgMask[i]);
      }

      stream->println();

      if (hasNext) {
        next->print(stream);
      }
    }
};
