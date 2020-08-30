#include "ricart-agrawala.h"

void *RicartAgrawala::createZmqSocket(int type) {
  void *newSocket = zmq_socket(context, type);
  return newSocket;
}
void RicartAgrawala::closeZmqSocket(void *socket) { zmq_close(socket); }

void RicartAgrawala::sendMessage(Message message, int _port) {
  void *socket = createZmqSocket(ZMQ_REQ);
  std::string host = HOST_ADDRESS + std::to_string(_port);
  if (zmq_connect(socket, host.c_str()) == 0) {
    std::cout << "Sending to " << host << ": " << message << std::endl;
    std::string serializedMessage = message.serializeMessage();
    zmq_send(socket, serializedMessage.c_str(), serializedMessage.size(), 0);
  } else {
    std::cout << zmq_strerror(zmq_errno()) << std::endl;
  }
  zmq_close(socket);
}

void RicartAgrawala::sendReplyMessage(Message message) {
  Message replyMessage = Message{message, port};
  sendMessage(replyMessage, message.getPort());
}

std::string
RicartAgrawala::getRequestIdWithMemoryAddress(std::string memoryAddress) {

  for (int i = 0; i < requestQueue.size(); i++) {
    if (requestQueue.at(i).second.getMemoryAddress() == memoryAddress) {
      return requestQueue.at(i).second.getRequestId();
    }
  }
  return "";
}

void RicartAgrawala::sortRequestQueue() {
  std::sort(requestQueue.begin(), requestQueue.end(),
            [](const std::pair<long, Message> &x, std::pair<long, Message> &y) {
              return x.first < y.first;
            });
}

RicartAgrawala::RicartAgrawala(int port) : port{port} {
  context = zmq_ctx_new();
  requestId = 0;
}

RicartAgrawala::~RicartAgrawala() { zmq_ctx_destroy(context); }

void RicartAgrawala::sendReplyMessages() {
  std::vector<std::string> requestedMemoryAddresses{};
  for (int i = 0; i < requestQueue.size(); i++) {
    if (requestQueue.at(i).second.getPort() == port) {
      requestedMemoryAddresses.push_back(
          requestQueue.at(i).second.getMemoryAddress());
      continue;
    } else if (std::count(requestedMemoryAddresses.begin(),
                          requestedMemoryAddresses.end(),
                          requestQueue.at(i).second.getMemoryAddress()) == 0) {
      Message message = requestQueue.at(i).second;
      Message replyMessage = Message{message, port};
      sendMessage(replyMessage, message.getPort());
      removeMessageFromQueue(message);
    }
  }
}

void RicartAgrawala::removeMessageFromQueue(Message message) {
  for (int i = 0; i < requestQueue.size(); i++) {
    if (message.getRequestId() == requestQueue.at(i).second.getRequestId()) {
      requestQueue.erase(requestQueue.begin() + i);
      break;
    }
  }
}

Message RicartAgrawala::sendRequestMessage(std::string address) {
  long timestamp = Utils::getCurrentTimestamp();
  std::string s_requestId = Utils::createRequestId(port, requestId);
  Message message{s_requestId, timestamp, port, address, MessageType::REQUEST};
  addToRequestQueue(message);
  for (int i = 0; i < portNumbers.size(); i++) {
    sendMessage(message, portNumbers.at(i));
  }
  requestId++;
  return message;
}

void RicartAgrawala::sendRemoveMessage(Message message) {
  message.setMessageType(MessageType::REMOVE);
  for (int i = 0; i < portNumbers.size(); i++) {
    sendMessage(message, portNumbers.at(i));
  }
}

void RicartAgrawala::receiveRequestMessage(Message message) {
  // Utils::outputMessageInformation(message, message.getPort(), HelperMessageReceiverOrSender::RECEIVER);
  if (requestQueue.size() == 0) {
    sendReplyMessage(message);
  } else {
    addToRequestQueue(message);
  }
}

void RicartAgrawala::addToRequestQueue(Message message) {
  requestQueue.push_back(
      std::pair<long, Message>{message.getTimestamp(), message});
  sortRequestQueue();
  sendReplyMessages();
}

void RicartAgrawala::receiveReplyMessage(Message message) {
  // Utils::outputMessageInformation(message, port, HelperMessageReceiverOrSender::RECEIVER);
  std::vector<int> replies;
  if (replyReceived.count(message.getRequestId())) {
    replies = replyReceived[message.getRequestId()];
    replies.push_back(message.getPort());
    replyReceived[message.getRequestId()] = replies;
  } else {
    replies.push_back(message.getPort());
    replyReceived[message.getRequestId()] = replies;
  }
}

void RicartAgrawala::receiveRemoveMessage(Message message) {
  // Utils::outputMessageInformation(message, port, HelperMessageReceiverOrSender::RECEIVER);
  removeMessageFromQueue(message);
  sendReplyMessages();
}

Message
RicartAgrawala::removeMessageWithMessageAddress(std::string memoryAddress) {
  Message message{"", (long)-1, -1, "", MessageType::REMOVE};
  for (int i = 0; i < requestQueue.size(); i++) {
    if (requestQueue.at(i).second.getPort() == port &&
        requestQueue.at(i).second.getMemoryAddress() == memoryAddress) {
      Message message2 = requestQueue.at(i).second;
      requestQueue.erase(requestQueue.begin() + i);
      return message2;
    }
  }
  sendReplyMessages();
  return message;
}

bool RicartAgrawala::canEnterCriticalSection(std::string memoryAddress) {
  if (requestQueue.size() > 0) {
    if (checkIfReceivedAllReplies(memoryAddress)) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool RicartAgrawala::checkIfReceivedAllReplies(std::string memoryAddress) {
  return replyReceived[getRequestIdWithMemoryAddress(memoryAddress)].size() ==
         portNumbers.size();
}

void RicartAgrawala::exitCriticalSection(std::string memoryAddress) {
  Message message = removeFirstElementFromRequestQueue();
  removeFromReplyReceived(message.getRequestId());
  sendReplyMessages();
}

void RicartAgrawala::removeFromReplyReceived(std::string requestId) {
  replyReceived.erase(requestId);
}

Message RicartAgrawala::removeFirstElementFromRequestQueue() {
  Message message = requestQueue.at(0).second;
  requestQueue.erase(requestQueue.begin());
  return message;
}

int RicartAgrawala::requestQueueSize() { return requestQueue.size(); }

void RicartAgrawala::addNewPortNumber(int port) { portNumbers.push_back(port); }

void RicartAgrawala::removePortNumber(int port) {
  int index;
  if (index = std::find(portNumbers.begin(), portNumbers.end(), port) !=
              portNumbers.end()) {
    portNumbers.erase(portNumbers.begin() + index);
  }
}

void RicartAgrawala::displayPortNumbers() { Utils::displayVector(portNumbers); }

int RicartAgrawala::getPort() { return port; }

void RicartAgrawala::displayMessages() {
  std::cout << "----" << std::endl;
  std::cout << "Wektor requestQueue" << std::endl;
  Utils::displayVector(requestQueue);
  std::cout << "----" << std::endl;
}
