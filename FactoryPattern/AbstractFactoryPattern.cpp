/******************************************************************************
Abstract Factory pattern:-

Abstract Product types: Button, msgPrompt
Concrete Product types: winButton, winMsgPrompt and linuxButton, linuxMsgPrompt for windows and linux

abstract GuiFactory: abstractGUIFactory
Concrete GuiFactory: winGUIFactory and linuxGUIFactory for windows and linux which create families
of products i.e. button and msgPrompt for Windows and Linux.

*******************************************************************************/
#include <iostream>
using namespace std;

class abstractButton {
   public:
    virtual void doSomething() = 0;
};
class linuxButton : public abstractButton {
   public:
    void doSomething() { cout << "\n OK button on Linux"; }
};
class winButton : public abstractButton {
   public:
    void doSomething() { cout << "\n OK button on Windows"; }
};

class abstractMsgPrompt {
   public:
    virtual void doSomethingElse() = 0;
};
class linuxMsgPrompt : public abstractMsgPrompt {
   public:
    void doSomethingElse() { cout << "\nShowing message on Linux"; }
};
class winMsgPrompt : public abstractMsgPrompt {
   public:
    void doSomethingElse() { cout << "\nShowing message on Windows"; }
};

class abstractGUIFactory {
   public:
    virtual abstractButton* createButton() = 0;
    virtual abstractMsgPrompt* createMsgPrompt() = 0;
};
class linuxGUIFactory : public abstractGUIFactory {
   public:
    abstractButton* createButton() { return new linuxButton; }
    abstractMsgPrompt* createMsgPrompt() { return new linuxMsgPrompt; }
};
class winGUIFactory : public abstractGUIFactory {
   public:
    abstractButton* createButton() { return new winButton; }
    abstractMsgPrompt* createMsgPrompt() { return new winMsgPrompt; }
};

int main() {
    cout << "Client starts on Windows";
    abstractGUIFactory* abstractFactory = new winGUIFactory; //setting the type of factory, Windows or Linux

    abstractButton* button = abstractFactory->createButton();//now button and msgPrompt will be of same type only.
    abstractMsgPrompt* msgPrompt = abstractFactory->createMsgPrompt();k

    button->doSomething();
    msgPrompt->doSomethingElse();

    return 0;
}
