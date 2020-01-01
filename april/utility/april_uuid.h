/*
 @written by Li,Yangang @2019.4
*/
#ifndef APRILUUID_H
#define APRILUUID_H
#include<string>
class AprilUUID
{
public:
    AprilUUID();
    ~AprilUUID();
public:
    std::string UUID2String();
private:
    std::string _uuid;
};
#endif//UUID_H