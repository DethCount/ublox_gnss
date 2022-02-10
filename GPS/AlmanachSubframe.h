class GPSAlmanachSubframe : public GPSSubframe {
  public:
    GPSAlmanachSubframe(bool raw = false) : GPSSubframe(raw) {}

    uint8_t getDataId() {
      return uint8_t((words[raw ? 0 : 2] >> 22) & 0x3);
    }

    uint8_t getPage() {
      return uint8_t((words[raw ? 0 : 2] >> 16) & 0x3F);
    }

    void print(Stream* stream, char* name = "GPSAlmanachSubframe") {
      GPSSubframe::print(stream, name);

      stream->print(F("Data id"));
      stream->println(getDataId());

      stream->print(F("SV (PAGE) ID"));
      stream->println(getPage());

      stream->println();
    }
};
