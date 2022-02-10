class NavigationSpaceVehiculeInfo : public UBXMessage {
  public:
    uint32_t iTOW;
    uint8_t numCh;
    byte globalFlags;
    // reserved2 U2
    NavigationSpaceVehicule* spaceVehicules[GNSS_MAX_SVID];

    NavigationSpaceVehiculeInfo() {
      msgId = MessageId::Navigation_SpaceVehiculeInfo;
    }

    NavigationSpaceVehiculeInfo(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    uint8_t getChipGeneration() {
      return uint8_t(globalFlags & 0x7);
    }

    virtual ~NavigationSpaceVehiculeInfo() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationSpaceVehiculeInfo"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Flags: 0x"));
      stream->println(globalFlags, HEX);

      stream->print(F("Chip generation: "));
      stream->println(getChipGeneration());

      stream->print(F("Number of channels: "));
      stream->println(numCh);

      for (uint8_t i = 0; i < numCh; i++) {
        stream->print(F("spaceVehicules["));
        stream->print(i);
        stream->println(F("]: "));
        spaceVehicules[i]->print(stream);
      }

      stream->println();
    }
};
