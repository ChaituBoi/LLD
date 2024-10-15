/******************************************************************************
Singleton- 
1. Copy constructor disabled.
2. operator = overloading deleted.
*******************************************************************************/
#include <iostream>
using namespace std;

class Singleton{
  
  private:
  
  static Singleton *mySingleInstance;
  
  Singleton()
  {
      //private constructor so class is locked.
  }
  int data;
  
  public:
  
  Singleton(Singleton& other) = delete;//delete copy constructor
  void operator =(Singleton* other) = delete;//delete assignment operation i.e. obj1 = obj2;
  
  static Singleton* getInstance();
  void setData(int x){data=x;}
  int getData(){return data;}
    
};


Singleton* Singleton::mySingleInstance = NULL;
Singleton* Singleton::getInstance()
{
    if(mySingleInstance==NULL)
    {
        mySingleInstance = new Singleton;
        return mySingleInstance;
    }
    return mySingleInstance;
}

int main()
{
    Singleton* inst1;
    
    inst1 = Singleton::getInstance();
    inst1->setData(10);
    
    // Singleton inst2(*inst1); //won't work
    Singleton* inst2(inst1); //will work
    // Singleton inst2 = *inst1; //won't work
    cout<<(inst2==inst1);

    return 0;
}