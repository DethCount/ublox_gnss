#include "GNSS.h"

SoftwareSerial ss(11, 10); // RX, TX
GNSS *gnss = new GNSS(&ss);

void setup()
{
  Serial.begin(9600);
  FREERAM_PRINT;
  Serial.println("Setting up GNSS...");
  gnss->begin(PortRate::Bauds_9600); // Sets up the GNSS module to communicate with the Arduino over serial at 9600 baud

  gnss->ubxClient->numTries = 5;
  gnss->ubxClient->timeout = 400;

  // UBXMessage* packet;

  // Serial.println("Disabling UBX time NAV data");
  // gnss->configuration->enableMessage(MessageId::Navigation_TimeUTC, false, 0x00);

  // Serial.println("Disabling UBX position NAV data");
  // gnss->configuration->enableMessage(MessageId::Navigation_PosLLH, false, 0x00);

/*
  FREERAM_PRINT;

  MonitoringHardware* hw = gnss->monitoring->getHardware();
  FREERAM_PRINT;
  hw->print(&Serial);
  delete hw;
*/

  gnss->monitoring->print(&Serial);
  gnss->configuration->print(&Serial);
  gnss->aiding->print(&Serial);
  gnss->navigation->print(&Serial);
  gnss->log->print(&Serial);
  gnss->receiverManager->print(&Serial);
  gnss->timing->print(&Serial);

  /*
  ConfigurationMessaging *msgRate = gnss->configuration->getMsgRate(MessageId::Navigation_PosLLH);
  Serial.println(msgRate->msgId);
  for (uint8_t i = 0; i < sizeof(msgRate->portRate); i++) {
    Serial.println(msgRate->portRate[i]);
  }
  //*/

  /*
  packet = gnss->configuration->getRate();
  if (packet->isValid) {
    ConfigurationRate* cfgRate = static_cast<ConfigurationRate*>(packet);
    Serial.println("Configuration rate");
    Serial.println(cfgRate->measRate);
    Serial.println(cfgRate->navRate);
    Serial.println(cfgRate->timeRef);
  }
  */

  /*
  packet = gnss->navigation->getPosVT();
  if (packet->isValid) {
    NavigationPosVT* posVT = static_cast<NavigationPosVT*>(packet);
    Serial.println("NavigationPosVT");
    Serial.println(posVT->iTOW);
    Serial.println(posVT->year);
    Serial.println(posVT->month);
    Serial.println(posVT->day);
    Serial.println(posVT->hour);
    Serial.println(posVT->minute);
    Serial.println(posVT->second);
    Serial.println(posVT->valid);
    Serial.println(posVT->tAcc);
    Serial.println(posVT->nano);
    Serial.println((uint8_t) posVT->fixType);
    Serial.println(posVT->flags);
    Serial.println(posVT->numSV);
    Serial.println(posVT->longitude);
    Serial.println(posVT->latitude);
    Serial.println(posVT->height);
    Serial.println(posVT->hMSL);
    Serial.println(posVT->hAcc);
    Serial.println(posVT->vAcc);
    Serial.println(posVT->velocityNorth);
    Serial.println(posVT->velocityEast);
    Serial.println(posVT->velocityDown);
    Serial.println(posVT->groundSpeed);
    Serial.println(posVT->heading);
    Serial.println(posVT->sAcc);
    Serial.println(posVT->headingAcc);
    Serial.println(posVT->pDOP);
    Serial.println("end NavigationPosVT");
  }
  //*/

  /*
  Serial.println("Enabling UBX time NAV data");
  gnss->configuration->enableMessage(MessageId::Navigation_TimeUTC, false, 0x01);

  Serial.println("Enabling UBX position NAV data");
  gnss->configuration->enableMessage(MessageId::Navigation_PosLLH, false, 0x01);
  */
  Serial.println("GNSS setup complete !");

  /*
  Serial.println("Calculating SVs positions... !");

  NavigationSpaceVehiculeInfo* svInfo = gnss->navigation->getSpaceVehiculeInfo();

  if (!svInfo->isValid) {
    return;
  }

  for (uint8_t i = 0; i < svInfo->numCh; i++) {
    if (!svInfo->spaceVehicules[i]->isSVUsedForNavigation()
      || svInfo->spaceVehicules[i]->isUnhealthy()
      || !svInfo->spaceVehicules[i]->isEphemerisAvailable()
    ) {
      continue;
    }

    AidingEphemeris* ephemeris = gnss->aiding->getEphemeris(
      svInfo->spaceVehicules[i]->svid
    );

    if (!ephemeris->isValid) {
      continue;
    }

    NavigationPosVT* posVT = gnss->navigation->getPosVT();
    if (!posVT->isValid) {
      continue;
    }

    uint32_t t = posVT->iTOW * 1e-3;
    uint32_t toe = svInfo->iTOW * 1e-3;

    uint32_t sqrta = ephemeris->subframe2->getSemiMajorAxisSqrt();
    uint32_t dn = ephemeris->subframe2
      ->getMeanMotionDifferenceFromComputedValue();
    uint32_t m0 = ephemeris->subframe2->getMeanAnomalyAtReferenceTime();
    uint32_t e = ephemeris->subframe2->getEccentricity();

    uint32_t o = ephemeris->subframe3->getArgumentOfPerigee();
    uint32_t o0 = ephemeris->subframe3
      ->getLongitudeOfAscendingNodeOfOrbitPlaneAtWeeklyEpoch();
    uint32_t i0 = ephemeris->subframe3->getInclinationAngleAtReferenceTime();

    // calculate sat positions
    uint32_t tk = t - toe;

    uint32_t n0 = sqrt(3.986005e14) / pow(sqrta, 6); // 1 / 2^-19

    uint32_t n = n0 + dn; // 2^-11 + 2^-43

    uint32_t mk = m0 + n * tk; // 2^-11 + 2^-31 + 2^-43

    uint32_t ek = mk;
    for (uint8_t j = 0; j < 3; j++) {
      ek += ((mk - ek) + e * sin(ek))
        / (1 - e * cos(ek));
    }

    uint32_t vk = 2 * atan(
      sqrt((1 + e) / (1 - e))
      * tan(ek / 2)
    );

    uint32_t r = pow(sqrta, 2) * (1 + e);

    // (A, e, OMEGA, i, omega) -> ECI
    uint32_t orbitPlaneX = r * cos(o + vk);
    uint32_t orbitPlaneY = r * sin(o + vk);

    uint32_t x = orbitPlaneX;
    uint32_t y = orbitPlaneY;
    uint32_t z = 0;

    // apply inclinaition
    uint32_t ci0 = cos(i0);
    uint32_t si0 = sin(i0);
    y = y * ci0 - z * si0;
    z = y * si0 + z * ci0;

    // apply longitude of ascending node
    uint32_t co0 = cos(o0);
    uint32_t so0 = sin(o0);
    x = x * co0 - y * so0;
    y = x * so0 + y * co0;
  }

  Serial.println("SVs positions calculated !");
  */
}

void loop()
{
  /*
  UBXMessage* packet;
  
  packet = gnss->ubxClient->next();
  if (!packet->isValid) {
    Serial.println("Invalid packet");
    delay(10);
    return;
  }

  Serial.println(packet->msgId);
  if (packet->msgId == MessageId::Navigation_TimeUTC) {
    // Print UTC time hh:mm:ss
    NavigationTimeUTC* t = static_cast<NavigationTimeUTC*>(packet);
    Serial.println();
    Serial.print("UTC time: ");
    Serial.print(t->year);
    Serial.print("-");
    Serial.print(t->month);
    Serial.print("-");
    Serial.print(t->day);
    Serial.print(" ");
    Serial.print(t->hour);
    Serial.print(":");
    Serial.print(t->minute);
    Serial.print(":");
    Serial.print(t->second);
    Serial.println();
  }

  
  if (packet->msgId == MessageId::Navigation_PosLLH) {
    NavigationPosLLH* l = static_cast<NavigationPosLLH*>(packet);
    // Print location (latitude/longitude/height)
    Serial.println();
    Serial.println("PosLLH: ");
    Serial.print(" iTOW: ");
    Serial.println(l->iTOW);
    Serial.print(" Lat: ");
    Serial.println(l->latitude);
    Serial.print(" Long: ");
    Serial.println(l->longitude);
    Serial.print(" height: ");
    Serial.println(l->height);
    Serial.print(" hMSL: ");
    Serial.println(l->hMSL);
    Serial.print(" hAcc: ");
    Serial.println(l->hAcc);
    Serial.print(" vAcc: ");
    Serial.println(l->vAcc);
  }
  
  delay(10);
  */
}
