class InformationNotice : public UBXMessage {
  InformationNotice() {
    msgId = MessageId::Information_Notice;
  }

  InformationNotice(UBXMessage & msg) {
    isValid = msg.isValid;
    msgId = msg.msgId;
    payloadLength = msg.payloadLength;
    memcpy(payload, msg.payload, UBX_MSG_PAYLOAD_SIZE);
    memcpy(checksum, msg.checksum, 2);
  }

  virtual ~InformationNotice() {}
};
