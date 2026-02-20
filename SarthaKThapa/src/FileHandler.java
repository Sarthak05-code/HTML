import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileHandler {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        Student student = new Student();

        final int n = 5;

        // Taking subject names
        for (int i = 1; i <= n; i++) {
            System.out.print("Enter Subject " + i + " name: ");
            String name = sc.nextLine().trim();

            if (!name.isEmpty()) {
                name = name.substring(0, 1).toUpperCase() +
                       name.substring(1).toLowerCase();
            }

            student.addSubject(new Subject(name));
        }

        // Taking marks
        for (Subject subject : student.getSubjects()) {

            while (true) {
                System.out.print("Enter marks for " + subject.getName() + ": ");
                int marks = sc.nextInt();

                if (MarksValidator.isValid(marks)) {
                    subject.setMarks(marks);
                    break;
                }

                System.err.println("Invalid marks! Must be between 0 and 50.");
            }
        }

        // Display result
        System.out.println("\nMarks Sheet:");
        student.displaySubjects();

        System.out.println("Total Marks: " + student.calculateTotal());
        System.out.println("Average: " + student.calculateAverage());

        sc.close();
    }
}
class Subject {

    private String name;
    private int marks;

    public Subject(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getMarks() {
        return marks;
    }

    public void setMarks(int marks) {
        this.marks = marks;
    }
}

class MarksValidator {

    private static final int TOTAL_MARKS = 50;

    public static boolean isValid(int marks) {
        return marks >= 0 && marks <= TOTAL_MARKS;
    }
}

class Student {

    private List<Subject> subjects = new ArrayList<>();

    public void addSubject(Subject subject) {
        subjects.add(subject);
    }

    public List<Subject> getSubjects() {
        return subjects;
    }

    public void displaySubjects() {
        for (Subject s : subjects) {
            System.out.println(s.getName() + " : " + s.getMarks());
        }
    }

    public int calculateTotal() {
        int total = 0;
        for (Subject s : subjects) {
            total += s.getMarks();
        }
        return total;
    }

    public double calculateAverage() {
        return calculateTotal() / (double) subjects.size();
    }
}