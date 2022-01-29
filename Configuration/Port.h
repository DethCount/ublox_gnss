class ConfigurationPort : public UBXMessage {
  public:
    PortId portId;
    uint16_t txReady;
    uint32_t mode;
    PortRate baudRate;
    uint16_t inProtoMask;
    uint16_t outProtoMask;
    uint16_t flags;
    ConfigurationPort* next;

    ConfigurationPort() {
      msgId = MessageId::Configuration_Port;
    }

    ConfigurationPort(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationPort() {}
};
