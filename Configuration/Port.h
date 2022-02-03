class ConfigurationPort : public UBXMessage {
  public:
    PortId portId;
    uint16_t txReady;
    uint32_t mode;
    PortRate baudRate;
    uint16_t inProtoMask;
    uint16_t outProtoMask;
    uint16_t flags;
    bool hasNext;
    ConfigurationPort* next;

    ConfigurationPort() {
      msgId = MessageId::Configuration_Port;
    }

    ConfigurationPort(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationPort() {}

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationPort"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("portId: "));
      stream->println((uint8_t)portId);

      stream->print(F("txReady: "));
      stream->println(txReady);

      stream->print(F("mode: "));
      stream->println(mode);

      stream->print(F("baudRate: "));
      stream->print((uint32_t)baudRate);
      stream->println(F("bauds"));

      stream->print(F("inProtoMask: "));
      stream->println(inProtoMask, HEX);

      stream->print(F("outProtoMask: "));
      stream->println(outProtoMask, HEX);

      stream->print(F("flags: "));
      stream->println(flags, HEX);

      stream->println();

      if (hasNext) {
        next->print(stream);
      }
    }
};
