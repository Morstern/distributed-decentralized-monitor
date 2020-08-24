#ifndef RICART_AGRAWALA_H
#define RICART_AGRAWALA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <zmq.h>
#include <algorithm>
#include <set>
#include "../message/message.h"
#include "../utils/utils.h"

class RicartAgrawala {
    private:
    std::vector<int> portNumbers;
    std::vector<std::pair<long, Message>> requestQueue;
    std::map<std::string, std::vector<int>> replyReceived;
    
    int port;
    int requestId;
  
    void sendMessage(Message message, int port);
    void sendReplyMessages();
    void sendReplyMessage(Message message);
    std::string getFirstRequestIDInRequestQueue();
    bool checkIfReceivedAllReplies();
    void removeFirstElementFromRequestQueue();
    void sortRequestQueue();
    
    public:
     RicartAgrawala(int port);
     void sendRequestMessage(std::string filename);
     void addToRequestQueue(Message message);
     void receiveRequestMessage(Message message);
     void receiveReplyMessage(Message message);
     bool canEnterCriticalSection();
     void exitCriticalSection();
     void addNewPortNumber(int port);
     void removePortNumber(int port);
     void displayPortNumbers();
     int requestQueueSize();


};
#endif