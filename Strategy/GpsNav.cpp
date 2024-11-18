#include <iostream>
using namespace std;

class routeBuildStrategy
{
    public:
    
    virtual void buildRoute()=0;

};

class byCar: public routeBuildStrategy
{
    public:
    void buildRoute()
    {
        cout<<"Showing route for Car.";
    }
};
class byWalk: public routeBuildStrategy
{
    public:
    void buildRoute()
    {
        cout<<"Showing route for pedestrians.";
    }
};
class byBus: public routeBuildStrategy
{
    public:
    void buildRoute()
    {
        cout<<"Showing route for Bus.";
    }
};
class GpsNav
{
    private:
    routeBuildStrategy* obj;
    public:
    void setStrategy(routeBuildStrategy* obj)
    {
        this->obj = obj;
    }

    void buildRoute()
    {
        obj->buildRoute();
    }
    
};

int main()
{
    
    //
    GpsNav objGps;
    objGps.setStrategy(new byCar);

    objGps.buildRoute(); 
    return 0;
}
