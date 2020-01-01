/*s
 @written by Li,Yangang @2019.5
*/
#ifndef DOMAINSOCKET_H
#define DOMAINSOCKET_H

#ifndef WIN32
#include"socket.h"
#include<string>
namespace April{
namespace net{
    class DomainSocket:public Socket
    {
    public:
        //path should be absolute path.
        DomainSocket(std::string strPath);
        DomainSocket(const DomainSocket& ds);
        ~DomainSocket();
    public:
        int connectTo(std::string strServerPath);
        bool operator==(const DomainSocket& ds) const;
        //DomainSocket accept();
    private:
        std::string _fdPath;
    };
}//net
}//April
#endif //WIN32

#endif //DOMAINSOCKET_H