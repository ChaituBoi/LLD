public class Singleton {

    private static int data;
    private Singleton(int val)
    {
        data = val;
    }
    private static Singleton myInstance = null;

    public static Singleton getInstance(int val)
    {
        synchronized (Singleton.class)
        {
            if(myInstance==null)
            {
                System.out.println("Init Singleton with value: "+ val);
                myInstance = new Singleton(val);

            }
        }

        return myInstance;
    }

    public int getData() {
        return data;
    }
}
