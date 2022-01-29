class MonitoringTransmitterBuffer : public MonitoringBuffer {
  public:
    MonitoringTransmitterBuffer() {
      msgId = MessageId::Monitoring_TransmitterBuffer;
    }

    MonitoringTransmitterBuffer(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringTransmitterBuffer() {}
};
