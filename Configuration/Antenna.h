class ConfigurationAntenna : public UBXMessage {
  public:
    uint16_t flags;
    uint16_t pins;

    ConfigurationAntenna() {
      msgId = MessageId::Configuration_Antenna;
    }

    ConfigurationAntenna(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationAntenna() {}

    bool isSupplyVoltageControlSignalEnabled() {
      return bool(flags & 0x1);
    }

    bool isShortCircuitDetectionEnabled() {
      return bool(flags & 0x2);
    }

    bool isOpenCircuitDetectionEnabled() {
      return bool(flags & 0x4);
    }

    bool powerDownOnShortCircuit() {
      return bool(flags & 0x8);
    }

    bool isShortCircuitRecoveryEnabled() {
      return bool(flags & 0x10);
    }

    uint8_t getPinSwitch() {
      return uint8_t(pins & 0x1F);
    }

    uint8_t getPinSCD() {
      return uint8_t((pins >> 5) & 0x1F);
    }

    uint8_t getPinOCD() {
      return uint8_t((pins >> 10) & 0x1F);
    }

    bool isReconfiguration() {
      return bool(pins & 0x8000);
    }

    virtual void print(Stream *stream) {
      stream->println(F("ConfigurationAntenna"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is supply voltage control signal enabled ? : "));
      stream->println(isSupplyVoltageControlSignalEnabled());

      stream->print(F("Is short circuit detection enabled ? : "));
      stream->println(isShortCircuitDetectionEnabled());

      stream->print(F("Is open circuit detection enabled ? : "));
      stream->println(isOpenCircuitDetectionEnabled());

      stream->print(F("Power down when a short circuit is detected ? : "));
      stream->println(powerDownOnShortCircuit());

      stream->print(F("Is short circuit recovery enabled ? : "));
      stream->println(isShortCircuitRecoveryEnabled());

      stream->print(F("pins: b"));
      stream->println(pins, BIN);

      stream->print(F("PIO-pin used for switching antenna supply: "));
      stream->println(getPinSwitch());

      stream->print(F("PIO-pin used for detecting a short in the antenna supply: "));
      stream->println(getPinSCD());

      stream->print(F("PIO-pin used for detecting open/not connected antenna: "));
      stream->println(getPinOCD());

      stream->print(F("Update pin configuration ? : "));
      stream->println(isReconfiguration());

      stream->println();
    }
};
