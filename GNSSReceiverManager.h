class GNSSReceiverManager {
  private:
    UBXClient *client;

  public:
    GNSSReceiverManager(UBXClient *c);

    ReceiverManagerAlmanach* getAlmanach();
    ReceiverManagerAlmanach* getAlmanach(uint8_t svid);

    ReceiverManagerEphemeris* getEphemeris();
    ReceiverManagerEphemeris* getEphemeris(uint8_t svid);

    ReceiverManagerRaw* getRaw();

    ReceiverManagerSpaceVehiculeInfo* getSpaceVehiculeInfo();

    void powerRequest(uint32_t duration, uint32_t flags);
};
