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
      isValid = false;
      msgId = MessageId::None;
      payloadLength = 0;
    }

    NavigationAOPStatus(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationAOPStatus() {}
};
