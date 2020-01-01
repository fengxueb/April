/*
 @written by Li,Yangang @2019.6
*/
#ifndef APRIL_THREADPOOL_H
#define APRIL_THREADPOOL_H
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include <condition_variable>
#include<memory>
#include"Itask.h"
namespace April{
namespace process{

   class ThreadPool{
   public:
       ThreadPool(int size);
       ~ThreadPool();

       void enqueue(std::shared_ptr<ITask> task);
   private:
       std::vector<std::thread> _workerList;
       std::queue<std::shared_ptr<ITask>> _taskQueue;
       std::mutex  _mutex;
       bool _stop;
       std::condition_variable _condition;
   };    
}    
}

#endif//APRIL_THREADPOOL_H