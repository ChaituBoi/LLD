/******************************************************************************
README
Asteroid spaceship game using Factory pattern.
IgameObject is object Interface, asteroid and powerup are concrete implementations.
IobjCreator is creator/factory interface, asteroidCreator and powerupCreator are concrete implementations.

Game difficulty is controlled by a modifier(biz logic) which increases with time. The asteroids created will increase in size and speed overtime. While Powerups will decrease in both overtime.
*******************************************************************************/
#include <iostream>
using namespace std;

class IgameObject {
   public:
    int size = 100;
    int velocityX = 90;
    int velocityY = 70;

    virtual void objectAction() = 0;
    virtual void objectMovement() = 0;
};  // product Interface
class asteroid : public IgameObject {
   private:
   public:
    asteroid(int modifier) {
        this->size *= modifier;
        this->velocityX *= modifier;
        this->velocityY *= modifier;
    }
    void objectAction() {
        cout << "\nAsteroid of size " << size
             << " is spawned endangering your spaceship.";
    }

    void objectMovement() {
        cout << "\nAsteroid moves at speed (" << velocityX << "," << velocityY
             << ") m/s.";
    }

};  // product1
class powerup : public IgameObject {
   private:
   public:
    powerup(int modifier) {
        this->size *= (100 - modifier);
        this->velocityX *= (100 - modifier);
        this->velocityY *= (100 - modifier);
    }
    void objectAction() {
        cout << "\nPowerup of size " << size
             << " is spawned. Take it before it expires.";
    }

    void objectMovement() {
        cout << "\nPowerup moves at speed (" << velocityX << "," << velocityY
             << ") m/s.";
    }

};  // product2

class IobjCreator {
   public:
    int diffModifier = 100;
    virtual IgameObject* createObj() = 0;
    void setModifier(int mod) { diffModifier = mod; }
};
class asteroidCreator : public IobjCreator {
   public:
    asteroidCreator(int diffModifier) { this->diffModifier = diffModifier; }
    IgameObject* createObj() {
        asteroid* ast = new asteroid(diffModifier);
        return ast;
    }
};
class powerupCreator : public IobjCreator {
   public:
    powerupCreator(int diffModifier) {
        this->diffModifier = 100 - diffModifier;
    }
    IgameObject* createObj() {
        powerup* pwr = new powerup(diffModifier);
        return pwr;
    }
};

int main() {
    //
    cout << "\nGame starts with difficult easy:-";
    int modifier = 20;
    IobjCreator* creator;
    IgameObject* gameObj;
    asteroidCreator* astCreator = new asteroidCreator(modifier);
    powerupCreator* pwrCreator = new powerupCreator(modifier);

    while (modifier < 101) {
        creator = astCreator;
        creator->setModifier(modifier);
        gameObj = creator->createObj();
        gameObj->objectAction();
        gameObj->objectMovement();

        creator = pwrCreator;
        gameObj = creator->createObj();
        gameObj->objectAction();
        gameObj->objectMovement();

        modifier += 20;
    }

    return 0;
}
