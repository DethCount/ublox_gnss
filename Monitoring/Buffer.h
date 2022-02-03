class MonitoringBuffer : public UBXMessage {
  public:
    uint16_t pending[GNSS_NB_PORTS];
    uint8_t usage[GNSS_NB_PORTS];
    uint8_t peakUsage[GNSS_NB_PORTS];

    MonitoringBuffer() {}

    MonitoringBuffer(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringBuffer() {}

    void print(Stream* stream) {
      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      for (uint8_t i = 0; i < GNSS_NB_PORTS; i++) {
        stream->print(F("pending["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(pending[i]);

        stream->print(F("usage["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(usage[i]);

        stream->print(F("peakUsage["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(peakUsage[i]);
      }

      stream->println();
    }
};
