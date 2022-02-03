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

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationNavigationExpert"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("version: "));
      stream->println(version);

      stream->print(F("mask1: "));
      stream->println(mask1, HEX);

      stream->print(F("minSVs: "));
      stream->println(minSVs);

      stream->print(F("maxSVs: "));
      stream->println(maxSVs);

      stream->print(F("minCNO: "));
      stream->print(minCNO);
      stream->println(F("dBHz"));

      stream->print(F("iniFix3D: "));
      stream->println(iniFix3D);

      stream->print(F("wknRollover: "));
      stream->println(wknRollover);

      stream->print(F("usePPP: "));
      stream->println(usePPP);

      stream->print(F("aopCfg: "));
      stream->println(aopCfg);

      stream->print(F("aopOrbMaxErr: "));
      stream->print(aopOrbMaxErr);
      stream->println(F("m"));

      stream->println();
    }
};
