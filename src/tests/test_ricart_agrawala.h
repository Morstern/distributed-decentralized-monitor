#ifndef TEST_RICART_AGRAWALA_H
#define TEST_RICART_AGRAWALA_H

#include "../ricart-agrawala/ricart-agrawala.h"
#include <chrono>
#include <ctime>
#include <iostream>

void runRicartAgrawalaTests();
void canEnterCriticalSectionTest_positive();
void canEnterCriticalSectionTest_negative();
void exitCriticalSectionTest_positive();
void removeMessage();
void replyToOtherRequestsFirst_positive();

#endif