class ReceiverManagerSpaceVehicule : public UBXMessage {
  public:
    uint8_t svid;
    byte svFlag;
    int16_t azim;
    int8_t elev;
    byte age;

    ReceiverManagerSpaceVehicule() {}

    virtual ~ReceiverManagerSpaceVehicule() {}
};
