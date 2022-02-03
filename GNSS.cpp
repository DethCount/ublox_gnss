#include "GNSS.h"

#ifdef __AVR__
GNSS::GNSS(SoftwareSerial *ss)
{
  swSerial = ss;
  stream = ss;
}
#endif

GNSS::GNSS(HardwareSerial *hs)
{
  hwSerial = hs;
  stream = hs;
}

void GNSS::begin(PortRate baudrate)
{
  if (hwSerial) {
    hwSerial->begin((uint32_t) baudrate);
  }

  #ifdef __AVR__
    if (swSerial) {
      swSerial->begin((uint32_t) baudrate);
    }
  #endif

  ubxClient = new UBXClient(stream);

  aiding = new GNSSAiding(ubxClient);
  navigation = new GNSSNavigation(ubxClient);
  configuration = new GNSSConfiguration(ubxClient);
  log = new GNSSLog(ubxClient);
  monitoring = new GNSSMonitoring(ubxClient);
  receiverManager = new GNSSReceiverManager(ubxClient);
  timing = new GNSSTiming(ubxClient);
  //information = new GNSSInformation(ubxClient);

  UBXRequestStatus st = configuration->setPortRate(baudrate);
  #ifdef GNSS_LOG_INFO
    if (st == UBXRequestStatus::Success) {
      Serial.print("Port rate configured to: ");
      Serial.print((uint32_t) baudrate);
      Serial.println("bauds");
    }
  #endif
}
