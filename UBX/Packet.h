class UBXPacket : public UBXMessage {
  public:
    static const int PAYLOAD_SIZE = 0x0FFF;

    uint16_t payloadLength;
    byte checksum[2] = { 0x00, 0x00 };
    byte payload[PAYLOAD_SIZE];

    virtual ~UBXPacket() {}
};
