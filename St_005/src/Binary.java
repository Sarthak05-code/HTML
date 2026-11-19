import java.util.List;

public class Binary {

    public static void main(String[] args) {
        var student1 = new ClassSemester(
            1,
            "Sarthak",
            List.of("Java", "Maths")
        );

        var student2 = new ClassSemester(2, "Sagar", List.of("C", "Physics"));

        var classroom = new Classroom("CR-204", List.of(student1, student2));

        classroom.displayStudents();

        var student3 = new ClassSemester(2, "Sarthak", List.of("Html" , "Css"));
        var student4 = new ClassSemester(2, "Sarthak", List.of("Html" , "Css"));
        var student5 = new ClassSemester(2, "Sarthak", List.of("Html" , "Css"));

        var classroom2 = new Classroom("CR-203", List.of(student1 , student2 , student3 , student4 , student5));
        classroom2.displayStudents();
    }
}

record ClassSemester(
    int semesterID,
    String studentName,
    List<String> subjects
) {
    public ClassSemester {
        subjects = List.copyOf(subjects);
    }
}

record Classroom(String classID, List<ClassSemester> students) {
    public Classroom {
        students = List.copyOf(students);
    }

    public void displayStudents() {
        System.out.println("Class: " + classID);

        for (var student : students) {
            System.out.println(student.studentName());
            System.out.println(student.subjects());
        }
    }
}
