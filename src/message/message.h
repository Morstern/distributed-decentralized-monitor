#ifndef MESSAGE_H
#define MESSAGE_H
#include <chrono>
#include <string>
#include <iostream>
#include "messageType.h"
#include "../utils/utils.h"

class Message {
    private:
    std::string requestId;
    long timestamp;
    int port;
    std::string memoryAddress;
    MessageType messageType;


    public:
    Message(std::string requestId, long timestamp, int port, std::string memoryAddress, MessageType messageType);
    Message(const Message& message, int port);
    std::string getRequestId();
    long getTimestamp();
    int getPort();
    std::string getMemoryAddress();
    MessageType getMessageType();
    


    friend std::ostream& operator<<(std::ostream& os, const Message& message);
    friend bool operator<(const Message& message, const Message& otherMessage);
};
#endif