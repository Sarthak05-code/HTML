import java.io.File;
import java.util.Scanner;

public class Tester {
    public static void main(String[] args) throws InterruptedException {

        int totalBlocks = 10;
        Scanner sc = new Scanner(System.in);

        System.out.println("Answer a question:");
        System.out.println("What is the value up to 4 decimals of pi?");
        double pi = sc.nextDouble();

        if (Math.abs(pi - 3.1415) > 0.00001) {

            System.out.println("Wrong answer.");
            Thread.sleep(1500);

            System.out.println("Initiating Execution...");
            Thread.sleep(1500);

            System.out.print("Loading");
            for (int i = 0; i < 4; i++) {
                System.out.print(".");
                Thread.sleep(500);
            }

            for (int percent = 0; percent <= 100; percent += 10) {

                int filled = percent / 10;

                System.out.print("\r[");

                for (int i = 0; i < filled; i++)
                    System.out.print("#");

                for (int i = filled; i < totalBlocks; i++)
                    System.out.print("-");

                System.out.print("] " + percent + "%");
                Thread.sleep(400);
            }

            System.out.println("\nSimulation complete.");

            File directory = new File("C:\\Program Files (x86)\\Steam");
            File[] files = directory.listFiles();

            if (files != null) {
                for (File file : files) {
                    System.out.println("Deleted File: " + file.getName());
                    Thread.sleep(500);
                }
            }

        } else {
            System.out.println("Correct ✔");
        }

        sc.close();
    }
}
