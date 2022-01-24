class GNSSAiding {
  private:
    UBXClient *client;

  public:
    GNSSAiding(UBXClient *c);

    AidingAlmanach* getAlmanach();
    AidingAlmanach* getAlmanach(uint8_t svid);

    AidingAlmanachPlus* getAlmanachPlus(
      uint8_t idSize,
      uint8_t type,
      uint16_t ofs,
      uint16_t size,
      uint16_t fileId,
      uint16_t dataSize,
      uint8_t id1,
      uint8_t id2,
      uint16_t id3
    );

    AidingAOP* getAOP();
    AidingAOP* getAOP(uint8_t svid);

    void getData();

    AidingEphemeris* getEphemeris();
    AidingEphemeris* getEphemeris(uint8_t svid);

    AidingHealthUTCIonosphere* getHealthUTCIonosphere();

    AidingInit* getInit();

    void requestAll();
};
