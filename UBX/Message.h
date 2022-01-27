class UBXMessage {
  public:
    static const int PAYLOAD_SIZE = 0x0FFF;
    bool isValid;
    MessageId msgId;
    uint16_t payloadLength;
    byte payload[PAYLOAD_SIZE];
    byte checksum[2] = { 0x00, 0x00 };

    virtual ~UBXMessage() {}
};
