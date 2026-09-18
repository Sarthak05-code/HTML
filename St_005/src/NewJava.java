//677375

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class NewJava {

    public static void main(String[] args) throws Exception {
        try {
            BufferedReader reader = new BufferedReader(
                new FileReader("FileTester.txt")
            );

            String line;

            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            reader.close();
        } catch (IOException e) {
            System.out.println("Could not find the file. ");
        }
    }
}
