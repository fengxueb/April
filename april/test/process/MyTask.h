/*
 @written by Li,Yangang @2019.6
*/
#ifndef MYTASK_H
#define MYTASK_H
#include "Itask.h"
#include<string>
using namespace April::process;

class MyTask:public ITask
{
public:
    MyTask(std::string name);
    ~MyTask();
   void Run();
private:
   std::string _name;
};
#endif