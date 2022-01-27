class UBXClient {
  public:
    static const uint8_t NUM_TRIES = 3;
    static const uint16_t TIMEOUT = 2000;
    static const byte SYNC_1 = 0xB5;
    static const byte SYNC_2 = 0x62;

    Stream *stream;
    UBXParser *parser;
    unsigned short numTries;
    unsigned int timeout;

    UBXClient(
      Stream *s,
      unsigned short numTries = NUM_TRIES,
      unsigned int timeout = TIMEOUT
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
