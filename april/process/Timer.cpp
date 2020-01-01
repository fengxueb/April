/*
 @written by Li,Yangang @2019.6
*/

#include"Timer.h"
#include<thread>

using namespace April::process;


void Timer::Sleep(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}



