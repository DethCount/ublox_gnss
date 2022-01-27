enum MessageClass : uint8_t {
  Navigation      = 0x01, // Navigation Results: Position, Speed, Time, Acc, Heading, DOP, SVs used
  ReceiverManager = 0x02, // RXM Messages: Satellite Status, RTC Status
  Information     = 0x04, // Information Messages: Printf-Style Messages, with IDs such as Error, Warning, Notice
  ACK             = 0x05, // Ack/Nack Messages: as replies to CFG Input Messages
  Configuration   = 0x06, // Configuration Input Messages: Set Dynamic Model, Set DOP Mask, Set Baud Rate, etc
  Monitoring      = 0x0A, // Monitoring Messages: Comunication Status, CPU Load, Stack Usage, Task Status
  Aiding          = 0x0B, // AssistNow Aiding Messages: Ephemeris, Almanac, other A-GPS data input
  Timing          = 0x0D, // Timing Messages: Time Pulse Output, Timemark Results
  NMEAStandard    = 0x0F,
  Log             = 0x21, // Logging Messages: Log creation, deletion, info and retrieval
  NMEA            = 0xF0,
  NMEAPUBX        = 0xF1,
};
