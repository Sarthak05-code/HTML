public class NewJava {

    public static void main(String[] args) {
        var ld = new LoadBalancer();
        ld.createTraffic(5000);
        ld.displayKids();

        var sb = new SeperateBalancer();
        sb.additionalBalance(1000);
        sb.displayKids();
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

class SeperateBalancer extends LoadBalancer {

    public void additionalBalance(int kids) {
        createTraffic(kids);
    }
}
