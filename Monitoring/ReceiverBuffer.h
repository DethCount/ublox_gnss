class MonitoringReceiverBuffer : public MonitoringBuffer {
  public:
    MonitoringReceiverBuffer() {
      msgId = MessageId::Monitoring_ReceiverBuffer;
    }

    MonitoringReceiverBuffer(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringReceiverBuffer() {}

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringReceiverBuffer"));

      MonitoringBuffer::print(stream);
    }
};
