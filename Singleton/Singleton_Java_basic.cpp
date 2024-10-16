/****
This is a naive Singleton class implementation. Not thread safe at all. If two threads are created
and run simultaneously, you will end up with different instances.
****/
class Singleton{
    
    private Singleton(String val){
        data = val;
    }
    public String data;
    static private Singleton singletonObj=null;
    
    public static Singleton getInstance(String val)
    {
        if(singletonObj==null)
        {
            System.out.println("Singleton obj created with value: "+val);
            singletonObj = new Singleton(val);
            
            return singletonObj;
        }
        return singletonObj;
    }
};


class Main{
    

    
    public static void main(String argc[]){
        
        Singleton obj = Singleton.getInstance("Hello");
        Singleton obj2 = Singleton.getInstance("Baby");//doesn't print constructor log. But if run
        //parallely with prev obj as thread, you can end up with different copies.
        
    }
    
}