/*
 @written by Li,Yangang @2019.5
*/
#ifndef WIN32
#include "domainsocket.h"
#include<string.h>
#include "commsock.h"
using namespace April::net;

DomainSocket::DomainSocket(std::string strPath):_fdPath(strPath)
{
    _sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(strPath.c_str());
    
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, strPath.c_str(), strPath.length());
    int ret = ::bind(_sockfd, (struct sockaddr*)&addr, sizeof(addr));
}
DomainSocket::~DomainSocket()
{
    unlink(_fdPath.c_str());
}
DomainSocket::DomainSocket(const DomainSocket& ds):Socket(ds)
{
    _fdPath = ds._fdPath;
}
int DomainSocket::connectTo(std::string strServerPath)
{
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, strServerPath.c_str(), strServerPath.length());
    return  ::connect(_sockfd, (struct sockaddr*)&addr, sizeof(addr));
}
bool DomainSocket::operator==(const DomainSocket& ds) const
{
    if ( _sockfd == ds._sockfd )
        return true;
    return false;
}
#endif