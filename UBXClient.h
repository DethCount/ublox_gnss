class UBXClient {
  public:
    Stream *stream;
    UBXParser *parser;
    unsigned short numTries;
    unsigned int timeout;

    UBXClient(
      Stream *s,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    UBXMessage* next(MessageId expectedId = MessageId::None);
    UBXMessage* next(
      MessageId expectedId,
      unsigned int timeout
    );

    UBXRequestStatus nextACK(UBXMessage* msg);

    void calcChecksum(UBXMessage* msg);

    void send(UBXMessage* msg);

    UBXRequestStatus trySendWithACK(UBXMessage* msg);

    UBXMessage* trySend(UBXMessage* msg, MessageId expectedResponseMsgId);
};
