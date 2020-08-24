#include "utils.h"

long Utils::getCurrentTimestamp() {
    return std::chrono::milliseconds(std::time(NULL)).count();
}

template <>
void Utils::displayVector(std::vector<int> vector)
{
    for( int i=0;i<vector.size();i++){
        std::cout<<"i["+std::to_string(i)+"]: "<<vector.at(i)<<std::endl;
    }
}

template <>
void Utils::displayVector(std::vector<std::pair<long,Message>> vector)
{
    for( int i=0;i<vector.size();i++){
        std::cout<<"i["+std::to_string(i)+"]:"<<std::endl;
        std::cout<<"{"<<std::endl<<vector.at(i).second<<std::endl<<"}"<<std::endl;
    }
}

std::string Utils::createRequestId(int port, int requestId){
    
    std::string s_port = std::to_string(port);
    std::string s_requestId = std::to_string(requestId);

    return std::string(s_port + "_" + s_requestId);
    
}

void Utils::outputMessageInformation(Message message, int _port){
    switch(message.getMessageType()){
        case MessageType::REQUEST:
        {
        std::cout<<"-----------"<<std::endl;
        if(message.getPort()!=_port){
        std::cout<<"Wysylam [REQUEST] do: "<<_port<<std::endl;
        std::cout<<"Wiadomosc: {"<<std::endl<<message<<"}"<<std::endl;
        }else{
           std::cout<<"Odbieram [REQUEST] od: "<<message.getPort()<<std::endl;
        std::cout<<"Wiadomosc: {"<<std::endl<<message<<"}"<<std::endl; 
        }
        std::cout<<"-----------"<<std::endl;
        break;
        }
        case MessageType::REPLY:
        {
        std::cout<<"-----------"<<std::endl;
        if(message.getPort()==_port){
        std::cout<<"Wysylam [REPLY] do: "<<_port<<std::endl;
        std::cout<<"Wiadomosc: {"<<std::endl<<message<<"}"<<std::endl;
        }else{
           std::cout<<"Odbieram [REPLY] od: "<<message.getPort()<<std::endl;
        std::cout<<"Wiadomosc: {"<<std::endl<<message<<"}"<<std::endl; 
        }
        std::cout<<"-----------"<<std::endl;
        break;
        }
    }
}