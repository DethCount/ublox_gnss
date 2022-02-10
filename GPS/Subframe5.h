class GPSSubframe5 : public GPSAlmanachSubframe {
  public:
    GPSSubframe5(bool raw = false) : GPSAlmanachSubframe(raw) {}

    void print(Stream* stream, char* name = "GPSSubframe5") {
      GPSAlmanachSubframe::print(stream, name);
    }
};
