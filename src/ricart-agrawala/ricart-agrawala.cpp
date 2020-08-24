#include "ricart-agrawala.h"

void RicartAgrawala::sendMessage(Message message, int _port){
    // TODO: Implement send message in ZMQ
    // Utils::outputMessageInformation(message,_port);
}


void RicartAgrawala::sendReplyMessages(){
    for (int i=0; i<requestQueue.size(); i++){
        if(requestQueue[i].second.getPort()!=port){
            Message message = requestQueue[i].second;
            Message replyMessage = Message{message,port};
            sendMessage(replyMessage, message.getPort());
            removeFirstElementFromRequestQueue();
        }
        else{
            break;
        }
    }
}

void RicartAgrawala::sendReplyMessage(Message message) {
        Message replyMessage = Message {message,message.getPort()};
        sendMessage(replyMessage,replyMessage.getPort());
}

std::string RicartAgrawala::getFirstRequestIDInRequestQueue(){
    return requestQueue.at(0).second.getRequestId();
}

bool RicartAgrawala::checkIfReceivedAllReplies(){
    return replyReceived[getFirstRequestIDInRequestQueue()].size()==portNumbers.size();
}

void RicartAgrawala::removeFirstElementFromRequestQueue(){
    requestQueue.erase(requestQueue.begin());
}

void RicartAgrawala::sortRequestQueue() {
    std::sort(requestQueue.begin(), requestQueue.end(), [](const std::pair<long,Message>& x, std::pair<long,Message>& y){
        return x.first < y.first;
    });
}

RicartAgrawala::RicartAgrawala(int port) : port{port} {
    requestId = 0;
}

void RicartAgrawala::sendRequestMessage(std::string filename){
    long timestamp = Utils::getCurrentTimestamp();
    std::string s_requestId = Utils::createRequestId(port, requestId);
    Message message {s_requestId, timestamp, port, filename, MessageType::REQUEST};
    addToRequestQueue(message);
    for (int i=0; i<portNumbers.size();i++){
        sendMessage(message,portNumbers[i]);
    }
    requestId++;
}

void RicartAgrawala::receiveRequestMessage(Message message) {
    // Utils::outputMessageInformation(message,message.getPort());
    if(requestQueue.size()==0){
        sendReplyMessage(message);
    }else{
    addToRequestQueue(message);
    }
}

void RicartAgrawala::receiveReplyMessage(Message message) {
    // Utils::outputMessageInformation(message,port);
    std::vector<int> replies;
    if(replyReceived.count(message.getRequestId())){
        replies = replyReceived[message.getRequestId()];
        replies.push_back(message.getPort());
        replyReceived[message.getRequestId()]=replies;
    }else{
        replies.push_back(message.getPort());
        replyReceived[message.getRequestId()] = replies;   
    }
}

bool RicartAgrawala::canEnterCriticalSection() {
    if(requestQueue.size()>0){
        if(checkIfReceivedAllReplies()){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

void RicartAgrawala::exitCriticalSection(){
    removeFirstElementFromRequestQueue();
    sendReplyMessages();
}

void RicartAgrawala::addNewPortNumber(int port){
    portNumbers.push_back(port);
}

void RicartAgrawala::removePortNumber(int port){
    int index;
    if(index = std::find(portNumbers.begin(),portNumbers.end(), port) != portNumbers.end()){
        portNumbers.erase(portNumbers.begin()+index);
    }
}

void RicartAgrawala::displayPortNumbers(){
    Utils::displayVector(portNumbers);
}

void RicartAgrawala::addToRequestQueue(Message message){
    requestQueue.push_back(std::pair<long,Message> {message.getTimestamp(), message});
    sortRequestQueue();
    sendReplyMessages();
}

int RicartAgrawala::requestQueueSize(){
    return requestQueue.size();
}