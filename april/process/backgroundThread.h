/*
 @written by Li,Yangang @2019.6
*/
#ifndef APRIL_BACKGROUNDTHREAD_H
#define APRIL_BACKGROUNDTHREAD_H
#include"Itask.h"
#include<memory>
#include<thread>
namespace April{
namespace process{ 

   class BackgroundThread:public ITask{
   public:    
       BackgroundThread();
       virtual ~BackgroundThread();
       void Start();
       void Join();
       void Detach();
    private:
        std::thread* _thr;
   };
}
}

#endif//APRIL_BACKGROUNDTHREAD_H