/*
 @written by Li,Yangang @2019.4
*/
#include"april_uuid.h"
#ifdef WIN32
#else
#include<uuid/uuid.h>
#endif
AprilUUID::AprilUUID()
{

#ifdef WIN32

#else

   uuid_t uu;  
    int i;  
    uuid_generate( uu );  
    char buf[64] = {0};
    sprintf(buf, "%02x%02x%02x%02x-%02x%02x-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X", uu[0],
    uu[1],uu[2],uu[3],uu[4],uu[5],uu[6],uu[7],uu[8],uu[9],uu[10],uu[11],uu[12],uu[13],uu[14],
    uu[15]);
    _uuid = buf;
#endif
    

}
AprilUUID::~AprilUUID()
{

}
std::string AprilUUID::UUID2String()
{
    return _uuid;
}