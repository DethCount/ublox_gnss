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

    bool useAOP() {
      return bool(aopCfg & 0x1);
    }

    virtual void print(Stream* stream) {
      stream->println(F("NavigationAOPStatus"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("AOP configuration flags: 0x"));
      stream->println(aopCfg, HEX);

      stream->print(F("AOP enabled flag: "));
      stream->println(useAOP());

      stream->print(F("Status: "));
      stream->println(uint8_t(aopCfg));

      stream->print(F("Data availability mask for GPS SVs: 0x"));
      stream->println(availGPS, HEX);

      stream->println();
    }
};
