/*
 @written by Li,Yangang @2019.6
*/
#ifndef DOMAINMSGHANDLER_H
#define DOMAINMSGHANDLER_H
namespace April{
namespace net{
    class IDomainMsgHandler{
    public:
        virtual void execute() = 0; 
    };
}
}
#endif //DOMAINMSGHANDLER_H