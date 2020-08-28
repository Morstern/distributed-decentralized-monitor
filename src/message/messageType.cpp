#include "messageType.h"

std::string messagetype_to_string(const MessageType &messageType) {
  switch (messageType) {
  case MessageType::REPLY: {
    return "REPLY";
  }
  case MessageType::REQUEST: {
    return "REQUEST";
  }
  case MessageType::REMOVE: {
    return "REMOVE";
  }
  default: {
    return "REPLY";
  }
  }
}

MessageType string_to_messagetype(const std::string &s_messageType) {
  if (s_messageType == "REPLY") {
    return MessageType::REPLY;
  } else if (s_messageType == "REQUEST") {
    return MessageType::REQUEST;
  } else {
    return MessageType::REMOVE;
  }
}

std::ostream &operator<<(std::ostream &os, const MessageType &messageType) {
  os << messagetype_to_string(messageType);
  return os;
}