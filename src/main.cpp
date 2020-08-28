#include "./tests/test_message.h"
#include "./tests/test_monitor.h"
#include "./tests/test_ricart_agrawala.h"
#include <thread>

// HOW TO RUN:
// ./a.out test -> run tests
// ./a.out monitor MODE OWN_PORT OTHER_PORT_1 OTHER_PORT_2 OTHER_PORT_3...

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
      monitor.enter("TEST_1");
      std::cout << "Czy monitor ma dostep do [TEST_1]: "
                << monitor.isEntered("TEST_1") << std::endl;

      monitor.exit("TEST_1");
      std::cout << "KONIEC" << std::endl;
      while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
      break;
    }
    case 2: {
      std::cout << "CASE 2" << std::endl;
      monitor.enter("TEST_1");
      while (true) {
        monitor.tryEnter("TEST_2", 2000);
        if (!monitor.isEntered("TEST_2")) {
          monitor.exit("TEST_1");
          monitor.enter("TEST_1");
        } else {
          break;
        }
      }

      std::cout << "Czy monitor ma dostep do [TEST_1]: "
                << monitor.isEntered("TEST_1") << std::endl;
      std::cout << "Czy monitor ma dostep do [TEST_2]: "
                << monitor.isEntered("TEST_2") << std::endl;
      monitor.exit("TEST_1");
      monitor.exit("TEST_2");
      std::cout << "KONIEC" << std::endl;
      while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      }
      break;

      break;
    }
    case 3: {
      std::cout << "CASE 3" << std::endl;

      break;
    }
    case 4: {
      std::cout << "CASE 4" << std::endl;

      break;
    }
    }
  } else {
    std::cout << "Invalid argument: " << argv[1] << std::endl;
  }
}