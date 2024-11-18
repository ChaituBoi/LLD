interface routeBuildStrategy{

    void buildRoute();

}
class byCar implements routeBuildStrategy{

    @Override
    public void buildRoute() {
        System.out.println("Showing route for Car.");
    }
}
class byWalk implements routeBuildStrategy{

    @Override
    public void buildRoute() {
        System.out.println("Showing route for walk.");
    }
}
class byBus implements routeBuildStrategy{

    @Override
    public void buildRoute() {
        System.out.println("Showing route for Bus.");
    }
}

class GPS
{
    routeBuildStrategy obj;

    public void setRouteBuildStrategy(routeBuildStrategy obj)
    {
        this.obj = obj;
    }
    public void buildRoute()
    {
        obj.buildRoute();
    }
}
//context here
public class GpsNav {

    public static void main(String[] args) {

        GPS gps = new GPS();
        System.out.println("Welcome to Maps-");

        String type="Car";
//        String type="Bus";
//        String type="Walk";
        switch (type)
        {
            case "Car":
                gps.setRouteBuildStrategy(new byCar());
                break;
            case "Bus":
                gps.setRouteBuildStrategy(new byBus());
                break;
            case "Walk":
                gps.setRouteBuildStrategy(new byWalk());
                break;

            default:
                throw new RuntimeException("Please enter correct input.");

        }
        gps.buildRoute();
    }
}
