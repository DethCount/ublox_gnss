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
};
