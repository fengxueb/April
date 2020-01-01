/*
 @written by Li,Yangang @2019.6
*/
#include"domainSocketServer.h"
#include "domainSocket.h"
#include"../../socket/socket.h"
using namespace April::net;
DomainSocketServer::DomainSocketServer(std::string strPath, IDomainMsgHandler& handler)
:_path(strPath),_handler(handler),_exit(false) 
{

}
bool DomainSocketServer::Start()
{
    DomainSocket ds(_path);
    const int backlog = 5;
    ds.listen(backlog);
    
    SOCKETLIST readList;
    SOCKETLIST readReadyList;
    SOCKETLIST writeList;
    SOCKETLIST writeReadyList;
    SOCKETLIST exceptList;
    SOCKETLIST exceptReadyList;

    readList.push_back(ds);

    while(_exist != true)
    {
        Socket::select(readList, readReadyList,
                       writeList, writeReadyList, 
                       exceptList, exceptReadyList, 
                       2000);

        if(readReadyList.size() > 0)
        {
            SOCKETLIST::iterator it = readReadyList.begin();
            while (it !=  readReadyList.end())
            {
                 if (ds == *it)
                 {
                     //new connection comming
                 }
            }


        }
                

    }
    

}