#include "Arduino.h"

#ifdef __AVR__
  #include <util/delay.h>
  #include <SoftwareSerial.h>
#endif

#define GNSS_DEBUG

#define GNSS_NB_PORTS 6
#define GNSS_NB_PROTOCOLS 8
#define GNSS_MAX_SVID 0xFF

#include "UBX/MessageClass.h"
#include "UBX/MessageId.h"
#include "UBX/RequestStatus.h"
#include "UBX/Message.h"
#include "UBX/Packet.h"
#include "UBX/Ack.h"

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

enum struct SBASMode : uint8_t {
  Disabled = 0x00,
  EnabledIntegrity = 0x01,
  EnabledTestmode = 0x03
};

enum struct SBASSystem : int8_t {
  Unknown = -1,
  WAAS = 0,
  EGNOS = 1,
  MSAS = 2,
  GPS = 16
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

enum struct AntennaSupervisorStatus : uint8_t {
  Init = 0,
  Unknown = 1,
  OK = 2,
  Short = 3,
  Open = 4
};

enum struct AntennaPowerStatus : uint8_t {
  Off = 0,
  On = 1,
  Unknown = 2
};

#include "GPS/Subframe.h"
#include "GPS/Subframe1.h"
#include "GPS/Subframe2.h"
#include "GPS/Subframe3.h"

#include "Aiding/Almanach.h"
#include "Aiding/AlmanachPlus.h"
#include "Aiding/AOP.h"
#include "Aiding/Ephemeris.h"
#include "Aiding/HealthUTCIonosphere.h"
#include "Aiding/Init.h"

#include "Navigation/AOPStatus.h"
#include "Navigation/Clock.h"
#include "Navigation/DGPSChannel.h"
#include "Navigation/DGPS.h"
#include "Navigation/DOP.h"
#include "Navigation/PosECEF.h"
#include "Navigation/PosLLH.h"
#include "Navigation/PosVT.h"
#include "Navigation/SBASItem.h"
#include "Navigation/SBAS.h"
#include "Navigation/SOL.h"
#include "Navigation/Status.h"
#include "Navigation/SpaceVehicule.h"
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

#include "Monitoring/Hardware.h"
#include "Monitoring/HardwareExtended.h"
#include "Monitoring/IO.h"
#include "Monitoring/MsgParseProcess.h"
#include "Monitoring/Buffer.h"
#include "Monitoring/Receiver.h"
#include "Monitoring/ReceiverBuffer.h"
#include "Monitoring/TransmitterBuffer.h"
#include "Monitoring/Version.h"

#include "ReceiverManager/Almanach.h"
#include "ReceiverManager/Ephemeris.h"
#include "ReceiverManager/RawSpaceVehicule.h"
#include "ReceiverManager/Raw.h"
#include "ReceiverManager/Subframe.h"
#include "ReceiverManager/SpaceVehicule.h"
#include "ReceiverManager/SpaceVehiculeInfo.h"

#include "Timing/Mark.h"
#include "Timing/Pulse.h"
#include "Timing/Verification.h"

#include "UBXParser.h"
#include "UBXClient.h"

#include "GNSSAiding.h"
#include "GNSSNavigation.h"
#include "GNSSConfiguration.h"
#include "GNSSLog.h"
#include "GNSSMonitoring.h"
#include "GNSSReceiverManager.h"
#include "GNSSTiming.h"

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

