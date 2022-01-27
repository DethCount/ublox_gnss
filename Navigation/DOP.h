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

    NavigationDOP(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
    }

    virtual ~NavigationDOP() {}
};
