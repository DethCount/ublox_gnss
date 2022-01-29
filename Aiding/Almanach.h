class AidingAlmanach : public UBXMessage {
  public:
    static const short MAX_NB_DWORD = 8;

    uint32_t svid;
    uint32_t week;
    uint32_t dword[MAX_NB_DWORD];

    AidingAlmanach() {
      msgId = MessageId::Aiding_Almanach;
    }

    AidingAlmanach(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~AidingAlmanach() {}
};
