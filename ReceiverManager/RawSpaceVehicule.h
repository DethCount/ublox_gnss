class ReceiverManagerRawSpaceVehicule : public UBXMessage {
  public:
    uint64_t cpMes;
    uint64_t prMes;
    uint32_t doMes;
    uint8_t svid;
    int8_t mesQI;
    int8_t cno;
    uint8_t lli;

    ReceiverManagerRawSpaceVehicule() {}

    virtual ~ReceiverManagerRawSpaceVehicule() {}

    virtual void print(Stream* stream) {
      stream->println(F("ReceiverManagerRawSpaceVehicule"));

      stream->print(F("svid: "));
      stream->println(svid);

      stream->print(F("Carrier phase measurement: "));
      stream->print(uint32_t(cpMes >> 32));
      stream->print(F(" "));
      stream->print(uint32_t(cpMes));
      stream->println(F("cycles"));

      stream->print(F("Pseudorange measurement: "));
      stream->print(uint32_t(prMes >> 32));
      stream->print(F(" "));
      stream->print(uint32_t(prMes));
      stream->println(F("m"));

      stream->print(F("Doppler measurement: "));
      stream->print(doMes);
      stream->println(F("Hz"));

      stream->print(F("Measurement quality indicator: "));
      stream->println(mesQI);

      stream->print(F("Carrier noise ratio (signal strength): "));
      stream->println(cno);
      stream->println(F("dBHz"));

      stream->print(F("Loss of lock indicator (RINEX): "));
      stream->println(lli);

      stream->println();
    }
};
