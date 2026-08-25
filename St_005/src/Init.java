public class Init {

    public static void main(String[] args) {
        Initialize<Circle> circle = Initialize.init(new Circle());

        double result = circle.get().area(12);

        System.out.printf("The value is %.2f%n", result);
    }

    static class Initialize<T> {

        private T object;

        private Initialize(T object) {
            this.object = object;
        }

        public static <T> Initialize<T> init(T object) {
            return new Initialize<>(object);
        }

        public T get() {
            return object;
        }
    }

    static class Circle {

        private static final double PI = 3.1415;

        public double area(double radius) {
            return PI * radius * radius;
        }
    }
}
