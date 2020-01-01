/*
 @written by Li,Yangang @2019.6
*/

#ifndef COUNT_H
#define COUNT_H
#include<iostream>
class Count{
public:
   Count():_count(0){

   }
   ~Count(){

   }
   void Add(){
       _count++;
       std::cout<<"Add"<<_count<<std::endl;
   }
private:
   int _count;
};

#endif//COUNT_H