#include "./test_ricart_agrawala.h"

void runRicartAgrawalaTests() {
  // ---!!!!--- if you want to check those tests,
  // comment: RicartAgrawala::sendMessage function
  // since it depends on ZMQ

  // canEnterCriticalSectionTest_positive();
  // canEnterCriticalSectionTest_negative();
  // exitCriticalSectionTest_positive();
  // removeMessage();
  // replyToOtherRequestsFirst_positive();
}

void canEnterCriticalSectionTest_positive() {

  RicartAgrawala ricartAgrawala{15};
  ricartAgrawala.addNewPortNumber(41);
  ricartAgrawala.addNewPortNumber(42);
  ricartAgrawala.addNewPortNumber(43);
  ricartAgrawala.sendRequestMessage("HEHEHE");

  for (int i = 41; i <= 43; i++) {
    ricartAgrawala.receiveReplyMessage(
        Message{"15_0", 1598271244, i, "HEHEHE", MessageType::REPLY});
  }

  if (ricartAgrawala.canEnterCriticalSection("HEHEHE")) {
    std::cout << "canEnterCriticalSectionTest_positive: POSITIVE" << std::endl;
  } else {
    std::cout << "canEnterCriticalSectionTest_positive: NEGATIVE --- cannot "
                 "enter critical section"
              << std::endl;
  }
}

void canEnterCriticalSectionTest_negative() {
  RicartAgrawala ricartAgrawala{15};
  ricartAgrawala.addNewPortNumber(41);
  ricartAgrawala.addNewPortNumber(42);
  ricartAgrawala.addNewPortNumber(43);
  ricartAgrawala.sendRequestMessage("HEHEHE");

  for (int i = 41; i <= 42; i++) {
    ricartAgrawala.receiveReplyMessage(
        Message{"15_0", 1598271244, i, "HEHEHE", MessageType::REPLY});
  }

  if (ricartAgrawala.canEnterCriticalSection("HEHEHE")) {
    std::cout << "canEnterCriticalSectionTest_positive: NEGATIVE --- can enter "
                 "critical section "
              << std::endl;
  } else {
    std::cout << "canEnterCriticalSectionTest_negative: POSITIVE" << std::endl;
  }
}

void exitCriticalSectionTest_positive() {
  RicartAgrawala ricartAgrawala{15};
  ricartAgrawala.addNewPortNumber(41);
  ricartAgrawala.addNewPortNumber(42);
  ricartAgrawala.addNewPortNumber(43);
  ricartAgrawala.sendRequestMessage("HEHEHE");

  for (int i = 41; i <= 43; i++) {
    ricartAgrawala.receiveReplyMessage(
        Message{"15_0", 1598271244, i, "HEHEHE", MessageType::REPLY});
  }

  if (ricartAgrawala.canEnterCriticalSection("HEHEHE")) {
    ricartAgrawala.exitCriticalSection("HEHEHE");
    if (ricartAgrawala.requestQueueSize() == 0) {
      std::cout << "canEnterCriticalSectionTest_positive: POSITIVE"
                << std::endl;
    } else {
      std::cout << "exitCriticalSectionTest_positive: NEGATIVE --- "
                   "requestQueueSize > 0 "
                << std::endl;
    }
  } else {
    std::cout << "exitCriticalSectionTest_positive: NEGATIVE --- cannot enter "
                 "critical section"
              << std::endl;
  }
}

void removeMessage() {
  RicartAgrawala ricartAgrawala{15};
  ricartAgrawala.addNewPortNumber(43);
  ricartAgrawala.sendRequestMessage("HEHEHE");
  ricartAgrawala.receiveRequestMessage(
      Message{"17_0", (long)1698271244, 43, "HEHEHE", MessageType::REQUEST});
  ricartAgrawala.receiveRequestMessage(
      Message{"17_1", (long)1698271244, 43, "HAHAHA", MessageType::REQUEST});
  ricartAgrawala.receiveRemoveMessage(
      Message{"17_0", (long)1698271244, 43, "HEHEHE", MessageType::REMOVE});

  if (ricartAgrawala.requestQueueSize() == 1) {
    std::cout << "removeMessage: POSITIVE" << std::endl;
  } else {
    std::cout
        << "removeMessage: NEGATIVE --- received message is still in queue"
        << std::endl;
  }
}

void replyToOtherRequestsFirst_positive() {
  RicartAgrawala ricartAgrawala{15};
  ricartAgrawala.addNewPortNumber(41);
  ricartAgrawala.addNewPortNumber(42);
  ricartAgrawala.addNewPortNumber(43);
  ricartAgrawala.receiveRequestMessage(
      Message{"17_0", (long)69, 43, "HEHEHE", MessageType::REQUEST});
  ricartAgrawala.sendRequestMessage("HEHEHE");

  for (int i = 41; i <= 42; i++) {
    ricartAgrawala.receiveReplyMessage(
        Message{"15_0", 1598271244, i, "HEHEHE", MessageType::REPLY});
  }

  if (ricartAgrawala.canEnterCriticalSection("HEHEHE")) {
    ricartAgrawala.exitCriticalSection("HEHEHE");
    if (ricartAgrawala.requestQueueSize() == 0) {
      std::cout << "replyToOtherRequests_positive: NEGATIVE --- "
                   "requestQueueSize should be 1"
                << std::endl;
    } else {
      std::cout
          << "replyToOtherRequests_positive: NEGATIVE --- requestQueueSize>0"
          << std::endl;
    }
  } else {
    ricartAgrawala.receiveReplyMessage(
        Message{"15_0", 1598271244, 43, "HEHEHE", MessageType::REPLY});
    if (ricartAgrawala.canEnterCriticalSection("HEHEHE")) {
      ricartAgrawala.exitCriticalSection("HEHEHE");
      if (ricartAgrawala.requestQueueSize() == 0) {
        std::cout << "replyToOtherRequests_positive: POSITIVE" << std::endl;
      } else {
        std::cout << "replyToOtherRequests_positive: NEGATIVE --- "
                     "requestQueueSize > 0"
                  << std::endl;
      }
    } else {
      std::cout << "replyToOtherRequests_positive: NEGATIVE --- cannot enter "
                   "critical section"
                << std::endl;
    }
  }
}