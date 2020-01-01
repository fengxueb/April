/*
 @written by Li,Yangang @2019.6
*/
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include"backgroundThread.h"
#include<string>
#include<mutex>
#include"Count.h"
using namespace April::process;
class MyThread:public BackgroundThread
{
public:
    MyThread(std::string name, Count* count);
    ~MyThread(){}
    void Run();
private:
   std::string _name;
   Count* _Count;
   static std::mutex _mutex;
};


#endif