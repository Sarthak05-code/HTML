public class App {
    public static void main(String[] args) {
        Rectangle rec = new Rectangle(5, 4);

        Rectangle recs = new Rectangle(rec);

        System.out.println("The value of the original is: " + rec.display());
        System.out.println("The area of the copied rectangle is: " + recs.display());

    }
}

class Rectangle {

    int length;
    int breadth;

    public Rectangle(int length, int breadth) {
        this.length = length;
        this.breadth = breadth;
    }

    public Rectangle(Rectangle rect) {
        this.length = rect.length;
        this.breadth = rect.breadth;
    }

    int display() {
        return length * breadth;
    }
}