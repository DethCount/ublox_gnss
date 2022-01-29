class MonitoringReceiver : public UBXMessage {
  public:
    byte flags;

    MonitoringReceiver() {
      msgId = MessageId::Monitoring_Receiver;
    }

    MonitoringReceiver(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringReceiver() {}
};
