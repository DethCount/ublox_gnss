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

    bool applySVsLimitationsSettings() {
      return bool(mask1 & 0x1);
    }

    bool applyCarrierNoiseRatioLimitationsSettings() {
      return bool(mask1 & 0x2);
    }

    bool applyInitialFixSettings() {
      return bool(mask1 & 0x4);
    }

    bool applyWeekNumberRolloverSettings() {
      return bool(mask1 & 0x8);
    }

    bool applyPrecisePointPositioningSettings() {
      return bool(mask1 & 0x10);
    }

    bool applyAOPSettings() {
      return bool(mask1 & 0x20);
    }

    bool isAOPEnabled() {
      return bool(aopCfg & 0x1);
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

      stream->print(F("mask1: 0x"));
      stream->println(mask1, HEX);

      stream->print(F("Apply SVs limitations settings: "));
      stream->println(applySVsLimitationsSettings());

      stream->print(F("Apply Carrrier/Noise limitations settings: "));
      stream->println(applyCarrierNoiseRatioLimitationsSettings());

      stream->print(F("Apply initial position fix settings: "));
      stream->println(applyInitialFixSettings());

      stream->print(F("Apply week number rollover settings: "));
      stream->println(applyWeekNumberRolloverSettings());

      stream->print(F("Apply Precise Point Positioning settings: "));
      stream->println(applyPrecisePointPositioningSettings());

      stream->print(F("Apply AOP settings: "));
      stream->println(applyAOPSettings());

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

      stream->print(F("Is AOP enabled ?: "));
      stream->println(isAOPEnabled());

      stream->print(F("aopOrbMaxErr: "));
      stream->print(aopOrbMaxErr);
      stream->println(F("m"));

      stream->println();
    }
};
