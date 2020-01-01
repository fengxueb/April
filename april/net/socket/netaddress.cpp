/*
 @written by Li,Yangang @2019.4
*/
#include"netaddress.h"

using namespace April::net;

NetAddr::NetAddr(std::string strIP, unsigned short port):_strIP(strIP), _port(port)
{

}
NetAddr::NetAddr():_strIP(""), _port(0)
{
    
}
NetAddr::~NetAddr()
{

}
std::string NetAddr::IP()
{
    return _strIP;
}
unsigned short NetAddr::Port()
{
    return _port;
}
void NetAddr::SetIP(std::string IP)
{
    _strIP = IP;
}
void NetAddr::SetAddrPort(unsigned short port)
{
    _port = port;
}