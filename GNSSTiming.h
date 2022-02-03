class GNSSTiming {
  private:
    UBXClient *client;

  public:
    GNSSTiming(UBXClient *c);

    TimingMark* getMark();
    TimingPulse* getPulse();
    TimingVerification* getVerification();

    void print(Stream* stream);
    void printMark(Stream* stream);
    void printPulse(Stream* stream);
    void printVerification(Stream* stream);
};
