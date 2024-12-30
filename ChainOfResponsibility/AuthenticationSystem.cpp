/**********
1. This code takes in a request for authentication of class person.
2. AgeVerification & authLvlVerification handlers check for age and auth level one after another.
3. One check failing leads to instant stop. Further handlers will not be called.
**********/
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

class person
{
    public:
        int age;
        int authLevel;
        person(): age(0),authLevel(0)
        {}
        person(int x,int y):age(x),authLevel(y)
        {}
};
enum{NORMIE=0,ADV,PRO,EXP};

class securityHandler
{
    public:
        virtual void setNext(std::shared_ptr<securityHandler> ptr) = 0;
        virtual void processRequest(std::shared_ptr<person> cred)=0;
        virtual ~securityHandler()//virtual destructors need their definition albeit empty. Pure virtual dest need defn outside class
        {
            std::cout << "security Handler dest called" <<std::endl;
        }
        
};
class ageVerification : public securityHandler
{
    private:
    std::shared_ptr<securityHandler> nextHandler = NULL;
    public:
    void setNext(std::shared_ptr<securityHandler> ptr)
    {
        nextHandler = ptr;
    }
    void processRequest(std::shared_ptr<person> cred)
    {
        if(cred->age<18)
        {
            std::cout << "Underage. Access rejected." <<std::endl;
            return;
        }
        else if(nextHandler != NULL)
        {
            nextHandler->processRequest(cred);
        }

    }

    ~ageVerification()
    {
        std::cout << "age dest called" << std::endl;
    }

};
class authLvlVerification : public securityHandler
{
    private:
    std::shared_ptr<securityHandler> nextHandler = NULL;
    public:
    void setNext(std::shared_ptr<securityHandler> ptr)
    {
        nextHandler = ptr;
    }
    void processRequest(std::shared_ptr<person> cred)
    {
        if(cred->authLevel<PRO)
        {
            std::cout << "Insufficient authLevel. Access rejected." <<std::endl;
            return;
        }
        else if(nextHandler != NULL)
        {
            nextHandler->processRequest(cred);
        }
    }
    ~authLvlVerification()
    {
        std::cout << "Auth lvl dest called" << std::endl;
    }

};

int main()
{
    
    std::shared_ptr<securityHandler> agePtr = std::make_shared<ageVerification>();
    std::shared_ptr<securityHandler> authPtr = std::make_shared<authLvlVerification>();

    agePtr->setNext(authPtr);

    agePtr->processRequest(std::make_shared<person>(20,EXP)); //everything fine and dandy.

    return 0;
}
