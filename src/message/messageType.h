#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H
#include <iostream>


enum class MessageType {
    REQUEST,
    REPLY
};
std::ostream& operator<<(std::ostream& os, const MessageType& messageType);
#endif