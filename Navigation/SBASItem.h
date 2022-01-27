class NavigationSBASItem {
  public:
    uint8_t svid;
    byte flags;
    byte udre;
    SBASSystem svSys;
    byte svService;
    // reserved1 U1
    int16_t prc;
    // reserved2 U2
    int16_t ic;

    NavigationSBASItem() {}

    virtual ~NavigationSBASItem() {}
};
