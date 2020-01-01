/*
 @write by Li,Yangang @2019.4
 A wrapper class of socket that can support both linux and windows 
*/
#ifndef SOCKET_H
#define SOCKET_H

#include<string>
#include<vector>
#include"netaddress.h"
namespace April{
namespace net{

    class Socket{
    public:
        Socket();
        Socket(const Socket& st);
        virtual ~Socket();
    public:
        bool bind_v4(std::string strip, unsigned short port);
        bool bind_v4(std::string strip, unsigned short port, bool reuseaddr, bool reuseport);
        bool bind_v4(NetAddr& addr);
        bool bind_v4(NetAddr& addr, bool reuseaddr, bool reuseport);
        int  listen(int backlog);
		void SetRecvTimeOut(int timeOut);
        int getSocknum() {return _sockfd;}
        // void setNoSigpipe();
        typedef  std::vector<Socket> SocketList;
        static int select(SocketList& readlist,   SocketList& readReadyList, 
                     SocketList& writelist,  SocketList& writeReadyList,
                     SocketList& exceptlist, SocketList& exceptReadyList,
                     int timeout);
    private:
        void  setReuseAddr(int sock, bool reuseaddr);
        void  setReusePort(int sock, bool reuseport);
    protected:
        int _sockfd;
    };

}//namespace net
}//namespace lyg

#endif //DATAGRAMSOCKET_H