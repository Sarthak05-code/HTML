public class Binary {

    public static void main(String[] args) {
        Data d1 = new Data(101, "Sarthak", 100.00);

        System.out.println(d1.ID() + " " + d1.name() + " " + d1.salary());

        System.out.println(d1);
        System.out.println(d1.hashCode());

        d1.displayBonus();

        var result = switch (Double.valueOf(d1.getBonus())) {
            case Double b when b >= 50.0 -> "Excellent bonus";
            case Double b when b >= 25.0 -> "Average bonus";
            default -> "Low bonus";
        };

        System.out.println(result);
    }
}

record Data(int ID, String name, double salary) {
    public void displayBonus() {
        if (salary >= 100.0) {
            System.out.println("Bonus of 5%");
        } else {
            System.out.println("No bonus.");
        }
    }

    public double getBonus() {
        return salary * 0.5;
    }
}
