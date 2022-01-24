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
};
