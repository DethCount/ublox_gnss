class NavigationDGPSChannel {
  public:
    uint8_t svid;
    byte flags;
    uint16_t ageC;
    uint32_t prc;
    uint32_t prrc;

    NavigationDGPSChannel() {}

    virtual ~NavigationDGPSChannel() {}
};
