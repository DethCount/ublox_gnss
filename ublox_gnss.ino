#include "GNSS.h"

SoftwareSerial ss(11, 10); // RX, TX
GNSS *gnss = new GNSS(&ss);

void setup()
{
  Serial.begin(9600);
  gnss->begin(PortRate::Bauds_9600); // Sets up the GNSS module to communicate with the Arduino over serial at 9600 baud

  UBXMessage* packet;
  
  Serial.println("Disabling UBX time NAV data");
  gnss->configuration->enableMessage(MessageId::Navigation_TimeUTC, false, 0x00);

  Serial.println("Disabling UBX position NAV data");
  gnss->configuration->enableMessage(MessageId::Navigation_PosLLH, false, 0x00);

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

  ///*
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

  Serial.println("Enabling UBX time NAV data");
  gnss->configuration->enableMessage(MessageId::Navigation_TimeUTC, false, 0x01);

  Serial.println("Enabling UBX position NAV data");
  gnss->configuration->enableMessage(MessageId::Navigation_PosLLH, false, 0x01);
}

void loop()
{
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
}
