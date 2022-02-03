#define UBX_PAYLOAD_SIZE 0x3FF //0x0FFF

class UBXPacket {
  public:
    bool isValid;
    MessageId msgId;
    uint16_t payloadLength = 0;
    byte checksum[2] = {0x00, 0x00};
    byte payload[UBX_PAYLOAD_SIZE];

    UBXPacket() {}

    virtual ~UBXPacket() {
      // delete[] checksum;
      // delete[] payload;
    }
};
