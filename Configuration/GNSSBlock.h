class ConfigurationGNSSBlock {
  public:
    uint8_t gnssId;
    uint8_t resTrkCh;
    uint8_t maxTrkCh;
    uint32_t flags;

    ConfigurationGNSSBlock() {}

    virtual ~ConfigurationGNSSBlock() {}

    bool isEnabled() {
      return bool(flags & 0x1);
    }

    virtual void print(Stream *stream) {
      stream->println(F("ConfigurationGNSSBlock"));

      stream->print(F("gnssId: "));
      stream->println(gnssId);

      stream->print(F("resTrkCh: "));
      stream->println(resTrkCh);

      stream->print(F("maxTrkCh: "));
      stream->println(maxTrkCh);

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is enabled ? : "));
      stream->println(isEnabled());

      stream->println();
    }
};
