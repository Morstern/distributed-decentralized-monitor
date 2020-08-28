#ifndef TEST_MESSAGE_H
#define TEST_MESSAGE_H

#include "../message/message.h"
#include <chrono>
#include <ctime>
#include <iostream>

void runMessageTests();
void is_serializedProperly();
void is_deserializedProperly();

#endif