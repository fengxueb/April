/*
 @written by Li,Yangang @2019.6
*/
#include"MyThread.h"
#include<iostream>
std::mutex MyThread::_mutex;
MyThread::MyThread(std::string name, Count* count):_name(name),_Count(count){

}

void MyThread::Run()
{
    std::cout<<"MyThread::Run()"<<_name<<std::endl;
    for ( int i = 0;  i < 500; i++)
    {
        std::cout<< i <<std::endl;
        if (_Count)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _Count->Add();
        }
    }
}
