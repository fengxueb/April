/*
 @written by Li,Yangang @2019.6
*/
#include"Count.h"
#include"MyThread.h"
#include"threadPool.h"
#include"Timer.h"
#include"MyTask.h"

using namespace April::process;

void testThread()
{
   
    Count count;

    MyThread mt1("t1", &count);    
    mt1.Start();

    MyThread mt2("t2", &count);
    mt2.Start();

    mt1.Join();
    mt2.Join();

    std::cout<<"testThread finished"<<std::endl;
}



class  TestThreadPool:public BackgroundThread
{
public:
    TestThreadPool(ThreadPool* pool_):_stop(false), _index(0), _pool(pool_){

    }
public:
    void Stop(){_stop = true;}
    void Run(){
        while(!_stop)
        {
            _index++;
            char buf[10]={0};
            sprintf(buf, "Task:%d", _index);
            std::string name = buf;
            std::shared_ptr<ITask> task(new MyTask(name));
            _pool->enqueue(task);
            Timer::Sleep(20); 
        }
    }
private:
    ThreadPool* _pool;
    bool _stop;
    int _index;
};
    
void testThreadPool()
{
    ThreadPool *pool = new ThreadPool(4);
    TestThreadPool testpool(pool);
    testpool.Run();

    while(1)
    {
        Timer::Sleep(200);
    }

}

int main()
{
   // testThread();
    testThreadPool();
    return 0;
}