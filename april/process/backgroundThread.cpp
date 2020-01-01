/*
 @written by Li,Yangang @2019.6
*/

#include"backgroundThread.h"
using namespace April::process;
BackgroundThread::BackgroundThread()
{

}
BackgroundThread::~BackgroundThread()
{
    Join();
    if ( _thr )
    {
        delete _thr;
    }
}
void BackgroundThread::Join()
{
    //std::thread* pthread = _thr.get();
    if ( _thr != nullptr )
    {
        if ( _thr->joinable() )
            _thr->join();
    }
}
void BackgroundThread::Detach()
{
   // std::thread* pthread = _thr.get();
    if (_thr != nullptr)
    {
        if ( _thr->joinable() )
            _thr->detach();
    }
}
void BackgroundThread::Start()
{ 
    _thr = new std::thread(std::bind(&BackgroundThread::Run, this));       
}
