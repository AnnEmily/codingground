#include <iostream>

using namespace std;

class A
{
public:
    virtual ~A () 
    {
        cout << "Deleting A" << endl ;
    } ;
    virtual void objectIs ()
    {
        cout << "Object is A" << endl ;
    } ;
} ;

class B : public A
{
public:
    ~B () 
    {
       cout << "Deleting B" << endl ;
    } ;
    void objectIs ()
    {
        cout << "Object is B" << endl ;
    } ;
};

int main()
{
   //B *myB = new B () ;
   
   A *myA = new B () ;
   
   myA->objectIs() ;
   myA->A::objectIs() ;
   
   delete myA ;
   
   return 0;
}
