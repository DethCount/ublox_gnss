class ConfigurationInterferenceMonitor : public UBXMessage {
  public:
    uint32_t config;
    uint32_t config2;

    ConfigurationInterferenceMonitor() {
      msgId = MessageId::Configuration_InterferenceMonitor;
    }

    ConfigurationInterferenceMonitor(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationInterferenceMonitor() {}

    uint8_t getBroadbandJammingDetectionThreshold() {
      return uint8_t(config & 0xF);
    }

    uint8_t getContinuousWaveJammingDetectionThreshold() {
      return (uint8_t(config) >> 4) & 0x1F;
    }

    uint32_t getReserved1() {
      return (config >> 9) & 0x3FFFFF;
    }

    bool isEnabled() {
      return bool(config & 0x400000);
    }

    uint16_t getReserved2() {
      return uint16_t(config2) & 0xFFF;
    }

    bool isPassiveAntenna() {
      return bool((config2 >> 12) & 0x1);
    }

    bool isActiveAntenna() {
      return bool((config2 >> 13) & 0x1);
    }

    uint32_t getReserved3() {
      return (config2 >> 14) & 0xFFFFFFF;
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationInterferenceMonitor"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("Configuration: 0x"));
      stream->println(config, HEX);

      stream->print(F("Broadband jamming detection threshold: "));
      stream->print(getBroadbandJammingDetectionThreshold());
      stream->println("dB");

      stream->print(F("Continuous wave jamming detection threshold: "));
      stream->print(getContinuousWaveJammingDetectionThreshold());
      stream->println("dB");

      stream->print(F("Reserved (1) algorithm settings: "));
      stream->println(getReserved1());

      stream->print(F("Is enabled ? : "));
      stream->println(isEnabled());

      stream->print(F("Configuration flags 2: 0x"));
      stream->println(config2, HEX);

      stream->print(F("Reserved (2) algorithm settings: "));
      stream->println(getReserved2());

      stream->print(F("Is passive antenna ? : "));
      stream->println(isPassiveAntenna());

      stream->print(F("Is active antenna ? : "));
      stream->println(isActiveAntenna());

      stream->print(F("Reserved (3) algorithm settings: "));
      stream->println(getReserved3());

      stream->println();
    }
};
