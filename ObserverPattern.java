import java.util.ArrayList;

interface IObserver{
  void update(String data);
}
interface IObservable{
  void add(IObserver o);
  void remove(IObserver o);
  void sendNotify();
}

class MobileUser implements IObserver
{
  String userName;
  public MobileUser(String userName)
  {
    this.userName = userName;
  }
  public void update(String data)
  {
    System.out.println("Trending now - \""+ data+"\". Viewing on mobile by "+userName+".");
  }
}

class LaptopUser implements IObserver
{
  String userName;
  public LaptopUser(String userName)
  {
    this.userName = userName;
  }
  public void update(String data)
  {
    System.out.println("Trending now - \""+ data+"\". Viewing on laptop by "+userName+".");
  }
}

class NewsWebsite implements IObservable
{
  ArrayList<IObserver> subscriberList = new ArrayList<IObserver>();
  String latestTrendingArticle = "DEFAULT";
  public void add(IObserver o)
  {
    subscriberList.add(o);
  }
  public void remove(IObserver o)
  {
    subscriberList.remove(o);
  }
  public void sendNotify()
  {
    for(int i=0;i<subscriberList.size();i++)
    {
      subscriberList.get(i).update(latestTrendingArticle);
    }
  }
  
  public void changeTrendingArticle(String articleName)
  {
    latestTrendingArticle = articleName;
    sendNotify();
  }
}
public class ObserverPattern{
  
  public static void main(String[] args)
  {
    MobileUser mUser1 = new MobileUser("Chaitanya");
    LaptopUser lUser1 = new LaptopUser("Ayush");
    NewsWebsite instNewsWebsite = new NewsWebsite();
    
    instNewsWebsite.add(mUser1);
    instNewsWebsite.changeTrendingArticle("Valve announces Half Life 3. Fans elated!!");
    
    instNewsWebsite.add(lUser1);
    instNewsWebsite.changeTrendingArticle("Salman Khan apologises for the black buck killing.");
  }
  
}