class NavigationDOP : public UBXMessage {
  public:
    uint32_t iTOW;
    double gDOP;
    double pDOP;
    double tDOP;
    double vDOP;
    double hDOP;
    double nDOP;
    double eDOP;

    NavigationDOP() {
      msgId = MessageId::Navigation_DillutionOfPrecision;
    }

    NavigationDOP(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationDOP() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationDOP"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("Geometric dillution of precision: "));
      stream->println(gDOP);

      stream->print(F("Position dillution of precision: "));
      stream->println(pDOP);

      stream->print(F("Time dillution of precision: "));
      stream->println(tDOP);

      stream->print(F("Vertical dillution of precision: "));
      stream->println(vDOP);

      stream->print(F("Horizontal dillution of precision: "));
      stream->println(hDOP);

      stream->print(F("Northing dillution of precision: "));
      stream->println(nDOP);

      stream->print(F("Easting dillution of precision: "));
      stream->println(eDOP);

      stream->println();
    }
};
