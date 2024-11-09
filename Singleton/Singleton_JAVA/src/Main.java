public class Main {
    public static void main(String[] args) {

        System.out.println("Both instances should have the same value, 1 or 2 to make sure only one instance of Singleton created.");
        RunnableDemo runnableInstance1 = new RunnableDemo(1);
        Thread thread1 = new Thread(runnableInstance1);
        RunnableDemo runnableInstance2 = new RunnableDemo(2);
        Thread thread2 = new Thread(runnableInstance2);

        thread1.start();
//        thread1.join();
        thread2.start();
    }
}