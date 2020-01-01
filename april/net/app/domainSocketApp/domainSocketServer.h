/*
 @written by Li,Yangang @2019.6
*/
#ifndef DOMAINSOCKETSERVER_H
#define DOMAINSOCKETSERVER_H
#include<string>
#include"IDomainMsgHandler.h"
#include<memory>

namespace April{
namespace net{

    class DomainSocketServer{
    public:
        explict  DomainSocketServer(std::string strPath, IDomainMsgHandler* handler);
        ~DomainSocketServer();
        bool Start();
        void Stop();
    private:
        std::string  _path;
        std::shared_ptr<IDomainMsgHandler> _handler;
        bool _exit;
    };

}//net
}//April
#endif//DOMAINSOCKETSERVER_H
