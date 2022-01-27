class AidingEphemeris : public UBXMessage {
  public:
    static const uint8_t WORDS_PER_SUBFRAME = 8;

    uint32_t svid;
    uint32_t how;
    uint32_t subframe1[WORDS_PER_SUBFRAME];
    uint32_t subframe2[WORDS_PER_SUBFRAME];
    uint32_t subframe3[WORDS_PER_SUBFRAME];

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
