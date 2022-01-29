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
};
