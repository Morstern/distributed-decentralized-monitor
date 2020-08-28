#ifndef MONITOR_H
#define MONITOR_H
#include "../common/common.h"
#include "../ricart-agrawala/ricart-agrawala.h"
#include "zmq.h"
#include <cstring>
#include <iostream>
#include <thread>

// NA DZISIAJ
// TODO: przesylanie wiadomosci
// TODO: przesylanie struktury message

class Monitor {
  RicartAgrawala ricartAgrawala;
  void *context;
  void *receiveSocket;
  void handleReceivingMessages();
  void processMessage();
  void destroyContext();

public:
  Monitor(int port, std::vector<int> otherPorts);
  ~Monitor();
  void enter(std::string memoryAddress);
  void tryEnter(std::string memoryAddress, int ms);
  void pulseAll(std::string memoryAddress);
  void wait(std::string memoryAddress);
  void exit(std::string memoryAddress);
  bool isEntered(std::string memoryAddress);
};

#endif