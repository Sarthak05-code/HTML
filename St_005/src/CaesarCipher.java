public class CaesarCipher {
    public static void main(String[] args) {
        String text = "Hello World";
        int shift = 2;

        String encrypted = encrypt(text, shift);
        String decrypted = decrypt(encrypted, shift);

        System.out.println("Original:  " + text);
        System.out.println("Encrypted: " + encrypted);
        System.out.println("Decrypted: " + decrypted);
    }

    static String encrypt(String text, int shift) {
        StringBuilder result = new StringBuilder();
        for (char c : text.toCharArray()) {
            if (Character.isLetter(c)) {
                char base = Character.isUpperCase(c) ? 'A' : 'a';
                result.append((char) ((c - base + shift) % 26 + base));
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }

    static String decrypt(String text, int shift) {
        return encrypt(text, 26 - shift);
    }
}