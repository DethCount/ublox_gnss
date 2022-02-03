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

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringReceiver"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("flags: "));
      stream->print(flags, HEX);
    }
};
