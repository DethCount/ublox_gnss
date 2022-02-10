class GPSSubframe4 : public GPSAlmanachSubframe {
  public:
    GPSSubframe4(bool raw = false) : GPSAlmanachSubframe(raw) {}

    void print(Stream* stream, char* name = "GPSSubframe4") {
      GPSAlmanachSubframe::print(stream, name);
    }
};
