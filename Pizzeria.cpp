#include <iostream>
#include <string>
#include <unordered_map>
#define MAX_TOPPINGS 3

std::unordered_map<std::string, int> ToppingToPriceMap;
std::unordered_map<std::string, int> CrustToPriceMap;

void initToppingToPriceMap()
{
    ToppingToPriceMap.insert({"DEFAULT", 0});
    ToppingToPriceMap.insert({"ONION", 30});
    ToppingToPriceMap.insert({"CAPSICUM",30});
    ToppingToPriceMap.insert({"PAPRIKA",20});
    ToppingToPriceMap.insert({"PANEER",50});
    ToppingToPriceMap.insert({"CHICKEN",60});
}
void initCrustToPriceMap()
{
    CrustToPriceMap.insert({"DEFAULT", 0});
    CrustToPriceMap.insert({"THIN_CRUST", 250});
    CrustToPriceMap.insert({"PAN_STYLE_CRUST",200});
    CrustToPriceMap.insert({"CHEESE_BURST",350});
    ToppingToPriceMap.insert({"HAND_TOSSED",200});
}

int min(int a,int b)
{
    return a > b ? b : a;
}
int max(int a,int b)
{
    return a > b ? a : b;
}
class IPizzaBuilder
{
    private:
    public:
        
        virtual void setPizzaBase(std::string baseType)=0;
        virtual void addPizzaToppings(std::string topping) = 0;
        virtual void removePizzaToppings(std::string topping) = 0;
        virtual int calculatePrice()=0;
        //const deconst
        virtual ~IPizzaBuilder(){}
};
//product
class Pizza
{
    public:
    std::string crust;//init with "DEFAULT"
    std::string toppings[MAX_TOPPINGS]; // MAX_TOPPINGS = 3
    int toppingCount;
    int price = 0;

    Pizza(Pizza &pizza) //deep copy for returning pizza from builder (prototype logic)
    {
        this->crust = pizza.crust;
        for(int ind=0;ind<pizza.toppingCount;ind++)
        {
            this->toppings[ind] = pizza.toppings[ind];
        }
        this->toppingCount = pizza.toppingCount;
        this->price = pizza.price;
    }

    Pizza* clone()//prototype logic
    {
        return new Pizza(*this);
    }

    Pizza()
    {
        crust="DEFAULT";
        for (int ind=0;ind<MAX_TOPPINGS;ind++)
        {
            toppings[ind] = "DEFAULT";
        }
        toppingCount = 0;
        price = 0;
    }
    void seePizza() 
    {
        std::cout << "Pizza is having crust: " << crust << " with toppings: ";
        for(int ind=0;ind<toppingCount;ind++)
        {
            std::cout << toppings[ind] << " ";
        }

        std::cout << std::endl << "It costs Rs "<<price<<std::endl;
    }

};
//
class ConcretePizzaBuilder : public IPizzaBuilder
{
    private:
        Pizza pizza;
    public:
        //void setPizza(Pizza *ptr){};
        Pizza* getPizza()
        {
            return pizza.clone(); //prototype logic
        }
        void setPizzaBase(std::string crustType) 
        {
            //need to check validity of topping.
            if(CrustToPriceMap.find(crustType)==CrustToPriceMap.end())
            {
                std::cout << "Action: SETCRUST. Invalid crust type." << std::endl;
                return;
            }
            pizza.crust = crustType;
            pizza.price += CrustToPriceMap[crustType];
        }
        void addPizzaToppings(std::string topping) 
        {
            //need to check validity of topping.
            if(ToppingToPriceMap.find(topping)==ToppingToPriceMap.end())
            {
                std::cout << "Action: ADDTOP. Invalid topping type." << std::endl;
                return;
            }
            //if max topping amount reached
            if(pizza.toppingCount>=MAX_TOPPINGS)
            {
                std::cout << "Action: ADDTOP. Max toppings amount reached. Please remove before adding." << std::endl;
                return;
            }

            pizza.toppings[pizza.toppingCount++] = topping;
            pizza.price += ToppingToPriceMap[topping];
        }
        void removePizzaToppings(std::string topping) 
        {
            //need to check validity of topping.
            if(ToppingToPriceMap.find(topping)==ToppingToPriceMap.end())
            {
                std::cout << "Action: REMTOP. Invalid topping type." << std::endl;
                return;
            }
            int ind = 0;
            for(ind;ind<pizza.toppingCount;ind++)
            {
                if(pizza.toppings[ind] == topping)
                {
                    pizza.price -= ToppingToPriceMap[topping];
                    break;
                }
            }
            if(ind >= pizza.toppingCount)
            {
                std::cout << "Action: REMTOP. Topping not present." << std::endl;
            }
            else
            {
                while(ind+1<pizza.toppingCount)
                {
                    pizza.toppings[ind] = pizza.toppings[ind + 1];
                    ind++;
                }
                pizza.toppingCount = max(0,pizza.toppingCount-1);
            }
        }
        int calculatePrice()
        {
            return pizza.price;
        }
};

int main()
{
    initToppingToPriceMap();
    initCrustToPriceMap();

    ConcretePizzaBuilder builder;
    
    builder.setPizzaBase("THIN_CRUST");
    builder.addPizzaToppings("CAPSICUM");
    builder.addPizzaToppings("ONION");//invalid topping type log
    builder.addPizzaToppings("PANEER");

    builder.addPizzaToppings("PAPRIKA");
    Pizza* pizza = builder.getPizza();
    pizza->seePizza();

    builder.removePizzaToppings("ONION"); //try to make changes in pizza again to see if we really received a deep copy of the pizza.
    pizza->seePizza();

    /*
    Output:

    Action: ADDTOP. Max toppings amount reached. Please remove before adding.
    Pizza is having crust: THIN_CRUST with toppings: CAPSICUM ONION PANEER    
    It costs Rs 360
    Pizza is having crust: THIN_CRUST with toppings: CAPSICUM ONION PANEER    
    It costs Rs 360    //shows that we really received a deep copy of the pizza
    */
    return 0;
}
