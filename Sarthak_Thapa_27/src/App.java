import java.util.Scanner;

public class App {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("The enter a letter: ");
        String a = sc.nextLine();
        
        
        for (int i = 0; i < a.length(); i++) {
            String binary = "";
            int remainder;
            char ch = a.charAt(i);
            int c = ch;

            while(c > 0)
            {
                remainder = c % 2;
                binary = remainder + binary;
                c /= 2;
            }

            System.out.println(ch + " - > " + binary);

            
        }



        sc.close();
    }
}
