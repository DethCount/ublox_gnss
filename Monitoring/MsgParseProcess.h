class MonitoringMsgParseProcess : public UBXMessage {
  public:
    uint16_t msgs[GNSS_NB_PORTS][GNSS_NB_PROTOCOLS];
    uint32_t skipped[GNSS_NB_PORTS];

    MonitoringMsgParseProcess() {
      msgId = MessageId::Monitoring_MsgParseProcess;
    }

    MonitoringMsgParseProcess(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~MonitoringMsgParseProcess() {}
};
