#ifndef UTILS_H
#define UTILS_H

#include "../message/message.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Forward declaration
class Message;

enum class HelperMessageReceiverOrSender { RECEIVER, SENDER };

class Utils {
private:
  Utils();

public:
  static long getCurrentTimestamp();

  template <typename T> static void displayVector(std::vector<T> vector);

  static std::string createRequestId(int port, int requestId);

  static void outputMessageInformation(Message message, int port,
                                       HelperMessageReceiverOrSender type);

  static std::vector<std::string> split_string(const std::string &txt, char ch);

  static int randomInt();
};

#endif