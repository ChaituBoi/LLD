public class RunnableDemo implements Runnable{

    int threadNum;
    RunnableDemo(int val)
    {
        threadNum=val;
    }

    @Override
    public void run() {
        Singleton instance = Singleton.getInstance(threadNum);
        System.out.println(threadNum + " is running. Singleton instance has value: "+ instance.getData());
    }
}
