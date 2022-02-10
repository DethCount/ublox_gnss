class MonitoringTransmitterBuffer : public MonitoringBuffer {
  public:
    uint8_t tUsage;
    uint8_t tPeakUsage;
    byte errors;

    MonitoringTransmitterBuffer() {
      msgId = MessageId::Monitoring_TransmitterBuffer;
    }

    MonitoringTransmitterBuffer(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringTransmitterBuffer() {}

    uint8_t getTargetBufferLimitReached() {
      return errors & 0x3F;
    }

    bool hasMemoryAllocationError() {
      return bool(errors & 0x40);
    }

    bool hasAllocationError() {
      return bool(errors & 0x80);
    }

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringTransmitterBuffer"));

      MonitoringBuffer::print(stream);

      stream->print(F("Maximum usage of transmitter buffer during the last sysmon period for all targets : "));
      stream->print(tUsage);
      stream->println(F("%"));

      stream->print(F("Maximum usage of transmitter buffer for all targets : "));
      stream->print(tPeakUsage);
      stream->println(F("%"));

      stream->print(F("Errors : 0x"));
      stream->println(errors);

      stream->print(F("Buffer limit of corresponding target reached : "));
      stream->println(getTargetBufferLimitReached());

      stream->print(F("Has memory allocation error ? : "));
      stream->println(hasMemoryAllocationError());

      stream->print(F("Has allocation error (TX buffer full) ? : "));
      stream->println(hasAllocationError());

      stream->println();
    }
};
