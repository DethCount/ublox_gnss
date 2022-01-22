#include "Arduino.h"

#ifdef __AVR__
  #include <util/delay.h>
  #include <SoftwareSerial.h>
#endif

#define GNSS_DEBUG

#define UBX_NUM_TRIES 3
#define UBX_TIMEOUT 2000

#define UBX_SYNC_1 0xB5
#define UBX_SYNC_2 0x62

#define DGPS_MAX_CHANNELS 0xFF
#define SBAS_MAX_ITEMS 0xFF
#define SVINFO_MAX_ITEMS 0xFF

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
  Logging         = 0x21, // Logging Messages: Log creation, deletion, info and retrieval
  NMEA            = 0xF0,
  NMEAPUBX        = 0xF1,
};

enum MessageId : unsigned int {
  None = 0x0000,
  Navigation_PosECEF = ((uint16_t) MessageClass::Navigation) << 8 | 0x01,
  Navigation_PosLLH = ((uint16_t) MessageClass::Navigation) << 8 | 0x02,
  Navigation_Status = ((uint16_t) MessageClass::Navigation) << 8 | 0x03,
  Navigation_DOP = ((uint16_t) MessageClass::Navigation) << 8 | 0x04,
  Navigation_SOL = ((uint16_t) MessageClass::Navigation) << 8 | 0x06,
  Navigation_PosVT = ((uint16_t) MessageClass::Navigation) << 8 | 0x07,
  Navigation_VelECEF = ((uint16_t) MessageClass::Navigation) << 8 | 0x11,
  Navigation_VelNED = ((uint16_t) MessageClass::Navigation) << 8 | 0x12,
  Navigation_TimeGPS = ((uint16_t) MessageClass::Navigation) << 8 | 0x20,
  Navigation_TimeUTC = ((uint16_t) MessageClass::Navigation) << 8 | 0x21,
  Navigation_Clock = ((uint16_t) MessageClass::Navigation) << 8 | 0x22,
  Navigation_SpaceVehiculeInfo = ((uint16_t) MessageClass::Navigation) << 8 | 0x30,
  Navigation_DGPS = ((uint16_t) MessageClass::Navigation) << 8 | 0x31,
  Navigation_SBAS = ((uint16_t) MessageClass::Navigation) << 8 | 0x32,
  Navigation_AOPStatus = ((uint16_t) MessageClass::Navigation) << 8 | 0x60,
  ReceiverManager_Raw = ((uint16_t) MessageClass::ReceiverManager) << 8 | 0x10,
  ReceiverManager_SubFrameBuffer = ((uint16_t) MessageClass::ReceiverManager) << 8 | 0x11,
  ReceiverManager_SVStatus = ((uint16_t) MessageClass::ReceiverManager) << 8 | 0x20,
  ReceiverManager_Almanach = ((uint16_t) MessageClass::ReceiverManager) << 8 | 0x30,
  ReceiverManager_Ephemeris = ((uint16_t) MessageClass::ReceiverManager) << 8 | 0x31,
  ReceiverManager_PowerReq = ((uint16_t) MessageClass::ReceiverManager) << 8 | 0x41,
  Information_Error = ((uint16_t) MessageClass::Information) << 8 | 0x00,
  Information_Warning = ((uint16_t) MessageClass::Information) << 8 | 0x01,
  Information_Notice = ((uint16_t) MessageClass::Information) << 8 | 0x02,
  Information_Test = ((uint16_t) MessageClass::Information) << 8 | 0x03,
  Information_Debug = ((uint16_t) MessageClass::Information) << 8 | 0x04,
  ACK_NACK = ((uint16_t) MessageClass::ACK) << 8 | 0x00,
  ACK_ACK = ((uint16_t) MessageClass::ACK) << 8 | 0x01,
  Configuration_Port = ((uint16_t) MessageClass::Configuration) << 8 | 0x00,
  Configuration_Messaging = ((uint16_t) MessageClass::Configuration) << 8 | 0x01,
  Configuration_Information = ((uint16_t) MessageClass::Configuration) << 8 | 0x02,
  Configuration_Reset = ((uint16_t) MessageClass::Configuration) << 8 | 0x04,
  Configuration_Datum = ((uint16_t) MessageClass::Configuration) << 8 | 0x06,
  Configuration_Rate = ((uint16_t) MessageClass::Configuration) << 8 | 0x08,
  Configuration_Configuration = ((uint16_t) MessageClass::Configuration) << 8 | 0x09,
  Configuration_Receiver = ((uint16_t) MessageClass::Configuration) << 8 | 0x11,
  Configuration_Antenna = ((uint16_t) MessageClass::Configuration) << 8 | 0x13,
  Configuration_SBAS = ((uint16_t) MessageClass::Configuration) << 8 | 0x16,
  Configuration_NMEA = ((uint16_t) MessageClass::Configuration) << 8 | 0x17,
  Configuration_USB = ((uint16_t) MessageClass::Configuration) << 8 | 0x18,
  Configuration_NavigationExpert = ((uint16_t) MessageClass::Configuration) << 8 | 0x23,
  Configuration_Navigation = ((uint16_t) MessageClass::Configuration) << 8 | 0x24,
  Configuration_TimePulse = ((uint16_t) MessageClass::Configuration) << 8 | 0x31,
  Configuration_RemoteInventory = ((uint16_t) MessageClass::Configuration) << 8 | 0x34,
  Configuration_Power = ((uint16_t) MessageClass::Configuration) << 8 | 0x38,
  Configuration_InterferenceMonitor = ((uint16_t) MessageClass::Configuration) << 8 | 0x39,
  Configuration_GlobalNavigationSatelliteSystem = ((uint16_t) MessageClass::Configuration) << 8 | 0x3E,
  Configuration_LogFilter = ((uint16_t) MessageClass::Configuration) << 8 | 0x47,
  Monitoring_IO = ((uint16_t) MessageClass::Monitoring) << 8 | 0x02,
  Monitoring_Version = ((uint16_t) MessageClass::Monitoring) << 8 | 0x04,
  Monitoring_MsgParseProcess = ((uint16_t) MessageClass::Monitoring) << 8 | 0x06,
  Monitoring_ReceiverBuffer = ((uint16_t) MessageClass::Monitoring) << 8 | 0x07,
  Monitoring_TransmitterBuffer = ((uint16_t) MessageClass::Monitoring) << 8 | 0x08,
  Monitoring_Hardware = ((uint16_t) MessageClass::Monitoring) << 8 | 0x09,
  Monitoring_Hardware2 = ((uint16_t) MessageClass::Monitoring) << 8 | 0x0B,
  Monitoring_Receiver = ((uint16_t) MessageClass::Monitoring) << 8 | 0x21,
  Aiding_Req = ((uint16_t) MessageClass::Aiding) << 8 | 0x00,
  Aiding_Init = ((uint16_t) MessageClass::Aiding) << 8 | 0x01,
  Aiding_HealthUTCIonosphere = ((uint16_t) MessageClass::Aiding) << 8 | 0x02,
  Aiding_Data = ((uint16_t) MessageClass::Aiding) << 8 | 0x10,
  Aiding_Almanach = ((uint16_t) MessageClass::Aiding) << 8 | 0x30,
  Aiding_Ephemeris = ((uint16_t) MessageClass::Aiding) << 8 | 0x31,
  Aiding_AlmanachPlus = ((uint16_t) MessageClass::Aiding) << 8 | 0x32,
  Aiding_AOP = ((uint16_t) MessageClass::Aiding) << 8 | 0x33,
  Aiding_AlmanachPlusFileTransfer = ((uint16_t) MessageClass::Aiding) << 8 | 0x50,
  Timing_Pulse = ((uint16_t) MessageClass::Timing) << 8 | 0x01,
  Timing_Mark = ((uint16_t) MessageClass::Timing) << 8 | 0x03,
  Timing_Verification = ((uint16_t) MessageClass::Timing) << 8 | 0x06,
  Logging_Erase = ((uint16_t) MessageClass::Logging) << 8 | 0x03,
  Logging_CreateFile = ((uint16_t) MessageClass::Logging) << 8 | 0x07,
  Logging_String = ((uint16_t) MessageClass::Logging) << 8 | 0x04,
  Logging_Info = ((uint16_t) MessageClass::Logging) << 8 | 0x08,
  Logging_Retrieve = ((uint16_t) MessageClass::Logging) << 8 | 0x09,
  Logging_RetrievePos = ((uint16_t) MessageClass::Logging) << 8 | 0x0B,
  Logging_RetrieveString = ((uint16_t) MessageClass::Logging) << 8 | 0x0D,
  Logging_FindTime = ((uint16_t) MessageClass::Logging) << 8 | 0x0E,
  NMEA_GGA = ((uint16_t) MessageClass::NMEA << 8) | 0x00,
  NMEA_GLL = ((uint16_t) MessageClass::NMEA << 8) | 0x01,
  NMEA_GSA = ((uint16_t) MessageClass::NMEA << 8) | 0x02,
  NMEA_GSV = ((uint16_t) MessageClass::NMEA << 8) | 0x03,
  NMEA_RMC = ((uint16_t) MessageClass::NMEA << 8) | 0x04,
  NMEA_VTG = ((uint16_t) MessageClass::NMEA << 8) | 0x05,
  NMEA_GRS = ((uint16_t) MessageClass::NMEA << 8) | 0x06,
  NMEA_GST = ((uint16_t) MessageClass::NMEA << 8) | 0x07,
  NMEA_ZDA = ((uint16_t) MessageClass::NMEA << 8) | 0x08,
  NMEA_GBS = ((uint16_t) MessageClass::NMEA << 8) | 0x09,
  NMEA_DTM = ((uint16_t) MessageClass::NMEA << 8) | 0x0A,
  NMEA_GNS = ((uint16_t) MessageClass::NMEA << 8) | 0x0D,
  NMEA_GPQ = ((uint16_t) MessageClass::NMEA << 8) | 0x40,
  NMEA_TXT = ((uint16_t) MessageClass::NMEA << 8) | 0x41,
  NMEA_GNQ = ((uint16_t) MessageClass::NMEA << 8) | 0x42,
  NMEA_GLQ = ((uint16_t) MessageClass::NMEA << 8) | 0x43,
  NMEAPUBX_Position = ((uint16_t) MessageClass::NMEAPUBX << 8) | 0x00,
  NMEAPUBX_SVStatus = ((uint16_t) MessageClass::NMEAPUBX << 8) << 8 | 0x03,
  NMEAPUBX_Time = ((uint16_t) MessageClass::NMEAPUBX << 8) << 8 | 0x04,
  NMEAPUBX_Rate = ((uint16_t) MessageClass::NMEAPUBX << 8) << 8 | 0x40,
  NMEAPUBX_Configuration = ((uint16_t) MessageClass::NMEAPUBX << 8) << 8 | 0x41,
};

enum struct UBXRequestStatus : uint8_t {
  Failure = 1,
  Timeout = 5,
  Success = 10,
};

enum struct NavigationMode : byte {
  Pedestrian = 0x03,
  Automotive = 0x04,
  Sea = 0x05,
  Airborne = 0x06
};

enum struct DataRate : uint16_t {
  F1Hz = 0xE803,
  F2Hz = 0xFA01,
  F3_33Hz = 0x2C01,
  F4Hz = 0xFA00
};

enum struct PortRate : uint32_t {
  Bauds_4800 = 4800,
  Bauds_9600 = 9600,
  Bauds_19200 = 19200,
  Bauds_38400 = 38400,
  Bauds_57600 = 57600,
  Bauds_115200 = 115200,
  Bauds_230400 = 230400
};

enum struct GNSSFixType : uint8_t {
  NoFix = 0x00,
  DeadReckoning = 0x01,
  D2 = 0x02,
  D3 = 0x03,
  GNSSWithDeadReckoning = 0x04,
  Time = 0x05
};

const int UBX_MSG_PAYLOAD_SIZE = 0x0FFF;
class UBXMessage {
  public:
    bool isValid;
    MessageId msgId;
    uint16_t payloadLength;
    byte payload[UBX_MSG_PAYLOAD_SIZE];
    byte checksum[2] = { 0x00, 0x00 };

    virtual ~UBXMessage() {}
};

class UBXAck : public UBXMessage {
  public:
    MessageId incomingMsgId;

    UBXAck() {
      isValid = false;
      msgId = MessageId::None;
      payloadLength = 0;
      incomingMsgId = MessageId::None;
    }

    UBXAck(UBXMessage & msg) {
      isValid = msg.isValid;
      msgId = msg.msgId;
      payloadLength = msg.payloadLength;
      memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
      memcpy(checksum, msg.checksum, 2);
      Serial.println("Conv UBXMess");
    }

    virtual ~UBXAck() {}
};

#include "Aiding/Almanach.h"
#include "Aiding/AlmanachPlus.h"
#include "Aiding/AOP.h"
#include "Aiding/Ephemeris.h"
#include "Aiding/HealthUTCIonosphere.h"
#include "Aiding/Init.h"

#include "Navigation/AOPStatus.h"
#include "Navigation/Clock.h"
#include "Navigation/DGPS.h"
#include "Navigation/DOP.h"
#include "Navigation/PosECEF.h"
#include "Navigation/PosLLH.h"
#include "Navigation/PosVT.h"
#include "Navigation/SBAS.h"
#include "Navigation/SOL.h"
#include "Navigation/Status.h"
#include "Navigation/SpaceVehiculeInfo.h"
#include "Navigation/TimeGPS.h"
#include "Navigation/TimeUTC.h"
#include "Navigation/VelECEF.h"
#include "Navigation/VelNED.h"

#include "Configuration/Rate.h"


// definition of UBX class IDs
// source: U-blox7 V14 Receiver Description Protocol page 88 https://www.u-blox.com/sites/default/files/products/documents/u-blox7-V14_ReceiverDescriptionProtocolSpec_%28GPS.G7-SW-12001%29_Public.pdf

class GNSS {
  public:
    #ifdef __AVR__
      GNSS(SoftwareSerial *ss);
    #endif

    GNSS(HardwareSerial *hs);

    void begin(PortRate baudrate);

    void getConfiguration(void);

    AidingAlmanach* getAidingAlmanach(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingAlmanach* getAidingAlmanach(
      uint8_t svid,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingAlmanachPlus* getAidingAlmanachPlus(
      uint8_t idSize,
      uint8_t type,
      uint16_t ofs,
      uint16_t size,
      uint16_t fileId,
      uint16_t dataSize,
      uint8_t id1,
      uint8_t id2,
      uint16_t id3,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingAOP* getAidingAOP(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingAOP* getAidingAOP(
      uint8_t svid,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    void getAidingData(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingEphemeris* getAidingEphemeris(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingEphemeris* getAidingEphemeris(
      uint8_t svid,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingHealthUTCIonosphere* getAidingHealthUTCIonosphere(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    AidingInit* getAidingInit(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationAOPStatus* getNavigationAOPStatus(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationClock* getNavigationClock(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationDGPS* getNavigationDGPS(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationDOP* getNavigationDOP(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationPosECEF* getNavigationPosECEF(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationPosLLH* getNavigationPosLLH(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationPosVT* getNavigationPosVT(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationSBAS* getNavigationSBAS(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationSOL* getNavigationSOL(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationStatus* getNavigationStatus(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationSpaceVehiculeInfo* getNavigationSpaceVehiculeInfo(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationTimeGPS* getNavigationTimeGPS(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationTimeUTC* getNavigationTimeUTC(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationVelECEF* getNavigationVelECEF(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    NavigationVelNED* getNavigationVelNED(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    ConfigurationRate* getConfigurationRate(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    UBXRequestStatus enableMessage(
      uint16_t msgId,
      bool changePort = false,
      byte port1 = 0x00,
      byte port2 = 0x00,
      byte port3 = 0x00,
      byte port4 = 0x00,
      byte port5 = 0x00,
      byte port6 = 0x00,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    UBXRequestStatus updatePortRate(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    UBXRequestStatus updateDataRate(
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    UBXMessage* nextUBXPacket(
      unsigned int timeout = UBX_TIMEOUT,
      MessageId expectedId = MessageId::None
    );

    UBXRequestStatus nextUBXACK(
      UBXMessage* msg,
      unsigned int timeout = UBX_TIMEOUT
    );

    void sendUBX(UBXMessage* msg);

    UBXRequestStatus trySendUBXWithACK(
      UBXMessage* msg,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );

    UBXMessage* trySendUBX(
      UBXMessage* msg,
      MessageId expectedResponseMsgId,
      unsigned short numTries = UBX_NUM_TRIES,
      unsigned int timeout = UBX_TIMEOUT
    );
  
  private:
    NavigationMode navigationMode = NavigationMode::Pedestrian;
    DataRate dataRate = DataRate::F4Hz;
    PortRate portRate;
    Stream *stream = NULL;
    HardwareSerial *hwSerial = NULL;
    #ifdef __AVR__
      SoftwareSerial *swSerial = NULL;
    #endif

    void sendConfiguration(void);

  	void calcChecksum(UBXMessage* msg);

    UBXMessage* parseUBXPacket(UBXMessage* msg);

    UBXAck* parseUBX_ACK(UBXMessage* msg);
    UBXAck* parseUBX_ACK(UBXAck* msg);

    UBXMessage* parseUBX_Aiding(UBXMessage* msg);
    UBXMessage* parseUBX_Navigation(UBXMessage* msg);
    UBXMessage* parseUBX_Configuration(UBXMessage* msg);

    AidingAlmanach* parseUBX_AidingAlmanach(UBXMessage* msg);
    AidingAlmanach* parseUBX_AidingAlmanach(AidingAlmanach* msg);

    AidingAlmanachPlus* parseUBX_AidingAlmanachPlus(UBXMessage* msg);
    AidingAlmanachPlus* parseUBX_AidingAlmanachPlus(AidingAlmanachPlus* msg);

    AidingAOP* parseUBX_AidingAOP(UBXMessage* msg);
    AidingAOP* parseUBX_AidingAOP(AidingAOP* msg);

    AidingEphemeris* parseUBX_AidingEphemeris(UBXMessage* msg);
    AidingEphemeris* parseUBX_AidingEphemeris(AidingEphemeris* msg);

    AidingHealthUTCIonosphere* parseUBX_AidingHealthUTCIonosphere(
      UBXMessage* msg
    );
    AidingHealthUTCIonosphere* parseUBX_AidingHealthUTCIonosphere(
      AidingHealthUTCIonosphere* msg
    );

    AidingInit* parseUBX_AidingInit(UBXMessage* msg);
    AidingInit* parseUBX_AidingInit(AidingInit* msg);

    NavigationAOPStatus* parseUBX_NavigationAOPStatus(UBXMessage* msg);
    NavigationAOPStatus* parseUBX_NavigationAOPStatus(NavigationAOPStatus* msg);

    NavigationClock* parseUBX_NavigationClock(UBXMessage* msg);
    NavigationClock* parseUBX_NavigationClock(NavigationClock* msg);

    NavigationDGPS* parseUBX_NavigationDGPS(UBXMessage* msg);
    NavigationDGPS* parseUBX_NavigationDGPS(NavigationDGPS* msg);

    NavigationDOP* parseUBX_NavigationDOP(UBXMessage* msg);
    NavigationDOP* parseUBX_NavigationDOP(NavigationDOP* msg);

    NavigationPosECEF* parseUBX_NavigationPosECEF(UBXMessage* msg);
    NavigationPosECEF* parseUBX_NavigationPosECEF(NavigationPosECEF* msg);

    NavigationPosLLH* parseUBX_NavigationPosLLH(UBXMessage* msg);
    NavigationPosLLH* parseUBX_NavigationPosLLH(NavigationPosLLH* msg);

    NavigationPosVT* parseUBX_NavigationPosVT(UBXMessage* msg);
    NavigationPosVT* parseUBX_NavigationPosVT(NavigationPosVT* msg);

    NavigationSBAS* parseUBX_NavigationSBAS(UBXMessage* msg);
    NavigationSBAS* parseUBX_NavigationSBAS(NavigationSBAS* msg);

    NavigationSOL* parseUBX_NavigationSOL(UBXMessage* msg);
    NavigationSOL* parseUBX_NavigationSOL(NavigationSOL* msg);

    NavigationStatus* parseUBX_NavigationStatus(UBXMessage* msg);
    NavigationStatus* parseUBX_NavigationStatus(NavigationStatus* msg);

    NavigationSpaceVehiculeInfo* parseUBX_NavigationSpaceVehiculeInfo(
      UBXMessage* msg
    );
    NavigationSpaceVehiculeInfo* parseUBX_NavigationSpaceVehiculeInfo(
      NavigationSpaceVehiculeInfo* msg
    );

    NavigationTimeGPS* parseUBX_NavigationTimeGPS(UBXMessage* msg);
    NavigationTimeGPS* parseUBX_NavigationTimeGPS(NavigationTimeGPS* msg);

    NavigationTimeUTC* parseUBX_NavigationTimeUTC(UBXMessage* msg);
    NavigationTimeUTC* parseUBX_NavigationTimeUTC(NavigationTimeUTC* msg);

    NavigationVelECEF* parseUBX_NavigationVelECEF(UBXMessage* msg);
    NavigationVelECEF* parseUBX_NavigationVelECEF(NavigationVelECEF* msg);

    NavigationVelNED* parseUBX_NavigationVelNED(UBXMessage* msg);
    NavigationVelNED* parseUBX_NavigationVelNED(NavigationVelNED* msg);

    ConfigurationRate* parseUBX_ConfigurationRate(UBXMessage* msg);
    ConfigurationRate* parseUBX_ConfigurationRate(ConfigurationRate* msg);

    uint8_t extractU1(uint8_t startIdx, byte* msgData);
    int8_t extractI1(uint8_t startIdx, byte* msgData);
    byte extractX1(uint8_t startIdx, byte* msgData);

    uint16_t extractU2(uint8_t startIdx, byte* msgData);
    int16_t extractI2(uint8_t startIdx, byte* msgData);
    uint16_t extractX2(uint8_t startIdx, byte* msgData);

    uint32_t extractU4(uint8_t startIdx, byte* msgData);
    int32_t extractI4(uint8_t startIdx, byte* msgData);
    uint32_t extractX4(uint8_t startIdx, byte* msgData);
    uint32_t extractR4(uint8_t startIdx, byte* msgData);

    uint64_t extractU8(uint8_t startIdx, byte* msgData);
    int64_t extractI8(uint8_t startIdx, byte* msgData);
    uint64_t extractR8(uint8_t startIdx, byte* msgData);
};

