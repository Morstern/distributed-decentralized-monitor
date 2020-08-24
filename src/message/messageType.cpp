#include "messageType.h"

std::ostream& operator<<(std::ostream& os, const MessageType& messageType){
    switch(messageType){
        case MessageType::REPLY:
        {
        os<<"REPLY";
        break;
        }
        case MessageType::REQUEST:
        {
            os<<"REQUEST";
             break;
        }
    }
    return os;
}