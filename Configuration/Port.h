class ConfigurationPort : public UBXMessage {
  public:
    PortId portId;
    uint16_t txReady;
    uint32_t mode;
    PortRate baudRate;
    uint16_t inProtoMask;
    uint16_t outProtoMask;
    uint16_t flags;
    bool hasNext;
    ConfigurationPort* next;

    ConfigurationPort() {
      msgId = MessageId::Configuration_Port;
    }

    ConfigurationPort(UBXMessage *msg) {
      isValid = msg->isValid;
      msgId = msg->msgId;
    }

    virtual ~ConfigurationPort() {}

    bool isTxReadyEnabled() {
      return bool(txReady & 0x1);
    }

    bool isLowActivePolarityEnabled() {
      return bool(txReady & 0x2);
    }

    uint8_t getPin() {
      return uint8_t(txReady >> 2) & 0x1F;
    }

    uint16_t getThreshold() {
      return uint16_t(txReady >> 7) & 0x1FF;
    }

    uint8_t getCharacterLength() {
      if (portId != PortId::UART) {
        return 0;
      }

      return 5 + (uint8_t(mode >> 6) & 0x3);
    }

    bool isOdd() {
      if (portId != PortId::UART) {
        return false;
      }

      return bool(mode & 0x200);
    }

    bool isParityDisabled() {
      if (portId != PortId::UART) {
        return false;
      }

      return bool(mode & 0x800);
    }

    bool isHalfStopBitsEnabled() {
      if (portId != PortId::UART) {
        return false;
      }

      return bool(mode & 0x1000);
    }

    bool isSecondStopBitEnabled() {
      if (portId != PortId::UART) {
        return false;
      }

      return bool(mode & 0x2000);
    }

    bool isSpiCPHAEnabled() {
      if (portId != PortId::SPI) {
        return false;
      }

      return bool(mode & 0x2);
    }

    bool isSpiCPOLEnabled() {
      if (portId != PortId::SPI) {
        return false;
      }

      return bool(mode & 0x4);
    }

    bool isSpiFlowControlEnabled() {
      if (portId != PortId::SPI) {
        return false;
      }

      return bool(mode & 0x40);
    }

    uint8_t getSpiFFCount() {
      if (portId != PortId::SPI) {
        return 0;
      }

      return uint8_t(mode >> 8);
    }

    uint8_t getDDCSlaveAddress() {
      if (portId != PortId::DDC) {
        return 0;
      }

      return uint8_t(mode >> 1);
    }

    bool isUBXInputEnabled() {
      return bool(inProtoMask & 0x1);
    }

    bool isNMEAInputEnabled() {
      return bool(inProtoMask & 0x2);
    }

    bool isRTCMInputEnabled() {
      return bool(inProtoMask & 0x4);
    }

    bool isUBXOutputEnabled() {
      return bool(outProtoMask & 0x1);
    }

    bool isNMEAOutputEnabled() {
      return bool(outProtoMask & 0x2);
    }

    bool isExtendedTxTimeoutEnabled() {
      return bool(flags & 0x2);
    }

    virtual void print(Stream* stream) {
      stream->println(F("ConfigurationPort"));

      if (!isValid) {
        stream->println(F("Invalid"));
        stream->println();
        return;
      }

      stream->print(F("portId: "));
      stream->println((uint8_t)portId);

      stream->print(F("txReady: "));
      stream->println(txReady);

      stream->print(F("Is Tx Ready enabled ?: "));
      stream->println(isTxReadyEnabled());

      stream->print(F("Is low-active polarity enabled ?: "));
      stream->println(isLowActivePolarityEnabled());

      stream->print(F("PIO-Pin : "));
      stream->println(getPin());

      stream->print(F("Threshold : "));
      stream->print(getThreshold());
      stream->println(" * 8 bytes");

      stream->print(F("mode: 0x"));
      stream->println(mode, HEX);

      switch (portId) {
        case PortId::UART:
          stream->print(F("Character length: "));
          stream->print(getCharacterLength());
          stream->println("bits");

          stream->print(F("Odd parity ? : "));
          stream->println(isOdd());

          stream->print(F("Is parity disabled ? : "));
          stream->println(isParityDisabled());

          stream->print(F("Is half stop bits enabled  ? : "));
          stream->println(isHalfStopBitsEnabled());

          stream->print(F("Is there 2 stop bits ? : "));
          stream->println(isSecondStopBitEnabled());
          break;
        case PortId::SPI:
          stream->print(F("Is SPI CPHA enabled ? : "));
          stream->println(isSpiCPHAEnabled());

          stream->print(F("Is SPI CPOL enabled ? : "));
          stream->println(isSpiCPOLEnabled());

          stream->print(F("Is SPI flow control enabled ? : "));
          stream->println(isSpiFlowControlEnabled());

          stream->print(
            F("SPI 0xFF bytes count before switching off reception : ")
          );
          stream->println(getSpiFFCount());
          break;
        case PortId::DDC:
          stream->print(F("DDC slave address : "));
          stream->println(getDDCSlaveAddress());
          break;
      }

      stream->print(F("baudRate: "));
      stream->print((uint32_t)baudRate);
      stream->println(F("bauds"));

      stream->print(F("inProtoMask: 0x"));
      stream->println(inProtoMask, HEX);

      stream->print(F("Is UBX input enabled ? : "));
      stream->println(isUBXInputEnabled());

      stream->print(F("Is NMEA input enabled ? : "));
      stream->println(isNMEAInputEnabled());

      stream->print(F("Is RTCM input enabled ? : "));
      stream->println(isRTCMInputEnabled());

      stream->print(F("outProtoMask: 0x"));
      stream->println(outProtoMask, HEX);

      stream->print(F("Is UBX output enabled ? : "));
      stream->println(isUBXOutputEnabled());

      stream->print(F("Is NMEA output enabled ? : "));
      stream->println(isNMEAOutputEnabled());

      stream->print(F("flags: 0x"));
      stream->println(flags, HEX);

      stream->print(F("Is extended Tx timeout enabled ? : "));
      stream->println(isExtendedTxTimeoutEnabled());

      stream->println();

      if (hasNext) {
        next->print(stream);
      }
    }
};
