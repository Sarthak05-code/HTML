public class Abstract {

    public static void main(final String[] args) {
        StaticTester st = new StaticTester();
        StaticTester.name();
        st.caller();
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

class Caller extends Main implements MainInterface, MainInterface2 {

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
        System.out.println("This class will run last. ");
    }
}

class StaticTester {

    Caller caller = new Caller();

    // this method call got turned into a method
    // and will call the method of another class as well.
    
    public void caller() {
        caller.runner();
        caller.runner2();
        caller.runner3();
    }

    // static method , the method here will be called directly by the className.
    public static void name() {
        System.out.println("The static caller. this is the static method");
    }
}
