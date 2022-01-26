class GNSSLog {
  private:
    UBXClient *client;

  public:
    static const uint16_t RETRIEVE_MAX_ENTRIES = 256;

    GNSSLog(UBXClient *c);

    UBXRequestStatus create(
      uint8_t version = 0,
      byte logCfg = 0x01,
      GNSSLogSize logSize = GNSSLogSize::MaximumSafeSize,
      uint32_t userDefinedSize = 0
    );

    UBXRequestStatus erase();

    LogFindTime* findTime(
      uint16_t year,
      uint8_t month,
      uint8_t day,
      uint8_t hour,
      uint8_t minute,
      uint8_t second,
      uint8_t version = 0
    );

    LogInfo* getInfo();

    uint32_t retrieve(
      UBXMessage *logEntries,
      uint32_t startNumber = 0,
      uint32_t entryCount = GNSSLog::RETRIEVE_MAX_ENTRIES,
      uint8_t version = 0,
      uint8_t numTries = UBX_NUM_TRIES
    );

    void log(char* str, uint8_t length);
};
