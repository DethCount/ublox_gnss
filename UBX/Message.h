class UBXMessage {
  public:
    bool isValid;
    MessageId msgId;

    UBXMessage() {}

    virtual ~UBXMessage() {}

    virtual void print(Stream* stream) {
      stream->println(F("UBXMessage"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("msgId: "));
      stream->print(highByte((uint16_t)msgId));
      stream->print(F(" "));
      stream->println(lowByte((uint16_t)msgId));

      stream->println();
    }
};
