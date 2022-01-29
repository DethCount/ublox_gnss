class GNSSTiming {
  private:
    UBXClient *client;

  public:
    GNSSTiming(UBXClient *c);

    TimingMark* getMark();
    TimingPulse* getPulse();
    TimingVerification* getVerification();
};
