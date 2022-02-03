class AidingAlmanachPlus : public UBXMessage {
  public:
    static const uint16_t MAX_DATA_SIZE = 0x0FFF;

  	uint8_t idSize;
    uint8_t type;
    uint16_t ofs;
    uint16_t size;
    uint16_t fileId;
    uint8_t id1;
    uint8_t id2;
    uint16_t id3;
    uint16_t dataSize;
    uint16_t data[MAX_DATA_SIZE];

    AidingAlmanachPlus() {
      msgId = MessageId::Aiding_AlmanachPlus;
    }

    AidingAlmanachPlus(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~AidingAlmanachPlus() {}

    virtual void print(Stream* stream) {
      stream->println(F("AidingAlmanachPlus"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("type: "));
      stream->println(type);

      stream->print(F("idSize: "));
      stream->println(idSize);

      stream->print(F("id1: "));
      stream->println(id1);

      stream->print(F("id2: "));
      stream->println(id2);

      stream->print(F("id3: "));
      stream->println(id3);

      stream->print(F("ofs: "));
      stream->println(ofs);

      stream->print(F("size: "));
      stream->println(size);

      stream->print(F("fileId: "));
      stream->println(fileId);

      stream->print(F("dataSize: "));
      stream->println(dataSize);

      for (uint8_t i = 0; i < dataSize; i++) {
        stream->print(F("data["));
        stream->print(i);
        stream->print(F("]: "));
        stream->println(data[i]);
      }

      stream->println();
    }
};
