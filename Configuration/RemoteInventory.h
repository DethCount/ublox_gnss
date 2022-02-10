class ConfigurationRemoteInventory : public UBXMessage {
  public:
    static const uint8_t MAX_DATA_SIZE = 30;

    byte flags;
    uint16_t dataSize;
    byte data[MAX_DATA_SIZE];

    ConfigurationRemoteInventory() {
      msgId = MessageId::Configuration_RemoteInventory;
    }

    ConfigurationRemoteInventory(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationRemoteInventory() {}

    bool isDataDumpAtStartupEnabled() {
      return bool(flags & 0x1);
    }

    bool isDataBinary() {
      return bool(flags & 0x2);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationRemoteInventory"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is data dumped at startup ? : "));
      stream->println(isDataDumpAtStartupEnabled());

      stream->print(F("Is data binary ? : "));
      stream->println(isDataBinary());

      stream->print(F("dataSize: "));
      stream->println(dataSize);

      for (uint16_t i = 0; i < dataSize; i++) {
        stream->print(F("data["));
        stream->print(i);
        stream->print(F("]: 0x"));
        stream->println(data[i], HEX);
      }

      stream->println();
    }
};
