import java.util.Scanner;

public class Binary {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter IP-Address: ");
        String ipAddress = scanner.nextLine();

        System.out.printf("The IP-Address -> %s\n", ipAddress);

        // 1. Validate the IP address format using Regular Expression (Regex)
        // This ensures 4 blocks of numbers ranging strictly from 0 to 255
        String zeroTo255 = "(\\d{1,2}|(0|1)\\" + "d{2}|2[0-4]\\d|25[0-5])";
        String ipRegex =
            zeroTo255 +
            "\\." +
            zeroTo255 +
            "\\." +
            zeroTo255 +
            "\\." +
            zeroTo255;

        if (!ipAddress.matches(ipRegex)) {
            System.out.println(
                "Error: Invalid IPv4 Address format! Please enter valid numbers (0-255)."
            );
            scanner.close();
            return; // Stops the program early
        }

        // 2. Split the validated IP address
        String[] octets = ipAddress.split("\\.");
        StringBuilder fullBinaryIP = new StringBuilder();

        // 3. Process each octet safely
        for (String octet : octets) {
            int number = Integer.parseInt(octet);
            String binary = Integer.toBinaryString(number);

            // Pad with leading zeros to make it exactly 8 bits
            String paddedBinary = String.format("%8s", binary).replace(
                ' ',
                '0'
            );

            fullBinaryIP.append(paddedBinary).append(".");
        }

        // Remove the trailing dot
        if (fullBinaryIP.length() > 0) {
            fullBinaryIP.setLength(fullBinaryIP.length() - 1);
        }

        System.out.println("Binary Format -> " + fullBinaryIP.toString());

        scanner.close();
    }
}
