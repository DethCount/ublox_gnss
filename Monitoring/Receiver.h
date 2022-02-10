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

    bool isAwake() {
      return bool(flags & 0x1);
    }

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringReceiver"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("flags: 0x"));
      stream->print(flags, HEX);

      stream->print(F("Is awake ? (not in backup mode) : "));
      stream->print(isAwake());
    }
};
