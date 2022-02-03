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
    bool hasNext;
    MonitoringIO* next;

    MonitoringIO() {
      msgId = MessageId::Monitoring_IO;
    }

    MonitoringIO(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringIO() {}

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringIO"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("rxBytes: "));
      stream->print(rxBytes);
      stream->println(F("bytes"));

      stream->print(F("txBytes: "));
      stream->print(txBytes);
      stream->println(F("bytes"));

      stream->print(F("parityErrs: "));
      stream->println(parityErrs);

      stream->print(F("framingErrs: "));
      stream->println(framingErrs);

      stream->print(F("overrunErrs: "));
      stream->println(overrunErrs);

      stream->print(F("breakCond: "));
      stream->println(breakCond);

      stream->print(F("rxBusy: "));
      stream->println(rxBusy);

      stream->print(F("txBusy: "));
      stream->println(txBusy);

      stream->println();

      if (hasNext) {
        next->print(stream);
      }
    }
};
