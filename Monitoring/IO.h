class MonitoringIO : public UBXMessage {
  public:
    uint32_t rxBytes;
    uint32_t txBytes;
    uint16_t parityErrs;
    uint16_t framingErrs;
    uint16_t overrunErrs;
    uint16_t breakCond;
    uint8_t rxBusy;
    uint8_t txBusy;
    MonitoringIO* next;

    MonitoringIO() {
      msgId = MessageId::Monitoring_IO;
    }

    MonitoringIO(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringIO() {}
};
