class MonitoringMsgParseProcess : public UBXMessage {
  public:
    uint16_t msgs[GNSS_NB_PORTS][GNSS_NB_PROTOCOLS];
    uint32_t skipped[GNSS_NB_PORTS];

    MonitoringMsgParseProcess() {
      msgId = MessageId::Monitoring_MsgParseProcess;
    }

    MonitoringMsgParseProcess(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringMsgParseProcess() {}

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringMsgParseProcess"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      for (uint8_t i = 0; i < GNSS_NB_PORTS; i++) {
        for (uint8_t j = 0; j < GNSS_NB_PROTOCOLS; j++) {
          stream->print(F("msgs["));
          stream->print(i);
          stream->print(F("]["));
          stream->print(j);
          stream->print(F("]: "));
          stream->println(msgs[i][j]);
        }
      }

      for (uint8_t i = 0; i < GNSS_NB_PORTS; i++) {
        stream->print(F("skipped["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(skipped[i]);
      }

      stream->println();
    }
};
