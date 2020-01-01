/*
 @written by Li,Yangang @2019.4
*/
#include"datagramsocket.h"
#include"commsock.h"
using namespace April::net;
DatagramSocket::DatagramSocket()
{
    _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
}
DatagramSocket::~DatagramSocket()
{
    
}
void DatagramSocket::joinMulticastGroup(std::string strGroupIP,
                                        std::string strIf,
                                        int ttl,
                                        bool loopback)
{
    struct ip_mreq imr;
	imr.imr_multiaddr.s_addr = ::inet_addr(strGroupIP.c_str());
    if(strIf == "")
    {
        //default using the first network inferce
        imr.imr_interface.s_addr = 0;
    }
    else
    {
        imr.imr_interface.s_addr = ::inet_addr(strIf.c_str());
    }
	setsockopt(_sockfd, IPPROTO_IP,  IP_ADD_MEMBERSHIP, (char*)&imr, sizeof(imr));
    setsockopt(_sockfd, IPPROTO_IP, IP_MULTICAST_TTL,(char*)&ttl,sizeof(int));
    
    int loop = loopback? 1: 0;  

	setsockopt(_sockfd, IPPROTO_IP,IP_MULTICAST_LOOP,(char*)&loop,sizeof(int));  
   
}
int DatagramSocket::recvFrom(char* buf, int len, NetAddr& addr)
{
    struct sockaddr_in clientAddr={0};
    SOCKLEN addrsize = sizeof(clientAddr);
    //std::cout<<"receiving"<<std::endl;
    int ret = ::recvfrom(_sockfd, buf, len, 0, (sockaddr*)&clientAddr, &addrsize);
  
    addr.SetIP(::inet_ntoa(clientAddr.sin_addr));
	
	addr.SetAddrPort(::ntohs(clientAddr.sin_port));
	
   

    return ret;
   
}
int DatagramSocket::sendTo(char* buf, int len, NetAddr& addr)
{

    struct sockaddr_in  sa;
    memset(&sa, 0,  sizeof(sa));
    sa.sin_family  = AF_INET;
    sa.sin_port    = htons(addr.Port());
    sa.sin_addr.s_addr  =  ::inet_addr(addr.IP().c_str());

    return ::sendto(_sockfd, buf, len, 0,  (sockaddr*)&sa, sizeof(sa));
}