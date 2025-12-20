public class Interface {
    public static void main(String[] args) {
        C c = new C();
        c.Alpha();
        c.Beta();
    }
}

interface A {
    void Alpha();
}

interface B {
    void Beta();
}

class C implements A, B {
    public void Alpha() {
        System.out.println("Hello from Alpha");
    }

    public void Beta() {
        System.out.println("Hello from Beta");
    }

}