#include "GNSS.h"

UBXClient::UBXClient(
  Stream *s,
  unsigned short numTries,
  unsigned int timeout
) {
  stream = s;

  parser = new UBXParser();
  numTries = numTries;
  timeout = timeout;
}

void UBXClient::calcChecksum(UBXPacket* packet)
{
  packet->checksum[0] = highByte(packet->msgId);
  packet->checksum[1] = packet->checksum[0];
  packet->checksum[0] += lowByte(packet->msgId);
  packet->checksum[1] += packet->checksum[0];

  packet->checksum[0] += lowByte(packet->payloadLength);
  packet->checksum[1] += packet->checksum[0];
  packet->checksum[0] += highByte(packet->payloadLength);
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
    #ifdef GNSS_DEBUG
      Serial.print("try ");
      Serial.println(tries + 1);
    #endif

    send(packet);
    result = nextACK(packet);
    tries++;
  }

  #ifdef GNSS_DEBUG
    if (tries == numTries && result != UBXRequestStatus::Success) {
      Serial.println("Failed UBX message with ACK.");
    }
  #endif

  return result;
}

UBXMessage* UBXClient::trySend(
  UBXPacket* packet,
  MessageId expectedResponseMsgId
) {
  UBXMessage* result = new UBXMessage();
  result->isValid = false;
  short tries = 0;

  while (tries < numTries && !result->isValid) {
    #ifdef GNSS_DEBUG
      Serial.print("try ");
      Serial.println(tries + 1);
    #endif

    send(packet);
    result = next(expectedResponseMsgId);
    if (result->isValid) {
      return result;
    }
    tries++;
  }

  #ifdef GNSS_DEBUG
    if (tries == numTries && !result->isValid) {
      Serial.print("Failed UBX message. Expecting: ");
      Serial.println(expectedResponseMsgId);
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
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println("sendUBX");
    Serial.println(SYNC_1, HEX);
  #endif

  stream->write(SYNC_2);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(SYNC_2, HEX);
  #endif

  stream->write(highByte(packet->msgId));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(highByte(packet->msgId), HEX);
  #endif

  stream->write(lowByte(packet->msgId));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(lowByte(packet->msgId), HEX);
  #endif

  stream->write(lowByte(packet->payloadLength));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(lowByte(packet->payloadLength), HEX);
  #endif

  stream->write(highByte(packet->payloadLength));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(highByte(packet->payloadLength), HEX);
  #endif

  for (int i = 0; i < packet->payloadLength; i++)
  {
    stream->write(packet->payload[i]);
    stream->flush();
    #ifdef GNSS_DEBUG
      Serial.println(packet->payload[i], HEX);
    #endif
  }

  if (packet->checksum[0] == 0x00 && packet->checksum[1] == 0x00) {
    calcChecksum(packet);
  }

  stream->write(packet->checksum[0]);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(packet->checksum[0], HEX);
  #endif

  stream->write(packet->checksum[1]);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(packet->checksum[1], HEX);
    Serial.println("end sendUBX");
  #endif

  stream->println();
  stream->flush();
}

UBXMessage* UBXClient::next(MessageId expectedId) {
  return next(expectedId, timeout);
}

UBXMessage* UBXClient::next(MessageId expectedId, unsigned int timeout)
{
  UBXPacket *packet = new UBXPacket();
  packet->isValid = false;
  uint8_t incoming_char;
  int byteIdx = 0;
  bool hasValidChecksum = true;
  uint16_t msgLength = 0;
  byte checksum[2] = { 0x00, 0x00 };
  unsigned long start = millis();
  MessageClass classId;

  while (true) {
    if (millis() - start > timeout) {
      #ifdef GNSS_DEBUG
        Serial.println("Timeout");
        Serial.println(timeout);
      #endif

      packet->isValid = false;
      return packet;
    }

    if (stream->available()) {
      incoming_char = stream->read();
      #ifdef GNSS_DEBUG
        Serial.println(incoming_char, HEX);
      #endif

      if (!packet->isValid) {
        byteIdx = 0;

        if (incoming_char == SYNC_1) {
          #ifdef GNSS_DEBUG
            Serial.println("Incoming packet");
          #endif

          packet->isValid = true;
          hasValidChecksum = true;
          checksum[0] = 0x00;
          checksum[1] = 0x00;
          classId = NULL;
          memset(packet->payload, 0x00, UBXPacket::PAYLOAD_SIZE);
          byteIdx++;
        }

        continue;
      }

      if (byteIdx == 1) {
        Serial.println("byte 1");
        packet->isValid = incoming_char == SYNC_2;
        byteIdx++;
      } else if (byteIdx == 2) {
        Serial.println("byte 2");
        classId = (MessageClass) incoming_char;
        checksum[0] = incoming_char;
        checksum[1] = checksum[0];
        byteIdx++;
      } else if (byteIdx == 3) {
        Serial.println("byte 3");
        packet->msgId = (MessageId)(classId << 8 | incoming_char);
        packet->isValid = expectedId == MessageId::None
          || packet->msgId == expectedId;
        if (packet->isValid) {
          checksum[0] += incoming_char;
          checksum[1] += checksum[0];
          byteIdx++;
        }
      } else if (byteIdx == 4) {
        Serial.println("byte 4");
        packet->payloadLength = incoming_char;
        checksum[0] += incoming_char;
        checksum[1] += checksum[0];
        byteIdx++;
      } else if (byteIdx == 5) {
        Serial.println("byte 5");
        packet->payloadLength += incoming_char << 8;
        checksum[0] += incoming_char;
        checksum[1] += checksum[0];

        Serial.print("payloadLength: ");
        Serial.println(packet->payloadLength);
        packet->isValid &= packet->payloadLength <= UBXPacket::PAYLOAD_SIZE;
        byteIdx++;
      } else if (byteIdx >= 6 && byteIdx < 6 + packet->payloadLength) {
        Serial.println("byte 6");
        if (byteIdx < UBXPacket::PAYLOAD_SIZE) {
          packet->payload[byteIdx - 6] = incoming_char;
          checksum[0] += incoming_char;
          checksum[1] += checksum[0];
          byteIdx++;
        } else {
          Serial.println("UBX packet buffer too short");
          packet->isValid = false;
        }
      } else if (byteIdx == 6 + packet->payloadLength) {
        Serial.println("byte 7");
        packet->checksum[0] = incoming_char;
        byteIdx++;
      } else if (byteIdx == 6 + packet->payloadLength + 1) {
        Serial.println("byte 8");
        packet->checksum[1] = incoming_char;
        hasValidChecksum = packet->msgId == MessageId::Navigation_PosVT
          || (checksum[0] == packet->checksum[0]
            && checksum[1] == packet->checksum[1]
          );
        packet->isValid &= hasValidChecksum;

        #ifdef GNSS_DEBUG
          Serial.print("RECV: ");
          Serial.print(packet->checksum[0], HEX);
          Serial.println(packet->checksum[1], HEX);

          Serial.print("CALC: ");
          Serial.print(checksum[0], HEX);
          Serial.println(checksum[1], HEX);
        #endif

        if (packet->isValid) {
          #ifdef GNSS_DEBUG
            Serial.println("Parsing packet...");
          #endif

          return parser->parse(packet);
        }
      }
    }
  }

  return packet;
}

UBXRequestStatus UBXClient::nextACK(UBXMessage* msg)
{
  UBXAck *ack;
  double start = (double) millis();
  double end = start + timeout;
  double now = start;

  while (end - now > 0) {
    ack = static_cast<UBXAck*>(next(MessageId::ACK_ACK, end - now));

    #ifdef GNSS_DEBUG
      Serial.println("ACK received");
      Serial.println(ack->isValid);
      Serial.println(ack->incomingMsgId, HEX);
      Serial.println(msg->msgId, HEX);
    #endif

    if (ack->isValid
      && ack->incomingMsgId == msg->msgId
    ) {
      #ifdef GNSS_DEBUG
        Serial.println("ACK !");
      #endif

      return UBXRequestStatus::Success;
    }

    now = millis();
  }

  #ifdef GNSS_DEBUG
    Serial.println("NACK !");
  #endif

  return UBXRequestStatus::Timeout;
}
