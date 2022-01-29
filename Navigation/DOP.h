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
};
