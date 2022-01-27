class NavigationSpaceVehicule {
  public:
    uint8_t chn;
    uint8_t svid;
    byte flags;
    byte quality;
    uint8_t cno;
    int8_t elev;
    int16_t azim;
    int32_t prRes;

    NavigationSpaceVehicule() {}

    virtual ~NavigationSpaceVehicule() {}
};
