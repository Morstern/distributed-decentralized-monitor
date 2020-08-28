#include "./test_message.h"

void runMessageTests() {
  is_serializedProperly();
  is_deserializedProperly();
}
void is_serializedProperly() {
  Message mes{"15_0", 1598271244, 43, "HEHEHE", MessageType::REPLY};
  std::string serializedMessage = mes.serializeMessage();
  if (serializedMessage == "15_0;1598271244;43;HEHEHE;REPLY") {
    std::cout << "is_serializedProperly: POSITIVE" << std::endl;
  } else {
    std::cout << "is_serializedProperly: NEGATIVE" << std::endl;
  }
}
void is_deserializedProperly() {
  std::string serializedMessage = "15_0;1598271244;43;HEHEHE;REPLY";
  Message message{serializedMessage};

  if (message.getRequestId() == "15_0" &&
      message.getTimestamp() == 1598271244 && message.getPort() == 43 &&
      message.getMemoryAddress() == "HEHEHE" &&
      message.getMessageType() == MessageType::REPLY) {
    std::cout << "is_deserializedProperly: POSITIVE" << std::endl;
  } else {
    std::cout << "is_deserializedProperly: NEGATIVE" << std::endl;
  }
}