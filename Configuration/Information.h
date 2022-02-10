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

    bool isErrorEnabled(MessageClass msgClass) {
      return isErrorEnabled((uint8_t) msgClass);
    }

    bool isErrorEnabled(uint8_t msgClassId) {
      return bool(infMsgMask[msgClassId] & 0x1);
    }

    bool isWarningEnabled(MessageClass msgClass) {
      return isWarningEnabled((uint8_t) msgClass);
    }

    bool isWarningEnabled(uint8_t msgClassId) {
      return bool(infMsgMask[msgClassId] & 0x2);
    }

    bool isNoticeEnabled(MessageClass msgClass) {
      return isNoticeEnabled((uint8_t) msgClass);
    }

    bool isNoticeEnabled(uint8_t msgClassId) {
      return bool(infMsgMask[msgClassId] & 0x4);
    }

    bool isDebugEnabled(MessageClass msgClass) {
      return isDebugEnabled((uint8_t) msgClass);
    }

    bool isDebugEnabled(uint8_t msgClassId) {
      return bool(infMsgMask[msgClassId] & 0x8);
    }

    bool isTestEnabled(MessageClass msgClass) {
      return isTestEnabled((uint8_t) msgClass);
    }

    bool isTestEnabled(uint8_t msgClassId) {
      return bool(infMsgMask[msgClassId] & 0x10);
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

        stream->print(F("Mask: "));
        stream->println(infMsgMask[i], HEX);

        stream->print(F("Is error enabled ? : "));
        stream->println(isErrorEnabled(i));

        stream->print(F("Is warning enabled ? : "));
        stream->println(isWarningEnabled(i));

        stream->print(F("Is notice enabled ? : "));
        stream->println(isNoticeEnabled(i));

        stream->print(F("Is debug enabled ? : "));
        stream->println(isDebugEnabled(i));

        stream->print(F("Is test enabled ? : "));
        stream->println(isTestEnabled(i));

        stream->println();
      }

      stream->println();

      if (hasNext) {
        next->print(stream);
      }
    }
};
