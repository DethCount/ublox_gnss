class ConfigurationGNSS : public UBXMessage {
  public:
    static const uint8_t MAX_NB_BLOCKS = 0xF;

    uint8_t msgVer;
    uint8_t numTrkChHw;
    uint8_t numTrkChUse;
    uint8_t numConfigBlocks;
    ConfigurationGNSSBlock* blocks[MAX_NB_BLOCKS];

    ConfigurationGNSS() {
      msgId = MessageId::Configuration_GlobalNavigationSatelliteSystem;
    }

    ConfigurationGNSS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationGNSS() {
      delete[] blocks;
    }

    virtual void print(Stream *stream) {
      stream->println(F("ConfigurationGNSS"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("msgVer: "));
      stream->println(msgVer);

      stream->print(F("numTrkChHw: "));
      stream->println(numTrkChHw);

      stream->print(F("numTrkChUse: "));
      stream->println(numTrkChUse);

      stream->print(F("numConfigBlocks: "));
      stream->println(numConfigBlocks);

      for (uint8_t i = 0; i < numConfigBlocks; i++) {
        stream->print(F("blocks["));
        stream->print(i);
        stream->println(F("]:"));

        blocks[i]->print(stream);
      }

      stream->println();
    }
};
