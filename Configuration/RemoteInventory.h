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

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationRemoteInventory"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("flags: "));
      stream->println(flags, HEX);

      stream->print(F("dataSize: "));
      stream->println(dataSize);

      for (uint16_t i = 0; i < dataSize; i++) {
        stream->print(F("data["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(data[i], HEX);
      }

      stream->println();
    }
};
