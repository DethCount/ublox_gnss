class NavigationVelNED : public UBXMessage {
  public:
    uint32_t iTOW;
    int32_t velocityNorth;
    int32_t velocityEast;
    int32_t velocityDown;
    uint32_t speed;
    uint32_t groundSpeed;
    double heading;
    uint32_t sAcc;
    double cAcc;

    NavigationVelNED() {
      msgId = MessageId::Navigation_VelNED;
    }

    NavigationVelNED(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~NavigationVelNED() {}

    virtual void print(Stream* stream) {
      stream->println(F("NavigationVelNED"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("GPS time of week: "));
      stream->print(iTOW);
      stream->println(F("ms"));

      stream->print(F("NED North velocity: "));
      stream->print(velocityNorth);
      stream->println("cm/s");

      stream->print(F("NED East velocity: "));
      stream->print(velocityEast);
      stream->println("cm/s");

      stream->print(F("NED Down velocity: "));
      stream->print(velocityDown);
      stream->println("cm/s");

      stream->print(F("Speed (3-D): "));
      stream->print(speed);
      stream->println("cm/s");

      stream->print(F("Ground speed (2-D): "));
      stream->print(groundSpeed);
      stream->println("cm/s");

      stream->print(F("Heading of motion (2-D): "));
      stream->print(heading);
      stream->println("°");

      stream->print(F("Speed accuracy estimate: "));
      stream->print(sAcc);
      stream->println("cm/s");

      stream->print(F("Course/Heading accuracy estimate: "));
      stream->print(cAcc);
      stream->println("°");

      stream->println();
    }
};
