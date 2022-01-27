class MonitoringReceiverBuffer : public MonitoringBuffer {
  public:
    MonitoringReceiverBuffer() {
      msgId = MessageId::Monitoring_ReceiverBuffer;
    }
};
