class MonitoringVersion : public UBXMessage {
  public:
    static const uint8_t SOFTWARE_VERSION_SIZE = 30;
    static const uint8_t HARDWARE_VERSION_SIZE = 10;
    static const uint8_t MAX_NB_EXTENSION = 0x10;
    static const uint8_t EXTENSION_SIZE = 30;

    char swVersion[SOFTWARE_VERSION_SIZE];
    char hwVersion[HARDWARE_VERSION_SIZE];
    uint8_t nbExtensions;
    char extension[MAX_NB_EXTENSION][EXTENSION_SIZE];

    MonitoringVersion() {
      msgId = MessageId::Monitoring_Version;
    }

    MonitoringVersion(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~MonitoringVersion() {}

    virtual void print(Stream* stream) {
      stream->println(F("MonitoringVersion"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("swVersion: "));
      stream->println(swVersion);

      stream->print(F("hwVersion: "));
      stream->println(hwVersion);

      for (uint8_t i = 0; i < nbExtensions; i++) {
        stream->print(F("extension["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(extension[i]);
      }

      stream->println();
    }
};
