enum struct DGPSStatus : uint8_t {
  None = 0x00,
  PRAndPRR = 0x01
};

class NavigationDGPS : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t age;
    int baseId;
    int baseHealth;
    uint8_t numCh;
    DGPSStatus status;
    NavigationDGPSChannel* channels[GNSS_MAX_SVID];

    NavigationDGPS() {
      msgId = MessageId::Navigation_DGPS;
    }

    NavigationDGPS(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationDGPS() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationDGPS"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Age: "));
      stream->print(age);
      stream->println(F("ms"));

      stream->print(F("DGPS basestation identifier: "));
      stream->println(baseId);

      stream->print(F("DGPS basestation health status: "));
      stream->println(baseHealth);

      stream->print(F("Number of channels: "));
      stream->println(numCh);

      stream->print(F("Status: "));
      stream->println(uint8_t(status));

      for (uint8_t i = 0; i < numCh; i++) {
        stream->print("channels[");
        stream->print(i);
        stream->println("]: ");
        channels[i]->print(stream);
      }

      stream->println();
    }
};
