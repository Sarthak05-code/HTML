import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        String code = "*1415#";
        System.out.printf("Dial a number: ");
        Scanner sc = new Scanner(System.in);
        String num = sc.nextLine();
        if(num.equals(code))
        {
            Thread.sleep(3000);
            System.out.println("Choose a data pack: ");
            System.out.println("1. Travelling: ");
            System.out.println("2. Abroad: ");
            System.out.println("3. Night Pack: ");
            System.out.println("4. Day Pack: ");
            System.out.println("5. Unlimited: ");

        }
        else{
            System.out.println("Dialing number: " + num);
        }

        sc.close();
    }
}


class DataPack{
    private boolean status = false;


}