/*
 @write by Li,Yangang @2019.4
 A wrapper class of socket that can support both linux and windows 
*/
#include "socket.h"
#include "commsock.h"

using namespace April::net;

Socket::Socket() : _sockfd(0)
{
}
Socket::Socket(const Socket &st)
{
    _sockfd = st._sockfd;
}
Socket::~Socket()
{
    if (_sockfd > 0)
    {
        closesocket(_sockfd);
    }
}
bool Socket::bind_v4(std::string strip, unsigned short port)
{
    int sd = getSocknum();
    if (sd > 0)
    {
        struct sockaddr_in addr = {0};
        addr.sin_family = AF_INET;
        if (strip == "")
        {
            addr.sin_addr.s_addr = INADDR_ANY;
        }
        else
        {
            addr.sin_addr.s_addr = ::inet_addr(strip.c_str());
        }

        addr.sin_port = htons(port);
        int ret = ::bind(sd, (struct sockaddr *)&addr, sizeof(addr));
        if (ret != -1)
        {
            return true;
        }
    }
    return false;
}
bool Socket::bind_v4(std::string strip, unsigned short port, bool reuseaddr, bool reuseport)
{
    int sd = getSocknum();
    setReuseAddr(sd, reuseaddr);
    setReusePort(sd, reuseport);
    return bind_v4(strip, port);
}

bool Socket::bind_v4(NetAddr &addr)
{
    return bind_v4(addr.IP(), addr.Port());
}
bool Socket::bind_v4(NetAddr &addr, bool reuseaddr, bool reuseport)
{
    return bind_v4(addr.IP(), addr.Port(), reuseaddr, reuseport);
}
int Socket::listen(int backlog)
{
    return ::listen(_sockfd, backlog);
}
void Socket::SetRecvTimeOut(int timeout)
{
	setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
}
void Socket::setReuseAddr(int sock, bool reuseaddr)
{
    int on = 0;
    if (reuseaddr)
    {
        on = 1;
    }

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on));
}

void Socket::setReusePort(int sock, bool reuseport)
{

#ifdef SO_REUSEPORT
    int on = 0;
    if (reuseport)
    {
        on = 1;
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, (const char *)&on, sizeof(on));
#endif
}
int Socket::select(SocketList &readList, SocketList &readReadyList,
                   SocketList &writeList, SocketList &writeReadyList,
                   SocketList &exceptList, SocketList &exceptReadyList,
                   int timeout)
{
    fd_set fdRead;
    fd_set fdWrite;
    fd_set fdExcept;

    int fd = 0;
    FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExcept);

    for (SocketList::iterator it = readList.begin(); it != readList.end(); ++it)
    {
        int sockfd = it->getSocknum();
        if (sockfd != -1)
        {
            if (fd < sockfd)
                fd = sockfd;
            FD_SET(sockfd, &fdRead);
        }
    }

    for (SocketList::iterator it = writeList.begin(); it != writeList.end(); ++it)
    {
        int sockfd = it->getSocknum();
        if (sockfd != -1)
        {
            if (fd < sockfd)
                fd = sockfd;
            FD_SET(sockfd, &fdWrite);
        }
    }

    for (SocketList::iterator it = exceptList.begin(); it != exceptList.end(); ++it)
    {
        int sockfd = it->getSocknum();
        if (sockfd != -1)
        {
            if (fd < sockfd)
                fd = sockfd;
            FD_SET(sockfd, &fdExcept);
        }
    }

    if (fd == 0)
        return 0;

    struct timeval tv;
    tv.tv_sec = (long)timeout / 1000;
    tv.tv_usec = (long)timeout % 1000;
    int selret = ::select(fd, &fdRead, &fdWrite, &fdExcept, &tv);

    if (selret < 0)
        return selret;

    for (SocketList::iterator it = readList.begin(); it != readList.end(); ++it)
    {
        int sockfd = it->getSocknum();
        if (sockfd != -1 && FD_ISSET(sockfd, &fdRead))
        {
            readReadyList.push_back(*it);
        }
    }

    for (SocketList::iterator it = writeList.begin(); it != writeList.end(); ++it)
    {
        int sockfd = it->getSocknum();
        if (sockfd != -1 && FD_ISSET(sockfd, &fdWrite))
        {
            writeReadyList.push_back(*it);
        }
    }

    for (SocketList::iterator it = exceptList.begin(); it != exceptList.end(); ++it)
    {
        int sockfd = it->getSocknum();
        if (sockfd != -1 && FD_ISSET(sockfd, &fdExcept))
        {
            exceptReadyList.push_back(*it);
        }
    }

    return selret;
}
