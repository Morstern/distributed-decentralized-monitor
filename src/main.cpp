#include "./tests/test_message.h"
#include "./tests/test_monitor.h"
#include "./tests/test_ricart_agrawala.h"
#include <thread>

// HOW TO RUN:
// ./a.out test -> run tests
// ./a.out monitor MODE{1,2,3} OWN_PORT OTHER_PORT_1 OTHER_PORT_2 OTHER_PORT_3...
// for example: 4 console windows:
// [console_1] ./a.out monitor 1 10000 10001 10002 10003
// [console_2] ./a.out monitor 3 10001 10000 10002 10003
// [console_3] ./a.out monitor 2 10002 10000 10001 10003
// [console_4] ./a.out monitor 2 10003 10001 10002 10000

const std::string TEST = "test";
const std::string MONITOR = "monitor";

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Please pass proper arguments" << std::endl;
    return -1;
  }

  if (argv[1] == TEST) {
    runMessageTests();
    runMonitorTests();
    runRicartAgrawalaTests();

  } else if (argv[1] == MONITOR) {

    int port = std::stoi(argv[3]);

    std::vector<int> otherPorts{};
    for (int i = 4; i < argc; i++) {
      otherPorts.push_back(std::stoi(argv[i]));
    }
    Monitor monitor{port, otherPorts};

    std::cout << "Press enter if others monitors are initialized: "
              << std::endl;
    std::cin.get();
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    switch (std::stoi(argv[2])) {
    case 1: {
      std::cout << "CASE 1" << std::endl;
      monitor.enter("TEST_A");
      std::cout << "Czy monitor ma dostep do [TEST_A]: "
                << monitor.isEntered("TEST_A") << std::endl;

      monitor.exit("TEST_A");
      while (true) {
        std::cout << "KONIEC" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
      break;
    }

    case 2: {
      std::cout << "CASE 2" << std::endl;
      monitor.enter("TEST_A");
      monitor.wait("TEST_A");
      monitor.enter("TEST_B");
      std::cout << "Czy monitor ma dostep do [TEST_A]: "
                << monitor.isEntered("TEST_A") << std::endl;
      std::cout << "Czy monitor ma dostep do [TEST_B]: "
                << monitor.isEntered("TEST_B") << std::endl;
      monitor.exit("TEST_A");
      monitor.exit("TEST_B");
      while (true) {
        std::cout << "KONIEC" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
      break;
    }

    case 3: {
      std::cout << "CASE 3" << std::endl;
      while (true) {
        monitor.enter("TEST_A");
        monitor.tryEnter("TEST_B", 2000);
        if (!monitor.isEntered("TEST_B")) {
          monitor.exit("TEST_A");
        } else {
          break;
        }
      }

      std::cout << "Czy monitor ma dostep do [TEST_A]: "
                << monitor.isEntered("TEST_A") << std::endl;
      std::cout << "Czy monitor ma dostep do [TEST_B]: "
                << monitor.isEntered("TEST_B") << std::endl;
      monitor.exit("TEST_A");
      monitor.exit("TEST_B");
      while (true) {
        std::cout << "KONIEC" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
      break;
    }
    }
  } else {
    std::cout << "Invalid argument: " << argv[1] << std::endl;
  }
}