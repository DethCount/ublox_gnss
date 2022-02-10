class ConfigurationNavigation : public UBXMessage {
  public:
    uint16_t mask;
    NavigationMode dynModel;
    GNSSFixType fixMode;
    double fixedAlt;
    double fixedAltVar;
    int8_t minElev;
    uint8_t drLimit;
    double pDOP;
    double tDOP;
    uint16_t pAcc;
    uint16_t tAcc;
    uint8_t staticHoldThresh;
    uint8_t dgpsTimeOut;
    uint8_t cnoThreshNumSVs;
    uint8_t cnoThresh;

    ConfigurationNavigation() {
      msgId = MessageId::Configuration_Navigation;
    }

    ConfigurationNavigation(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationNavigation() {}

    bool applyDynamicModelSettings() {
      return bool(mask & 0x1);
    }

    bool applyMinElevationSettings() {
      return bool(mask & 0x2);
    }

    bool applyFixModeSettings() {
      return bool(mask & 0x4);
    }

    bool applyDrLimitSettings() {
      return bool(mask & 0x8);
    }

    bool applyPositionMaskSettings() {
      return bool(mask & 0x10);
    }

    bool applyTimeMaskSettings() {
      return bool(mask & 0x20);
    }

    bool applyStaticHoldSettings() {
      return bool(mask & 0x40);
    }

    bool applyDGPSSettings() {
      return bool(mask & 0x80);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationNavigation"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("mask: 0x"));
      stream->println(mask, HEX);

      stream->print(F("Apply dynamic model settings ? : "));
      stream->println(applyDynamicModelSettings());

      stream->print(F("Apply min elevation settings ? : "));
      stream->println(applyMinElevationSettings());

      stream->print(F("Apply fix mode settings ? : "));
      stream->println(applyFixModeSettings());

      stream->print(F("Apply drLimit settings ? : "));
      stream->println(applyDrLimitSettings());

      stream->print(F("Apply position mask settings ? : "));
      stream->println(applyPositionMaskSettings());

      stream->print(F("Apply time mask settings ? : "));
      stream->println(applyTimeMaskSettings());

      stream->print(F("Apply static hold settings ? : "));
      stream->println(applyStaticHoldSettings());

      stream->print(F("Apply DGPS settings ? : "));
      stream->println(applyDGPSSettings());

      stream->print(F("dynModel: 0x"));
      stream->println((byte)dynModel, HEX);

      stream->print(F("fixMode: 0x"));
      stream->println((byte)fixMode, HEX);

      stream->print(F("fixedAlt: "));
      stream->print(fixedAlt);
      stream->println(F("m"));

      stream->print(F("fixedAltVar: "));
      stream->print(fixedAltVar);
      stream->println(F("m^2"));

      stream->print(F("minElev: "));
      stream->print(minElev);
      stream->println(F("°"));

      stream->print(F("drLimit: "));
      stream->println(drLimit);

      stream->print(F("pDOP: "));
      stream->println(pDOP);

      stream->print(F("tDOP: "));
      stream->println(tDOP);

      stream->print(F("pAcc: "));
      stream->print(pAcc);
      stream->println(F("m"));

      stream->print(F("tAcc: "));
      stream->print(tAcc);
      stream->println(F("m"));

      stream->print(F("staticHoldThresh: "));
      stream->print(staticHoldThresh);
      stream->println(F("cm/s"));

      stream->print(F("dgpsTimeOut: "));
      stream->print(dgpsTimeOut);
      stream->println(F("s"));

      stream->print(F("cnoThreshNumSVs: "));
      stream->println(cnoThreshNumSVs);

      stream->print(F("cnoThresh: "));
      stream->print(cnoThresh);
      stream->println(F("dBHz"));

      stream->println();
    }
};
