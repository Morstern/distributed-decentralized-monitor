#ifndef MESSAGE_H
#define MESSAGE_H
#include "../utils/utils.h"
#include "messageType.h"
#include <chrono>
#include <iostream>
#include <string>

class Message {
private:
  std::string requestId;
  long timestamp;
  int port;
  std::string memoryAddress;
  MessageType messageType;
  std::string serializeField(std::string fieldValue, bool isLast);

public:
  Message(std::string serializedMessage);
  Message(std::string requestId, long timestamp, int port,
          std::string memoryAddress, MessageType messageType);
  Message(const Message &message, int port);

  void setMessageType(MessageType newMessageType);

  std::string getRequestId();
  long getTimestamp();
  int getPort();
  std::string getMemoryAddress();
  MessageType getMessageType();

  std::string serializeMessage();
  void deserializeMessage(std::string serializedMessage);

  friend std::ostream &operator<<(std::ostream &os, const Message &message);
  friend bool operator<(const Message &message, const Message &otherMessage);
};
#endif