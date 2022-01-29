class ReceiverManagerRawSpaceVehicule : public UBXMessage {
  public:
    uint64_t cpMes;
    uint64_t prMes;
    uint32_t doMes;
    uint8_t svid;
    int8_t mesQI;
    int8_t cno;
    uint8_t lli;

    ReceiverManagerRawSpaceVehicule() {}

    virtual ~ReceiverManagerRawSpaceVehicule() {}
};
