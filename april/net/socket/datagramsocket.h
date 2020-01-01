/*
 @written by Li,Yangang @2019.4
*/
#ifndef DATAGRAMSOCKET_H
#define DATAGRAMSOCKET_H
#include"socket.h"
#include<string>

namespace April{
namespace net{

    class DatagramSocket:public Socket{
    public:
        DatagramSocket();
        ~DatagramSocket();
    public:
        void joinMulticastGroup(std::string strGroupIP, 
                                std::string strIf="",
                                int ttl = 8, 
                                bool loopback = false);
        int recvFrom(char* buf, int len, NetAddr& addr); 
        int sendTo(char* buf, int len, NetAddr& addr);
    };

}//namespace net
}//namespace April

#endif //DATAGRAMSOCKET_H