/******************************************************************************
Singleton basic
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
    
    
    Singleton* inst1,*inst2;
    
    inst1 = Singleton::getInstance();
    inst1->setData(10);
    inst2 = inst1;//copy constructor allowed
    cout<<inst2->getData();

    return 0;
}