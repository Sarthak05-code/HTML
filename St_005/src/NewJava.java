//677375
public class NewJava {

    public static void main(String[] args) throws Exception {
        Thread thread = Thread.startVirtualThread(() -> {
            System.out.println("Running on : " + Thread.currentThread());
        });
        thread.join();
    }
}
