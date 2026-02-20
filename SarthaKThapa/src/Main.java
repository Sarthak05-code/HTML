import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter how many subjects: ");
        int number = sc.nextInt();

        ArrayList<Integer> lists = new ArrayList<>();

        for (int i = 0; i < number; i++) {
            System.out.printf("Enter marks for subject %d: ", i + 1);
            lists.add(sc.nextInt());
        }

        System.out.print("Enter full marks per subject: ");
        int full = sc.nextInt();

        Marks marks = new Marks(lists, full);

        float total = marks.getTotal();
        float gpa = marks.getGpa();

        System.out.println("Total Marks: " + total + "/" + (number * full));
        System.out.printf("GPA (4.0 scale): %.2f\n", gpa);

        sc.close();
    }
}

class Marks {

    private ArrayList<Integer> marks;
    private int maxMarks;
    private float total;  // calculated once

    Marks(ArrayList<Integer> marks, int maxMarks) {
        this.marks = marks;
        this.maxMarks = maxMarks;
        calculateTotal();  // calculate once during object creation
    }

    // Private method (internal use only)
    private void calculateTotal() {
        total = 0;

        for (int i = 0; i < marks.size(); i++) {
            total += marks.get(i);
        }
    }

    public float getTotal() {
        return total;
    }

    public float getGpa() {
        return (total / (maxMarks * marks.size())) * 4;
    }
}
