#include <iostream>
#include "./ricart-agrawala/ricart-agrawala.h"
#include <chrono>
#include <ctime>


void canEnterCriticalSectionTest_positive();
void canEnterCriticalSectionTest_negative();
void exitCriticalSectionTest_positive();
void replyToOtherRequestsFirst_positive();

int main() {
    canEnterCriticalSectionTest_positive();
    canEnterCriticalSectionTest_negative();
    exitCriticalSectionTest_positive();
    replyToOtherRequestsFirst_positive();
}


void canEnterCriticalSectionTest_positive(){

    RicartAgrawala ricartAgrawala {15};
    ricartAgrawala.addNewPortNumber(41);
    ricartAgrawala.addNewPortNumber(42);
    ricartAgrawala.addNewPortNumber(43);
    ricartAgrawala.sendRequestMessage("HEHEHE");

    
    for (int i = 41;i<=43; i++){
        ricartAgrawala.receiveReplyMessage(Message{"15_0",1598271244, i, "HEHEHE", MessageType::REPLY});
    }

    if(ricartAgrawala.canEnterCriticalSection()){
        std::cout<<"canEnterCriticalSectionTest_positive: POSITIVE"<<std::endl;
    }else{
        std::cout<<"canEnterCriticalSectionTest_positive: NEGATIVE --- cannot enter critical section"<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
}

void canEnterCriticalSectionTest_negative(){
    RicartAgrawala ricartAgrawala {15};
    ricartAgrawala.addNewPortNumber(41);
    ricartAgrawala.addNewPortNumber(42);
    ricartAgrawala.addNewPortNumber(43);
    ricartAgrawala.sendRequestMessage("HEHEHE");

    
    for (int i = 41;i<=42; i++){
        ricartAgrawala.receiveReplyMessage(Message{"15_0",1598271244, i, "HEHEHE", MessageType::REPLY});
    }

    if(ricartAgrawala.canEnterCriticalSection()){
        std::cout<<"canEnterCriticalSectionTest_positive: NEGATIVE --- can enter critical section"<<std::endl;
    }else{
        std::cout<<"canEnterCriticalSectionTest_negative: POSITIVE"<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
}

void exitCriticalSectionTest_positive(){
    RicartAgrawala ricartAgrawala {15};
    ricartAgrawala.addNewPortNumber(41);
    ricartAgrawala.addNewPortNumber(42);
    ricartAgrawala.addNewPortNumber(43);
    ricartAgrawala.sendRequestMessage("HEHEHE");

    
    for (int i = 41;i<=43; i++){
        ricartAgrawala.receiveReplyMessage(Message{"15_0",1598271244, i, "HEHEHE", MessageType::REPLY});
    }

    if(ricartAgrawala.canEnterCriticalSection()){
        ricartAgrawala.exitCriticalSection();
        if(ricartAgrawala.requestQueueSize()==0){
            std::cout<<"canEnterCriticalSectionTest_positive: POSITIVE"<<std::endl;
        }else{
        std::cout<<"exitCriticalSectionTest_positive: NEGATIVE --- requestQueueSize>0"<<std::endl;
        }
    }else{
        std::cout<<"exitCriticalSectionTest_positive: NEGATIVE --- cannot enter critical section"<<std::endl;
    }
    std::cout<<std::endl<<std::endl<<std::endl<<std::endl;

}


/*
Test description: ->
odbior
wyslanie
wyslanie
wyslanie
wyslanie
odbior
odbior
odbior
*/
void replyToOtherRequestsFirst_positive(){
    RicartAgrawala ricartAgrawala {15};
    ricartAgrawala.addNewPortNumber(41);
    ricartAgrawala.addNewPortNumber(42);
    ricartAgrawala.addNewPortNumber(43);
    ricartAgrawala.receiveRequestMessage(Message{"17_0",(long)69,43,"HEHEHE",MessageType::REQUEST});
    ricartAgrawala.sendRequestMessage("HEHEHE");


    
    for (int i = 41;i<=42; i++){
        ricartAgrawala.receiveReplyMessage(Message{"15_0",1598271244, i, "HEHEHE", MessageType::REPLY});
    }

    if(ricartAgrawala.canEnterCriticalSection()){
        ricartAgrawala.exitCriticalSection();
        if(ricartAgrawala.requestQueueSize()==0){
            std::cout<<"replyToOtherRequests_positive: NEGATIVE --- requestQueueSize should be 1"<<std::endl;
        }else{
        std::cout<<"replyToOtherRequests_positive: NEGATIVE --- requestQueueSize>0"<<std::endl;
        }
    }else{
        ricartAgrawala.receiveReplyMessage(Message{"15_0",1598271244, 43, "HEHEHE", MessageType::REPLY});
        if(ricartAgrawala.canEnterCriticalSection()){
            ricartAgrawala.exitCriticalSection();
            if(ricartAgrawala.requestQueueSize()==0){
                std::cout<<"replyToOtherRequests_positive: POSITIVE"<<std::endl;
            }else{
                std::cout<<"replyToOtherRequests_positive: NEGATIVE --- requestQueueSize>0"<<std::endl;
            }
        }else{
        std::cout<<"replyToOtherRequests_positive: NEGATIVE --- cannot enter critical section"<<std::endl;
        }
    }
}