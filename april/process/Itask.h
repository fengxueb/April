/*
 @written by Li,Yangang @2019.6
*/

#ifndef APRIL_ITASK_H
#define APRIL_ITASK_H
namespace April{
namespace process{ 
    
    class ITask{
    public:
        virtual void Run() = 0;
    };

}
}
#endif //APRIL_ITASK_H