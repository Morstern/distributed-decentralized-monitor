#include "utils.h"

long Utils::getCurrentTimestamp() {
  return std::chrono::milliseconds(std::time(NULL)).count();
}

template <> void Utils::displayVector(std::vector<int> vector) {
  for (int i = 0; i < vector.size(); i++) {
    std::cout << "i[" + std::to_string(i) + "]: " << vector.at(i) << std::endl;
  }
}

template <>
void Utils::displayVector(std::vector<std::pair<long, Message>> vector) {
  for (int i = 0; i < vector.size(); i++) {
    std::cout << "[" + std::to_string(i) + "]:" << std::endl;
    std::cout << "{" << std::endl
              << vector.at(i).second << std::endl
              << "}" << std::endl;
  }
}

std::string Utils::createRequestId(int port, int requestId) {

  std::string s_port = std::to_string(port);
  std::string s_requestId = std::to_string(requestId);

  return std::string(s_port + "_" + s_requestId);
}

void Utils::outputMessageInformation(Message message, int _port,
                                     HelperMessageReceiverOrSender type) {
  switch (message.getMessageType()) {
  case MessageType::REQUEST: {
    std::cout << "-----------" << std::endl;
    if (type == HelperMessageReceiverOrSender::SENDER) {
      std::cout << "Wysylam [REQUEST] do: " << _port << std::endl;
      std::cout << "Wiadomosc: {" << std::endl << message << "}" << std::endl;
    } else {
      std::cout << "Odbieram [REQUEST] od: " << message.getPort() << std::endl;
      std::cout << "Wiadomosc: {" << std::endl << message << "}" << std::endl;
    }
    std::cout << "-----------" << std::endl;
    break;
  }
  case MessageType::REPLY: {
    std::cout << "-----------" << std::endl;
    if (type == HelperMessageReceiverOrSender::SENDER) {
      std::cout << "Wysylam [REPLY] do: " << _port << std::endl;
      std::cout << "Wiadomosc: {" << std::endl << message << "}" << std::endl;
    } else {
      std::cout << "Odbieram [REPLY] od: " << message.getPort() << std::endl;
      std::cout << "Wiadomosc: {" << std::endl << message << "}" << std::endl;
    }
    std::cout << "-----------" << std::endl;
    break;
  }
  case MessageType::REMOVE: {
    std::cout << "-----------" << std::endl;
    if (type == HelperMessageReceiverOrSender::SENDER) {
      std::cout << "Wysylam [REMOVE] do: " << _port << std::endl;
      std::cout << "Wiadomosc: {" << std::endl << message << "}" << std::endl;
    } else {
      std::cout << "Odbieram [REMOVE] od: " << message.getPort() << std::endl;
      std::cout << "Wiadomosc: {" << std::endl << message << "}" << std::endl;
    }
    std::cout << "-----------" << std::endl;
    break;
  }
  }
}

// https://stackoverflow.com/questions/5888022/split-string-by-single-spaces --
// NIE MOJ KOD
std::vector<std::string> Utils::split_string(const std::string &txt, char ch) {
  std::vector<std::string> strs;
  size_t pos = txt.find(ch);
  size_t initialPos = 0;
  strs.clear();

  // Decompose statement
  while (pos != std::string::npos) {
    strs.push_back(txt.substr(initialPos, pos - initialPos));
    initialPos = pos + 1;

    pos = txt.find(ch, initialPos);
  }

  // Add the last one
  strs.push_back(
      txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
  return strs;
}

int Utils::randomInt() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1, 10);
  return dist(mt);
}