public class Abstract {

    public static void main(final String[] args) {
        final Caller caller  = new Caller();
        caller.runner();
        caller.runner2();
    }
}

abstract class Main {
    abstract void runner();
}

interface MainInterface {
    public void runner2();
}

class Caller extends Main implements MainInterface {
    @Override
    public void runner() {
        System.out.println("The caller of the class. ");
    }

    @Override
    public void runner2() {
        System.out.println("Call of the class , again. ");
    }
}