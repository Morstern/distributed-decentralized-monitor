#include "monitor.h"

void Monitor::handleReceivingMessages() {
  int len;
  char *buffer = new char[BUFFER_SIZE];
  while (true) {
    memset(buffer, 0, BUFFER_SIZE);
    if (zmq_recv(receiveSocket, buffer, BUFFER_SIZE, 0) > -1) {
      zmq_send(receiveSocket, "", 0, 0);
      std::string serializedMessage =
          std::string(reinterpret_cast<char const *>(buffer),
                      std::char_traits<char>::length(buffer));
      Message message{serializedMessage};
      switch (message.getMessageType()) {
      case MessageType::REMOVE: {
        ricartAgrawala.receiveRemoveMessage(message);
        break;
      }
      case MessageType::REPLY: {
        ricartAgrawala.receiveReplyMessage(message);
        break;
      }
      case MessageType::REQUEST: {
        ricartAgrawala.receiveRequestMessage(message);
        break;
      }
      case MessageType::PING: {
        //
      }
      }
    }
  }
}

void Monitor::destroyContext() { zmq_ctx_destroy(context); }

Monitor::Monitor(int port, std::vector<int> otherPorts) : ricartAgrawala(port) {
  context = zmq_ctx_new();
  receiveSocket = zmq_socket(context, ZMQ_REP);
  std::string host = "tcp://127.0.0.1:" + std::to_string(port);
  zmq_bind(receiveSocket, host.c_str());
  std::cout << "Initialized with address: " << host << std::endl;
  for (const int &otherPort : otherPorts) {
    ricartAgrawala.addNewPortNumber(otherPort);
  }
  std::cout << "Has those other ports:" << std::endl;
  ricartAgrawala.displayPortNumbers();
  std::thread handlerThread(&Monitor::handleReceivingMessages, this);
  handlerThread.detach();
}

Monitor::~Monitor() {
  zmq_close(receiveSocket);
  destroyContext();
}

void Monitor::enter(std::string memoryAddress) {
  ricartAgrawala.sendRequestMessage(memoryAddress);
  while (!ricartAgrawala.canEnterCriticalSection(memoryAddress)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  std::cout << "Monitor with port: [" << ricartAgrawala.getPort()
            << "] has entered the: [" << memoryAddress << "]" << std::endl;
}

void Monitor::tryEnter(std::string memoryAddress, int ms) {
  Message message = ricartAgrawala.sendRequestMessage(memoryAddress);
  int totalTimeSpentForWaiting = 0;
  while (!ricartAgrawala.canEnterCriticalSection(memoryAddress) ||
         totalTimeSpentForWaiting < ms) {
    totalTimeSpentForWaiting += 250;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }

  if (ricartAgrawala.canEnterCriticalSection(memoryAddress)) {
    std::cout << "Monitor with port: [" << ricartAgrawala.getPort()
              << "] has entered the: [" << memoryAddress << "]" << std::endl;
  } else {
    ricartAgrawala.removeFromReplyReceived(message.getRequestId());
    std::cout << "Monitor with port: [" << ricartAgrawala.getPort()
              << "] could not enter the: [" << memoryAddress
              << "] he waited for: " << ms << "ms" << std::endl;
  }
}

void Monitor::wait(std::string memoryAddress) {
  Message message =
      ricartAgrawala.removeMessageWithMessageAddress(memoryAddress);
  ricartAgrawala.sendRemoveMessage(message);
  ricartAgrawala.sendRequestMessage(memoryAddress);

  while (!ricartAgrawala.canEnterCriticalSection(memoryAddress)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  std::cout << "Monitor with port: [" << ricartAgrawala.getPort()
            << "] has entered the: [" << memoryAddress << "]" << std::endl;
}

void Monitor::exit(std::string memoryAddress) {
  Message message =
      ricartAgrawala.removeMessageWithMessageAddress(memoryAddress);
  ricartAgrawala.sendReplyMessages();
}

bool Monitor::isEntered(std::string memoryAddress) {
  return ricartAgrawala.canEnterCriticalSection(memoryAddress);
}