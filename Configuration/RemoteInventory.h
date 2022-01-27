class ConfigurationRemoteInventory : public UBXMessage {
  public:
    static const uint8_t MAX_DATA_SIZE = 30;

    byte flags;
    uint16_t dataPayloadOffsetStart;
    uint16_t dataSize;

    ConfigurationRemoteInventory() {
      msgId = MessageId::Configuration_RemoteInventory;
    }

    ConfigurationRemoteInventory(UBXMessage& msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~ConfigurationRemoteInventory() {}
};
