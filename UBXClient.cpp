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

void UBXClient::calcChecksum(UBXMessage* msg)
{
  msg->checksum[0] = highByte(msg->msgId);
  msg->checksum[1] = msg->checksum[0];
  msg->checksum[0] += lowByte(msg->msgId);
  msg->checksum[1] += msg->checksum[0];

  msg->checksum[0] += lowByte(msg->payloadLength);
  msg->checksum[1] += msg->checksum[0];
  msg->checksum[0] += highByte(msg->payloadLength);
  msg->checksum[1] += msg->checksum[0];

  for (int i = 0; i < msg->payloadLength; i++) {
    msg->checksum[0] += msg->payload[i];
    msg->checksum[1] += msg->checksum[0];
  }
}

UBXRequestStatus UBXClient::trySendWithACK(UBXMessage* msg) {
  short tries = 0;
  UBXRequestStatus result;

  while (tries < numTries && result != UBXRequestStatus::Success) {
    #ifdef GNSS_DEBUG
      Serial.print("try ");
      Serial.println(tries + 1);
    #endif

    send(msg);
    result = nextACK(msg);
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
  UBXMessage* msg,
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

    send(msg);
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

void UBXClient::send(UBXMessage* msg)
{
  if (msg->checksum[0] == 0x00 && msg->checksum[1] == 0x00) {
    calcChecksum(msg);
  }

  stream->write(UBX_SYNC_1);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println("sendUBX");
    Serial.println(UBX_SYNC_1, HEX);
  #endif

  stream->write(UBX_SYNC_2);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(UBX_SYNC_2, HEX);
  #endif

  stream->write(highByte(msg->msgId));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(highByte(msg->msgId), HEX);
  #endif

  stream->write(lowByte(msg->msgId));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(lowByte(msg->msgId), HEX);
  #endif

  stream->write(lowByte(msg->payloadLength));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(lowByte(msg->payloadLength), HEX);
  #endif

  stream->write(highByte(msg->payloadLength));
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(highByte(msg->payloadLength), HEX);
  #endif

  for (int i = 0; i < msg->payloadLength; i++)
  {
    stream->write(msg->payload[i]);
    stream->flush();
    #ifdef GNSS_DEBUG
      Serial.println(msg->payload[i], HEX);
    #endif
  }

  if (msg->checksum[0] == 0x00 && msg->checksum[1] == 0x00) {
    calcChecksum(msg);
  }

  stream->write(msg->checksum[0]);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(msg->checksum[0], HEX);
  #endif

  stream->write(msg->checksum[1]);
  stream->flush();
  #ifdef GNSS_DEBUG
    Serial.println(msg->checksum[1], HEX);
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
  UBXMessage *packet = new UBXMessage();
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
      Serial.println("Timeout");
      Serial.println(timeout);
      packet->isValid = false;
      return packet;
    }

    if (stream->available()) {
      incoming_char = stream->read();
      Serial.println(incoming_char, HEX);

      if (!packet->isValid) {
        byteIdx = 0;

        if (incoming_char == UBX_SYNC_1) {
          Serial.println("Incoming packet");
          packet->isValid = true;
          hasValidChecksum = true;
          checksum[0] = 0x00;
          checksum[1] = 0x00;
          classId = NULL;
          memset(packet->payload, 0x00, UBX_MSG_PAYLOAD_SIZE);
          byteIdx++;
        }

        continue;
      }

      if (byteIdx == 1) {
        Serial.println("byte 1");
        packet->isValid = incoming_char == UBX_SYNC_2;
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
        packet->isValid &= packet->payloadLength <= UBX_MSG_PAYLOAD_SIZE;
        byteIdx++;
      } else if (byteIdx >= 6 && byteIdx < 6 + packet->payloadLength) {
        Serial.println("byte 6");
        if (byteIdx < UBX_MSG_PAYLOAD_SIZE) {
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

    Serial.println("ACK received");
    Serial.println(ack->isValid);
    Serial.println(ack->incomingMsgId, HEX);
    Serial.println(msg->msgId, HEX);

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
