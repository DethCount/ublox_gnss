class GPSSubframe {
  public:
    static const uint8_t NB_WORDS = 8;
    static const uint8_t RAW_NB_WORDS = 10;

    bool raw;
    uint8_t nbWords;
    uint32_t *words;

    GPSSubframe(bool raw = false) {
      nbWords = raw ? RAW_NB_WORDS : NB_WORDS;
      words = new uint32_t[nbWords];
    }

    virtual void print(Stream* stream, char* name = "GPSSubframe") {
      stream->println(name);

      for (uint8_t i = 0; i < nbWords; i++) {
        stream->print(F("word["));
        stream->print(i);
        stream->print(F("]: 0x"));
        stream->println(words[i], HEX);
      }

      stream->println();
    }
};
