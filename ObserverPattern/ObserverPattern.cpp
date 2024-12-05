#include <iostream>
#include "string.h"
using namespace std;
#define MAX_SUBSCRIBERS 100
//IObserver and IObservable are the crux of the program. Rest are customisable.
class IObserver
{
  public:
  virtual void update(const string articleName) = 0;
};
class IObservable
{
  public:
  virtual void subscribe(IObserver* o) = 0;
  virtual void unsubscribe(IObserver* o) = 0;
  virtual void notifySubsribers() = 0;
};

class MobileUser : public IObserver
{
  private:
  string userName="DEFAULT";
  
  public:
  MobileUser(const string userName)
  {
    this->userName = userName;
  }
  void update(const string articleName)
  {
    cout<<"Trending now - \""<<articleName<<"\". Viewed by "<<userName<<" on Mobile.\n";
  }
};

class LaptopUser : public IObserver
{
  private:
  string userName="DEFAULT";
  
  public:
  LaptopUser(const string userName)
  {
    this->userName = userName;
  }
  void update(const string articleName)
  {
    cout<<"Trending now - \""<<articleName<<"\". Viewed by "<<userName<<" on Laptop.\n";
  }
};
class NewsWebsite : public IObservable
{
  private:
  string latestTrendingArticle="DEFAULT";
  IObserver* subList[MAX_SUBSCRIBERS];
  int subCount = 0;
  
  public:
  void subscribe(IObserver* o)
  {
    if(subCount<MAX_SUBSCRIBERS)
    {
      subList[subCount++] = o;
    }
  }
  void unsubscribe(IObserver* o)
  {
    //too lazy to write.
  }
  void notifySubsribers()
  {
    for(int ind=0;ind<subCount;ind++)
    {
      subList[ind]->update(latestTrendingArticle);
    }
  }
  void changeArticle(string articleName)
  {
    latestTrendingArticle = articleName;
    notifySubsribers();
  }
};

int main()
{
  NewsWebsite news;
  MobileUser mUser1("Chaitanya");
  LaptopUser lUser1("Ayush");
  
  news.subscribe(&mUser1);
  news.changeArticle("Sachin Tendulkar calls off retirement. Mixed reactions!!");
  
  news.subscribe(&lUser1);
  news.changeArticle("Karen dials 911 on a white boy selling lemonade. Cops puzzled.");
  return 0;
}
