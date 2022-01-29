class ConfigurationNavigationExpert : public UBXMessage {
  public:
    uint16_t version;
    uint16_t mask1;
    uint8_t minSVs;
    uint8_t maxSVs;
    uint8_t minCNO;
    bool iniFix3D;
    uint16_t wknRollover;
    bool usePPP;
    uint8_t aopCfg;
    uint16_t aopOrbMaxErr;

    ConfigurationNavigationExpert() {
      msgId = MessageId::Configuration_NavigationExpert;
    }

    ConfigurationNavigationExpert(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationNavigationExpert() {}
};
