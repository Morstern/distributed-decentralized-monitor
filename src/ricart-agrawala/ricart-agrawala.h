#ifndef RICART_AGRAWALA_H
#define RICART_AGRAWALA_H

#include "../common/common.h"
#include "../message/message.h"
#include "../utils/utils.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <zmq.h>

class RicartAgrawala {
private:
  std::vector<int> portNumbers;
  std::vector<std::pair<long, Message>> requestQueue;
  std::map<std::string, std::vector<int>> replyReceived;

  void *context;
  int port;
  int requestId;

  void *createZmqSocket(int type);
  void closeZmqSocket(void *socket);

  void sendMessage(Message message, int port);
  void sendReplyMessage(Message message);

  std::string getRequestIdWithMemoryAddress(std::string memoryAddress);
  bool checkIfReceivedAllReplies(std::string memoryAddress);

  Message removeFirstElementFromRequestQueue();
  void removeMessageFromQueue(Message message);

  void sortRequestQueue();

public:
  RicartAgrawala(int port);
  ~RicartAgrawala();

  void sendReplyMessages();
  Message sendRequestMessage(std::string address);
  void sendRemoveMessage(Message message);

  void receiveRequestMessage(Message message);
  void receiveReplyMessage(Message message);
  void receiveRemoveMessage(Message message);

  Message removeMessageWithMessageAddress(std::string memoryAddress);

  bool canEnterCriticalSection(std::string memoryAddress);
  void exitCriticalSection(std::string memoryAddress);

  void removeFromReplyReceived(std::string requestId);
  void addToRequestQueue(Message message);
  int requestQueueSize();

  void addNewPortNumber(int port);
  void removePortNumber(int port);
  void displayPortNumbers();

  void displayMessages();
  int getPort();
};
#endif