class MonitoringTransmitterBuffer : public MonitoringBuffer {
  public:
    MonitoringTransmitterBuffer() {
      msgId = MessageId::Monitoring_TransmitterBuffer;
    }
};
