import java.util.ArrayList;
import java.util.Random;

public class Abstract {

    public static void main(String[] args) {
        Random rand = new Random();
        ArrayList<Integer> array = new ArrayList<>();
        Function function = new Function();
        Abstraction abstraction = new Abstraction();
        Inheritence inheritence = new Inheritence();

        for (int i = 0; i < 3; ++i) {
            array.add(rand.nextInt(0, 3) + 1);
        }
        System.out.println("The different number stored: " + array);

        for (Integer arr : array) {
            if (arr == 1) function.run();
            else if (arr == 2) abstraction.run();
            else inheritence.run();
        }
    }
}

class Function {

    public void run() {
        System.out.println("Function class was called");
    }
}

class Abstraction {

    public void run() {
        System.out.println("Abstraction class was called");
    }
}

class Inheritence {

    public void run() {
        System.out.println("Inheritance class was called");
    }
}
