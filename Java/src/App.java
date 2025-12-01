public class App {
    public static void main(String[] args) {
        Student obj = new Student("Sarthak", 12, 3.4);

        obj.display();

    }
}

class Student {

    String name;
    int age;
    double gpa;

    Student(String name, int age, double gpa) {
        this.name = name;
        this.age = age;
        this.gpa = gpa;
    }

    void display() {
        System.out.println("Name: " + name + "  Age: " + age + "    Gpa: " + gpa);
    }
}