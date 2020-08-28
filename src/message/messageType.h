#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H
#include <iostream>

// TODO: REMOVE -> send REMOVE message when wait timer expires
enum class MessageType { REQUEST, REPLY, REMOVE };

std::string messagetype_to_string(const MessageType &messageType);
MessageType string_to_messagetype(const std::string &s_messageType);

std::ostream &operator<<(std::ostream &os, const MessageType &messageType);
#endif