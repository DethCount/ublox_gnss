class AidingAlmanach : public UBXMessage {
  public:
    static const short MAX_NB_DWORD = 8;

    uint32_t svid;
    uint32_t week;
    uint32_t dword[MAX_NB_DWORD];

    AidingAlmanach() {}

    AidingAlmanach(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~AidingAlmanach() {}
};
