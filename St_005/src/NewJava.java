public class NewJava {

    public static void main(String[] args) {
        LoadBalancer ld = new LoadBalancer();
        ld.createTraffic(5000);
        ld.displayKids();
    }
}

class LoadBalancer {

    private int childrens;

    public void createTraffic(int childrens) {
        this.childrens += childrens;
    }

    public void displayKids() {
        System.out.println("The number of kids are : " + childrens);
    }
}
