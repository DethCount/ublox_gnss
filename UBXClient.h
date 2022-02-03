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

    UBXMessage* next(
      MessageId expectedId = MessageId::None,
      uint16_t expectedLength = 0
    );
    UBXMessage* next(
      MessageId expectedId,
      unsigned int timeout,
      uint16_t expectedLength
    );

    UBXRequestStatus nextACK(UBXPacket* packet);

    void calcChecksum(UBXPacket* packet);

    void send(UBXPacket* packet);

    UBXRequestStatus trySendWithACK(UBXPacket* packet);

    UBXMessage* trySend(
      UBXPacket* packet,
      MessageId expectedResponseMsgId,
      uint16_t expectedLength = 0
    );
};
