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
};
