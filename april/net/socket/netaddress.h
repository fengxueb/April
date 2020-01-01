/*
 @written by Li,Yangang @2019.4
*/
#ifndef NETADDRESS_H
#define NETADDRESS_H
#include<string>
namespace April{
namespace net{

class NetAddr{
public:
      NetAddr(std::string strIP, unsigned short port);
      NetAddr();
      ~NetAddr();
      void SetIP(std::string ip);;
      void SetAddrPort(unsigned short port);
      std::string IP();
      unsigned short  Port();
private:
      std::string _strIP;
      unsigned short  _port;
};

}}
#endif//NETADDRESS_H