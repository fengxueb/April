/*
 @written by Li,Yangang @2019.6
*/
#ifndef APRIL_TIMER_H
#define APRIL_TIMER_H
#include <chrono>
namespace April{
namespace process{

    class Timer{
    public:
        static void Sleep(int milliseconds);
    };
}
}

#endif
