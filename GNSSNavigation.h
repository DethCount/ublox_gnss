class GNSSNavigation {
  private:
    UBXClient *client;

  public:
    GNSSNavigation(UBXClient *c);

    NavigationAOPStatus* getAOPStatus();
    NavigationClock* getClock();
    NavigationDGPS* getDGPS();
    NavigationDOP* getDOP();
    NavigationPosECEF* getPosECEF();
    NavigationPosLLH* getPosLLH();
    NavigationPosVT* getPosVT();
    NavigationSBAS* getSBAS();
    NavigationSOL* getSOL();
    NavigationStatus* getStatus();
    NavigationSpaceVehiculeInfo* getSpaceVehiculeInfo();
    NavigationTimeGPS* getTimeGPS();
    NavigationTimeUTC* getTimeUTC();
    NavigationVelECEF* getVelECEF();
    NavigationVelNED* getVelNED();

    void print(Stream* stream);
    void printAOPStatus(Stream* stream);
    void printClock(Stream* stream);
    void printDGPS(Stream* stream);
    void printDOP(Stream* stream);
    void printPosECEF(Stream* stream);
    void printPosLLH(Stream* stream);
    void printPosVT(Stream* stream);
    void printSBAS(Stream* stream);
    void printSOL(Stream* stream);
    void printStatus(Stream* stream);
    void printSpaceVehiculeInfo(Stream* stream);
    void printTimeGPS(Stream* stream);
    void printTimeUTC(Stream* stream);
    void printVelECEF(Stream* stream);
    void printVelNED(Stream* stream);
};
