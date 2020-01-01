/*
 @written by Li,Yangang @2019.6
*/

#include "threadPool.h"

using namespace April::process;

ThreadPool::ThreadPool(int size) : _stop(false)
{
    for (int i = 0; i < size; i++)
    {
        _workerList.emplace_back(
            [this] {
                while (true)
                {
                    //std::function<void()> task

                    std::unique_lock<std::mutex> lock(this->_mutex);
                    this->_condition.wait(lock,
                                          [this] { return (this->_stop || !this->_taskQueue.empty()); });

                    if (this->_stop && this->_taskQueue.empty())
                        break;

                    std::shared_ptr<ITask> task = this->_taskQueue.front();
                    this->_taskQueue.pop();
                    if (task.get())
                    {
                        task->Run();
                    }
                }
            });
    }
}
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _stop = true;
    }

    _condition.notify_all();

    for (std::thread &worker : _workerList)
        worker.join();
}

void ThreadPool::enqueue(std::shared_ptr<ITask> task)
{
    std::unique_lock<std::mutex> lock(_mutex);
    if (_stop)
        return;

    _taskQueue.push(task);
    _condition.notify_one();
}
