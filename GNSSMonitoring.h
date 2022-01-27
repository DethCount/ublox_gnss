class GNSSMonitoring {
  private:
    UBXClient *client;

  public:
    GNSSMonitoring(UBXClient *c);

    MonitoringHardware* getHardware();

    MonitoringHardwareExtended* getHardwareExtended();

    MonitoringIO* getIO();

    MonitoringMsgParseProcess* getMsgParseProcess();

    MonitoringReceiver* getReceiver();

    MonitoringReceiverBuffer* getReceiverBuffer();

    MonitoringTransmitterBuffer* getTransmitterBuffer();

    MonitoringVersion* getVersion();
};
