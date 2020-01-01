/*
 @written by Li,Yangang @2019.6
*/
#include "MyTask.h"
#include<iostream>

MyTask::MyTask(std::string name):_name(name)
{

}
MyTask::~MyTask()
{

}
void MyTask::Run()
{
    std::cout<<_name<<std::endl;
    for (int i = 0; i < 10; i++ )
    {
        std::cout<<i<<std::endl;
    }
}
