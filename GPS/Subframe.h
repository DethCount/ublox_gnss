class GPSSubframe {
  public:
    static const uint8_t NB_WORDS = 10;
    uint32_t words[NB_WORDS];

    uint32_t getTelemetry() { // TLM
      return (words[0] >> 8) & 0x3FFFFF;
    }

    uint32_t getHandOverWord() { // HOW
      return (words[1] >> 8) & 0x3FFFFF;
    }
};
