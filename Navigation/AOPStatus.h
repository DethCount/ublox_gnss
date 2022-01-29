enum struct AOPStatus : uint8_t {
  Idle = 0x00,
  Running = 0x01
};

class NavigationAOPStatus : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t aopCfg;
    AOPStatus status;
    // reserved0 U1
    // reserved1 U1
    uint32_t availGPS;
    // reserved2 U4
    // reserved3 U4

    NavigationAOPStatus() {
      msgId = MessageId::Navigation_AOPStatus;
    }

    NavigationAOPStatus(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationAOPStatus() {}
};
