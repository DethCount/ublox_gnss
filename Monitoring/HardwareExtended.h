class MonitoringHardwareExtended : public UBXMessage {
  public:
    int8_t ofsI;
    uint8_t magI;
    int8_t ofsQ;
    uint8_t magQ;
    uint8_t cfgSource;
    uint32_t lowLevCfg;
    uint32_t postStatus;

    MonitoringHardwareExtended() {
      msgId = MessageId::Monitoring_HardwareExtended;
    }

    MonitoringHardwareExtended(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringHardwareExtended() {}

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringHardwareExtended"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("ofsI: "));
      stream->println(ofsI);

      stream->print(F("magI: "));
      stream->println(magI);

      stream->print(F("ofsQ: "));
      stream->println(ofsQ);

      stream->print(F("magQ: "));
      stream->println(magQ);

      stream->print(F("cfgSource: "));
      stream->println(cfgSource);

      stream->print(F("lowLevCfg: "));
      stream->println(lowLevCfg);

      stream->print(F("postStatus: "));
      stream->println(postStatus);

      stream->println();
    }
};
