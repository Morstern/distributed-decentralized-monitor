#include "test_monitor.h"

void runMonitorTests() { is_monitorProperlyInitialized(); }

void is_monitorProperlyInitialized() {
  std::vector<int> otherPorts = {42, 43, 44};
  Monitor monitor{41, otherPorts};
}