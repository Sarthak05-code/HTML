//677375

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class NewJava {

    public static void main(String[] args) throws Exception {
        try {
            // String content = Files.readString(Path.of("FileTester.txt"));
            // System.out.println(content);
            Files.lines(Path.of("FileTester.txt")).forEach(System.out::println);
        } catch (IOException e) {
            System.out.println("Could not find the file. ");
        }
    }
}
