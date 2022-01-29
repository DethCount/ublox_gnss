class MonitoringVersion : public UBXMessage {
  public:
    static const uint8_t SOFTWARE_VERSION_SIZE = 30;
    static const uint8_t HARDWARE_VERSION_SIZE = 10;
    static const uint8_t MAX_NB_EXTENSION = 0xFF;
    static const uint8_t EXTENSION_SIZE = 30;

    char swVersion[SOFTWARE_VERSION_SIZE];
    char hwVersion[HARDWARE_VERSION_SIZE];
    char extension[MAX_NB_EXTENSION][EXTENSION_SIZE];

    MonitoringVersion() {
      msgId = MessageId::Monitoring_Version;
    }

    MonitoringVersion(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringVersion() {}
};
