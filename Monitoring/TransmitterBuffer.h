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

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringTransmitterBuffer"));

      MonitoringBuffer::print(stream);
    }
};
