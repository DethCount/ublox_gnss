class AidingEphemeris : public UBXMessage {
  public:
    uint32_t svid;
    uint32_t how;
    GPSSubframe1 *subframe1;
    GPSSubframe2 *subframe2;
    GPSSubframe3 *subframe3;

    AidingEphemeris() {}

    AidingEphemeris(UBXMessage & msg) {
        isValid = msg.isValid;
        msgId = msg.msgId;
        payloadLength = msg.payloadLength;
        memcpy(payload, msg.payload, PAYLOAD_SIZE);
        memcpy(checksum, msg.checksum, 2);
    }

    virtual ~AidingEphemeris() {}
};
