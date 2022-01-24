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

	configuration->setPortRate(baudrate);
}
