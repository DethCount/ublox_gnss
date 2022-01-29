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
};
