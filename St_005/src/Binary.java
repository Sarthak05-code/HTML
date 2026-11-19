import java.util.ArrayList;

public class Binary {

    public static void main(String[] args) {
        var student1 = new Student(
            101,
            "Sarthak",
            "ytsarthak123@gmail.com",
            20
        );

        var student2 = new Student(102, "sagar", "sagarKamal@gmail.com");
        var student3 = new Student(103, "Jhondoe");

        var subject1 = new Subjects("CS-200", "Maths", 5);
        var subject2 = new Subjects("CS-210", "Java", 4);
        var subject3 = new Subjects("CS-220", "Economics", 3);

        var student_one_result_one = new ExamResult(student1, subject1, 100);
        var student_one_result_two = new ExamResult(student1, subject2, 98);
        var student_one_result_three = new ExamResult(student1, subject3, 67);

        var student_two_result_one = new ExamResult(student2, subject1, 55);
        var student_two_result_two = new ExamResult(student2, subject2, 48);
        var student_two_result_three = new ExamResult(student2, subject3, 77);

        var student_three_result_one = new ExamResult(student3, subject1, 99);
        var student_three_result_two = new ExamResult(student3, subject2, 58);
        var student_three_result_three = new ExamResult(student3, subject3, 57);

        ArrayList<ExamResult> classResults = new ArrayList<>();
        classResults.add(student_one_result_one);
        classResults.add(student_one_result_two);
        classResults.add(student_one_result_three);
        classResults.add(student_two_result_one);
        classResults.add(student_two_result_two);
        classResults.add(student_two_result_three);
        classResults.add(student_three_result_one);
        classResults.add(student_three_result_two);
        classResults.add(student_three_result_three);

        for (var result : classResults) {
            System.out.println(result);
        }

        for (var result : classResults) {
            if (result.isPassed()) {
                System.out.println(
                    "The Passed Person Name : " + result.student().name()
                );
            }
        }

        double totalMarks = 0;
        ExamResult highest = classResults.get(0);
        int failedCount = 0;

        for (var result : classResults) {
            totalMarks += result.marks();

            if (result.marks() > highest.marks()) {
                highest = result;
            }

            if (!result.isPassed()) {
                failedCount += 1;
            }
        }

        double average = totalMarks / classResults.size();

        System.out.println("Average Marks : " + average);
        System.out.println("Highest Scorer " + highest.student().name());
        System.out.println("Highest Marks " + highest.marks());

        System.out.println("Failed student Count : " + failedCount);
    }
}

record Student(int id, String name, String email, int age) {
    public Student(int id, String name, String email) {
        this(id, name, email, 18);
    }

    public Student(int id, String name) {
        this(id, name, "unknown@gmail.com", 18);
    }

    public Student {
        if (id <= 0) {
            throw new IllegalArgumentException("The ID can't be negative.");
        }

        if (name == null || name.isBlank()) {
            throw new IllegalArgumentException("Name can't be Null or Empty.");
        }

        if (email == null || !email.contains("@")) {
            throw new IllegalArgumentException("Invalid email.");
        }

        if (age < 16 || age > 100) {
            throw new IllegalArgumentException(
                "Age should be between 16 and 100."
            );
        }
        name = name.toUpperCase(java.util.Locale.ROOT);
    }
}

record Subjects(String subjectCode, String subjectName, int creditHours) {
    public Subjects {
        if (subjectCode == null || subjectCode.isBlank()) {
            throw new IllegalArgumentException("Invalid subject code.");
        }

        if (subjectName == null || subjectName.isBlank()) {
            throw new IllegalArgumentException("Invalid subject name.");
        }

        if (creditHours < 1 || creditHours > 6) {
            throw new IllegalArgumentException(
                "CreditHours should be between 1 and 6."
            );
        }
    }
}

record ExamResult(Student student, Subjects subjects, double marks) {
    public ExamResult {
        if (student == null || subjects == null) {
            throw new IllegalArgumentException("The records can't be empty.");
        }

        if (marks < 0 || marks > 100) {
            throw new IllegalArgumentException(
                "Marks must be between 0 and 100."
            );
        }
    }

    public boolean isPassed() {
        return marks >= 40;
    }

    // since marks are double, we use .0
    public String getGrade() {
        if (marks >= 90.0) {
            return "A+";
        } else if (marks >= 80.0) {
            return "A";
        } else if (marks >= 70.0) {
            return "B+";
        } else if (marks >= 60.0) {
            return "B";
        } else if (marks >= 50.0) {
            return "C";
        } else if (marks >= 40.0) {
            return "D";
        } else {
            return "F";
        }
    }
}
