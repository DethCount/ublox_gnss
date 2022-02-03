#include "GNSS.h"

UBXClient::UBXClient(
  Stream *s,
  unsigned short numT,
  unsigned int timeO
) {
  stream = s;

  parser = new UBXParser();
  numTries = numT;
  timeout = timeO;
}

void UBXClient::calcChecksum(UBXPacket* packet)
{
  packet->checksum[0] = highByte((uint16_t)packet->msgId);
  packet->checksum[1] = packet->checksum[0];
  packet->checksum[0] += lowByte((uint16_t)packet->msgId);
  packet->checksum[1] += packet->checksum[0];

  packet->checksum[0] += lowByte((uint16_t)packet->payloadLength);
  packet->checksum[1] += packet->checksum[0];
  packet->checksum[0] += highByte((uint16_t)packet->payloadLength);
  packet->checksum[1] += packet->checksum[0];

  for (int i = 0; i < packet->payloadLength; i++) {
    packet->checksum[0] += packet->payload[i];
    packet->checksum[1] += packet->checksum[0];
  }
}

UBXRequestStatus UBXClient::trySendWithACK(UBXPacket* packet) {
  short tries = 0;
  UBXRequestStatus result;

  while (tries < numTries && result != UBXRequestStatus::Success) {
    #ifdef GNSS_LOG_INFO
      Serial.print("try ");
      Serial.print(tries + 1);
      Serial.print(" / ");
      Serial.println(numTries);
    #endif

    send(packet);
    result = nextACK(packet);
    tries++;
  }

  delete packet;

  #ifdef GNSS_LOG_DEBUG
    if (tries == numTries && result != UBXRequestStatus::Success) {
      Serial.println("Failed UBX message with ACK.");
    }
  #endif

  return result;
}

UBXMessage* UBXClient::trySend(
  UBXPacket* packet,
  MessageId expectedResponseMsgId,
  uint16_t expectedLength
) {
  UBXMessage* result = new UBXMessage();
  result->isValid = false;
  short tries = 0;
  unsigned long start = millis();

  while (tries < numTries && !result->isValid) {
    #ifdef GNSS_LOG_INFO
      Serial.print("try ");
      Serial.print(tries + 1);
      Serial.print(" / ");
      Serial.println(numTries);
    #endif

    send(packet);
    delete result;
    result = next(expectedResponseMsgId, expectedLength);
    if (result->isValid) {
      #ifdef GNSS_LOG_INFO
      Serial.print("Responded in ");
      Serial.print(millis() - start);
      Serial.println("ms");
      #endif

      delete packet;
      return result;
    }
    tries++;
  }

  delete packet;

  #ifdef GNSS_LOG_INFO
    if (tries == numTries && !result->isValid) {
      Serial.print("Failed UBX message. Expecting: ");
      Serial.println((uint16_t)expectedResponseMsgId);
    }
  #endif

  return result;
}

void UBXClient::send(UBXPacket* packet)
{
  if (packet->checksum[0] == 0x00 && packet->checksum[1] == 0x00) {
    calcChecksum(packet);
  }

  stream->write(SYNC_1);
  #ifdef GNSS_LOG_DEBUG
    Serial.println("sendUBX");
    Serial.println(SYNC_1, HEX);
  #endif

  stream->write(SYNC_2);
  #ifdef GNSS_LOG_DEBUG
    Serial.println(SYNC_2, HEX);
  #endif

  stream->write(highByte((uint16_t)packet->msgId));
  #ifdef GNSS_LOG_DEBUG
    Serial.println(highByte((uint16_t)packet->msgId), HEX);
  #endif

  stream->write(lowByte((uint16_t)packet->msgId));
  #ifdef GNSS_LOG_DEBUG
    Serial.println(lowByte((uint16_t)packet->msgId), HEX);
  #endif

  stream->write(lowByte(packet->payloadLength));
  #ifdef GNSS_LOG_DEBUG
    Serial.println(lowByte(packet->payloadLength), HEX);
  #endif

  stream->write(highByte(packet->payloadLength));
  #ifdef GNSS_LOG_DEBUG
    Serial.println(highByte(packet->payloadLength), HEX);
    Serial.print("payloadLength: ");
    Serial.println(packet->payloadLength);
  #endif

  stream->flush();
  for (int i = 0; i < packet->payloadLength; i++)
  {
    if (i % 100 == 0) {
      stream->flush();
    }

    stream->write(packet->payload[i]);
    #ifdef GNSS_LOG_DEBUG
      Serial.println(packet->payload[i], HEX);
    #endif
  }

  if (packet->checksum[0] == 0x00 && packet->checksum[1] == 0x00) {
    calcChecksum(packet);
  }

  stream->write(packet->checksum[0]);
  #ifdef GNSS_LOG_DEBUG
    Serial.println("checksum0");
    Serial.println(packet->checksum[0], HEX);
  #endif

  stream->write(packet->checksum[1]);
  #ifdef GNSS_LOG_DEBUG
  Serial.println("checksum1");
    Serial.println(packet->checksum[1], HEX);
    Serial.println("end sendUBX");
  #endif

  stream->println();
  stream->flush();
}

UBXMessage* UBXClient::next(
  MessageId expectedId,
  uint16_t expectedLength
) {
  return next(expectedId, timeout, expectedLength);
}

UBXMessage* UBXClient::next(
  MessageId expectedId,
  uint16_t timeout,
  uint16_t expectedLength
) {
  UBXPacket packet;
  packet.isValid = false;
  uint8_t incoming_char;
  int byteIdx = 0;
  bool hasValidChecksum = true;
  uint16_t msgLength = 0;
  byte checksum[2] = { 0x00, 0x00 };
  unsigned long start = millis();
  unsigned long now;
  MessageClass classId;

  while (true) {
    now = millis();
    // Serial.print("Timeout:");
    // Serial.println(now - start);
    // Serial.println(timeout);
    if (now - start > timeout) {
      #ifdef GNSS_LOG_DEBUG
        Serial.println("Timeout");
        Serial.println(timeout);
      #endif

      UBXMessage* msg = new UBXMessage();
      msg->isValid = false;
      return msg;
    }

    if (stream->available()) {
      incoming_char = stream->read();
      #ifdef GNSS_LOG_DEBUG
        Serial.println(incoming_char, HEX);
      #endif

      if (!packet.isValid) {
        byteIdx = 0;

        if (incoming_char == SYNC_1) {
          #ifdef GNSS_LOG_DEBUG
            Serial.println("Incoming packet");
          #endif

          packet.isValid = true;
          hasValidChecksum = true;
          checksum[0] = 0x00;
          checksum[1] = 0x00;
          classId = MessageClass::None;
          memset(packet.payload, 0x00, UBX_PAYLOAD_SIZE);
          byteIdx++;
        }

        continue;
      }

      if (byteIdx == 1) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 1");
        #endif
        packet.isValid = incoming_char == SYNC_2;
        byteIdx++;
      } else if (byteIdx == 2) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 2");
        #endif
        classId = (MessageClass) incoming_char;
        checksum[0] = incoming_char;
        checksum[1] = checksum[0];
        byteIdx++;
      } else if (byteIdx == 3) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 3");
        #endif
        packet.msgId = (MessageId)(((uint8_t)classId) << 8 | incoming_char);
        packet.isValid = expectedId == MessageId::None
          || packet.msgId == expectedId;
        if (packet.isValid) {
          checksum[0] += incoming_char;
          checksum[1] += checksum[0];
          byteIdx++;
        }
      } else if (byteIdx == 4) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 4");
        #endif
        packet.payloadLength = incoming_char;
        if (expectedLength > 0) {
          checksum[0] += lowByte(expectedLength);
        }
        checksum[0] += incoming_char;
        checksum[1] += checksum[0];
        byteIdx++;
      } else if (byteIdx == 5) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 5");
        #endif

        packet.payloadLength += incoming_char << 8;

        if (expectedLength > 0) {
          packet.payloadLength = expectedLength;
        }

        checksum[0] += incoming_char;
        checksum[1] += checksum[0];

        #ifdef GNSS_LOG_DEBUG
          Serial.print("payloadLength: ");
          Serial.println(packet.payloadLength);
        #endif

        packet.isValid &= packet.payloadLength <= UBX_PAYLOAD_SIZE;
        byteIdx++;
      } else if (byteIdx >= 6 && byteIdx < 6 + packet.payloadLength) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 6");
        #endif

        if (byteIdx < UBX_PAYLOAD_SIZE) {
          packet.payload[byteIdx - 6] = incoming_char;
          checksum[0] += incoming_char;
          checksum[1] += checksum[0];
          byteIdx++;
        } else {
          #ifdef GNSS_LOG_DEBUG
            Serial.println("UBX packet buffer too short");
          #endif

          packet.isValid = false;
        }
      } else if (byteIdx == 6 + packet.payloadLength) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 7");
        #endif

        packet.checksum[0] = incoming_char;
        byteIdx++;
      } else if (byteIdx == 6 + packet.payloadLength + 1) {
        #ifdef GNSS_LOG_DEBUG
          Serial.println("byte 8");
        #endif

        packet.checksum[1] = incoming_char;
        hasValidChecksum = expectedLength > 0
          || packet.msgId == MessageId::Navigation_PosVT
          || (checksum[0] == packet.checksum[0]
            && checksum[1] == packet.checksum[1]
          );
        packet.isValid &= hasValidChecksum;

        #ifdef GNSS_LOG_DEBUG
          Serial.print("RECV: ");
          Serial.print(packet.checksum[0], HEX);
          Serial.println(packet.checksum[1], HEX);

          Serial.print("CALC: ");
          Serial.print(checksum[0], HEX);
          Serial.println(checksum[1], HEX);
        #endif

        #ifdef GNSS_LOG_INFO
        if (!hasValidChecksum) {
          Serial.println("Invalid checksum");
        }
        #endif

        if (packet.isValid) {
          #ifdef GNSS_LOG_DEBUG
            Serial.println("Parsing packet...");
          #endif

          return parser->parse(&packet);
        }
      }
    }
  }

  UBXMessage* msg = new UBXMessage();
  msg->isValid = false;
  return msg;
}

UBXRequestStatus UBXClient::nextACK(UBXPacket* packet)
{
  double start = (double) millis();
  double end = start + timeout;
  double now = start;

  while (end - now > 0) {
    UBXAck *ack = next(MessageId::ACK_ACK, end - now, 0);

    if (ack->isValid
      && ack->incomingMsgId == packet->msgId
    ) {
      #ifdef GNSS_LOG_DEBUG
        Serial.println("ACK !");
      #endif

      delete ack;
      return UBXRequestStatus::Success;
    }

    delete ack;
    now = millis();
  }

  #ifdef GNSS_LOG_DEBUG
    Serial.println("NACK !");
  #endif

  return UBXRequestStatus::Timeout;
}
