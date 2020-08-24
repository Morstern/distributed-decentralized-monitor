#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include "../message/message.h"

// Forward declaration
class Message;


class Utils{
    private:
    Utils();

    public:
    static long getCurrentTimestamp();

    template<typename T>
    static void displayVector(std::vector<T> vector);
    
    static std::string createRequestId(int port, int requestId);

    static void outputMessageInformation(Message message, int port);
};

#endif