class NavigationPosLLH : public UBXMessage {
  public:
    uint32_t iTOW;
    double longitude;
    double latitude;
    int32_t height;
    int32_t hMSL; // elevation above sea level
    uint32_t hAcc;
    uint32_t vAcc;

    NavigationPosLLH() {
      msgId = MessageId::Navigation_PosLLH;
    }

    NavigationPosLLH(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationPosLLH() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationPosLLH"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Longitude: "));
      stream->print(longitude);
      stream->println("°");

      stream->print(F("Latitude: "));
      stream->print(latitude);
      stream->println("°");

      stream->print(F("Height above ellipsoid: "));
      stream->print(height);
      stream->println("mm");

      stream->print(F("Height above mean sea level: "));
      stream->print(hMSL);
      stream->println("mm");

      stream->print(F("Horizontal accuracy estimate: "));
      stream->print(hAcc);
      stream->println("mm");

      stream->print(F("Vertical accuracy estimate: "));
      stream->print(vAcc);
      stream->println("mm");

      stream->println();
    }
};
