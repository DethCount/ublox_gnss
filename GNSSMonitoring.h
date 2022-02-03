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

    void GNSSMonitoring::print(Stream* stream);
    void GNSSMonitoring::printHardware(Stream* stream);
    void GNSSMonitoring::printHardwareExtended(Stream* stream);
    void GNSSMonitoring::printIO(Stream* stream);
    void GNSSMonitoring::printMsgParseProcess(Stream* stream);
    void GNSSMonitoring::printReceiver(Stream* stream);
    void GNSSMonitoring::printReceiverBuffer(Stream* stream);
    void GNSSMonitoring::printTransmitterBuffer(Stream* stream);
    void GNSSMonitoring::printVersion(Stream* stream);
};
