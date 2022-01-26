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
  Log             = 0x21, // Logging Messages: Log creation, deletion, info and retrieval
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
  Configuration_SatelliteBasedAugmentationSystems = ((uint16_t) MessageClass::Configuration) << 8 | 0x16,
  Configuration_NationalMarineElectronicsAssociation = ((uint16_t) MessageClass::Configuration) << 8 | 0x17,
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
  Aiding_Request = ((uint16_t) MessageClass::Aiding) << 8 | 0x00,
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
  Log_Erase = ((uint16_t) MessageClass::Log) << 8 | 0x03,
  Log_Create = ((uint16_t) MessageClass::Log) << 8 | 0x07,
  Log_String = ((uint16_t) MessageClass::Log) << 8 | 0x04,
  Log_Info = ((uint16_t) MessageClass::Log) << 8 | 0x08,
  Log_Retrieve = ((uint16_t) MessageClass::Log) << 8 | 0x09,
  Log_RetrievePosition = ((uint16_t) MessageClass::Log) << 8 | 0x0B,
  Log_RetrieveString = ((uint16_t) MessageClass::Log) << 8 | 0x0D,
  Log_FindTime = ((uint16_t) MessageClass::Log) << 8 | 0x0E,
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
  Portable = 0x00,
  Stationary = 0x02,
  Pedestrian = 0x03,
  Automotive = 0x04,
  Sea = 0x05,
  Airborne1G = 0x06,
  Airborne2G = 0x07,
  Airborne4G = 0x08,
};

enum struct DataRate : uint16_t {
  F1Hz = 1000, // ms period
  F2Hz = 500,
  F3_33Hz = 300,
  F4Hz = 250
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

enum struct PortId : uint8_t {
  DDC = 0x00,
  UART = 0x01,
  USB = 0x03,
  SPI = 0x04
};

enum struct GNSSProtocol : uint8_t {
  UBX = 0x00,
  NMEA = 0x01
};

enum struct GNSSFixType : uint8_t {
  NoFix = 0x00,
  DeadReckoning = 0x01,
  D2 = 0x02,
  D3 = 0x03,
  GNSSWithDeadReckoning = 0x04,
  Time = 0x05
};

enum struct GNSSReferenceTime : uint16_t {
  UTC = 0x00,
  GPS = 0x01
};

enum struct ConfigurationResetMode : uint8_t {
  HardwareResetImmediatly = 0x00,
  ControlledSoftwareReset = 0x01,
  ControlledSoftwareResetGNSSOnly = 0x02,
  HardwareResetAfterShutdown = 0x04,
  ControlledGNSSStop = 0x08,
  ControlledGNSSStart = 0x09
};

enum struct LowPowerMode : uint8_t {
  Continuous = 0x00,
  PowerSave = 0x01,
  Continuous2 = 0x04,
};

enum struct GNSSLogSize : uint8_t {
  MaximumSafeSize = 0x00,
  MinimumSize = 0x01,
  UserDefined = 0x02
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

#include "Configuration/Antenna.h"
#include "Configuration/Datum.h"
#include "Configuration/GNSSBlock.h"
#include "Configuration/GNSS.h"
#include "Configuration/Information.h"
#include "Configuration/InterferenceMonitor.h"
#include "Configuration/LogFilter.h"
#include "Configuration/Messaging.h"
#include "Configuration/Navigation.h"
#include "Configuration/NavigationExpert.h"
#include "Configuration/NMEA.h"
#include "Configuration/Port.h"
#include "Configuration/Power.h"
#include "Configuration/Rate.h"
#include "Configuration/RemoteInventory.h"
#include "Configuration/Receiver.h"
#include "Configuration/SBAS.h"
#include "Configuration/TimePulse.h"
#include "Configuration/USB.h"

#include "Information/Debug.h"
#include "Information/Error.h"
#include "Information/Notice.h"
#include "Information/Test.h"
#include "Information/Warning.h"

#include "Log/FindTime.h"
#include "Log/Info.h"
#include "Log/RetrievePosition.h"
#include "Log/RetrieveString.h"

#include "UBXParser.h"
#include "UBXClient.h"

#include "GNSSAiding.h"
#include "GNSSNavigation.h"
#include "GNSSConfiguration.h"
#include "GNSSLog.h"

// definition of UBX class IDs
// source: U-blox7 V14 Receiver Description Protocol page 88 https://www.u-blox.com/sites/default/files/products/documents/u-blox7-V14_ReceiverDescriptionProtocolSpec_%28GPS.G7-SW-12001%29_Public.pdf

class GNSS {
  public:
    UBXClient *ubxClient;
    GNSSAiding *aiding;
    GNSSNavigation *navigation;
    GNSSConfiguration *configuration;

    #ifdef __AVR__
      GNSS(SoftwareSerial *ss);
    #endif

    GNSS(HardwareSerial *hs);

    void begin(PortRate baudrate);
  private:
    Stream *stream = NULL;
    HardwareSerial *hwSerial = NULL;
    #ifdef __AVR__
      SoftwareSerial *swSerial = NULL;
    #endif

    void sendConfiguration(void);
};

