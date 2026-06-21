public class Abstract {

    public static void main(final String[] args) {
        final Caller caller  = new Caller();
        caller.runner();
        caller.runner2();
        caller.runner3();
    }
}

abstract class Main {
    abstract void runner();
}

interface MainInterface {
    public void runner2();
}
interface MainInterface2 {
    public void runner3();
}

class Caller extends Main implements MainInterface ,MainInterface2 {
    @Override
    public void runner() {
        System.out.println("The caller of the class. ");
    }

    @Override
    public void runner2() {
        System.out.println("Call of the class , again. ");
    }

    @Override
    public void runner3() {
        System.out.println("This will run last. ");
    }
}