class MonitoringReceiver : public UBXMessage {
  public:
    byte flags;

    MonitoringReceiver() {
      msgId = MessageId::Monitoring_Receiver;
    }

    MonitoringReceiver(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~MonitoringReceiver() {}
};
