class UBXMessage {
  public:
    bool isValid;
    MessageId msgId;

    virtual ~UBXMessage() {}
};
