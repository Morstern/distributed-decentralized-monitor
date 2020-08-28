#include "message.h"

Message::Message(std::string serializedMessage) {
  deserializeMessage(serializedMessage);
}

Message::Message(std::string _requestId, long _timestamp, int _port,
                 std::string _memoryAddress, MessageType _messageType)
    : requestId{_requestId}, timestamp{_timestamp}, port{_port},
      memoryAddress{_memoryAddress}, messageType{_messageType} {}

Message::Message(const Message &message, int _port) {
  requestId = message.requestId;
  timestamp = Utils::getCurrentTimestamp();
  port = _port;
  memoryAddress = message.memoryAddress;
  messageType = MessageType::REPLY;
}

void Message::setMessageType(MessageType newMessageType) {
  messageType = newMessageType;
}

std::string Message::getRequestId() { return requestId; }

int Message::getPort() { return port; }

long Message::getTimestamp() { return timestamp; }

std::string Message::getMemoryAddress() { return memoryAddress; }

MessageType Message::getMessageType() { return messageType; }

std::string Message::serializeMessage() {
  std::string serialized = "";
  serialized += serializeField(requestId, false);
  serialized += serializeField(std::to_string(timestamp), false);
  serialized += serializeField(std::to_string(port), false);
  serialized += serializeField(memoryAddress, false);
  serialized += serializeField(messagetype_to_string(messageType), true);
  return serialized;
}
std::string Message::serializeField(std::string fieldValue, bool isLast) {
  switch (isLast) {
  case false:
    return fieldValue + ";";

  case true:
    return fieldValue;
  }
}

void Message::deserializeMessage(std::string serializedMessage) {
  std::vector<std::string> fieldsValues =
      Utils::split_string(serializedMessage, ';');
  requestId = fieldsValues[0];
  timestamp = std::stol(fieldsValues[1]);
  port = std::stoi(fieldsValues[2]);
  memoryAddress = fieldsValues[3];
  messageType = string_to_messagetype(fieldsValues[4]);
}

std::ostream &operator<<(std::ostream &os, const Message &message) {
  os << "{" << std::endl;
  os << "Request ID: " << message.requestId << std::endl;
  os << "Port: " << message.port << std::endl;
  os << "Timestamp: " << message.timestamp << std::endl;
  os << "Memory Address: " << message.memoryAddress << std::endl;
  os << "Message type: " << message.messageType << std::endl;
  os << "}" << std::endl;

  return os;
}

bool operator<(const Message &message, const Message &otherMessage) {
  return message.timestamp < otherMessage.timestamp;
}