import java.util.Scanner;

public class Main {

    // Century anchor days (for Gregorian calendar)
    // 1800s = Friday(5), 1900s = Wednesday(3), 2000s = Tuesday(2), 2100s = Sunday(0)
    private static final int[] CENTURY_ANCHORS = { 2, 0, 5, 3 }; // For centuries 2000, 2100, 2200, 2300 mod 400

    private static final String[] DAYS = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
    };

    /**
     * Check if a year is a leap year
     */
    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

    /**
     * Calculate the doomsday for a given year
     * Formula: (century_anchor + (year % 100)/12 + (year % 100)%12 + ((year % 100)%12)/4) % 7
     */
    public static int calculateDoomsday(int year) {
        int century = year / 100;
        int yearInCentury = year % 100;

        // Get century anchor (simplified for common centuries)
        int centuryAnchor;
        switch (century % 4) {
            case 0:
                centuryAnchor = 2;
                break; // 2000, 2400... → Tuesday
            case 1:
                centuryAnchor = 0;
                break; // 2100, 2500... → Sunday
            case 2:
                centuryAnchor = 5;
                break; // 2200, 2600... → Friday
            case 3:
                centuryAnchor = 3;
                break; // 2300, 2700... → Wednesday
            default:
                centuryAnchor = 2;
        }

        // Conway's calculation
        int a = yearInCentury / 12; // How many times 12 fits
        int b = yearInCentury % 12; // Remainder
        int c = b / 4; // Leap years in remainder

        return (centuryAnchor + a + b + c) % 7;
    }

    /**
     * Get the doomsday date for a specific month
     */
    public static int getDoomsdayDate(int month, int year) {
        boolean leap = isLeapYear(year);

        switch (month) {
            case 1:
                return leap ? 4 : 3; // Jan 3 (or 4 in leap year)
            case 2:
                return leap ? 29 : 28; // Last day of Feb
            case 3:
                return 0; // March 0 = Feb 28/29 (already handled)
            case 4:
                return 4; // 4/4
            case 5:
                return 9; // 5/9
            case 6:
                return 6; // 6/6
            case 7:
                return 11; // 7/11
            case 8:
                return 8; // 8/8
            case 9:
                return 5; // 9/5
            case 10:
                return 10; // 10/10
            case 11:
                return 7; // 11/7
            case 12:
                return 12; // 12/12
            default:
                return -1;
        }
    }

    /**
     * Calculate day of week for any date
     * Returns 0=Sunday through 6=Saturday
     */
    public static int getDayOfWeek(int day, int month, int year) {
        // Handle January and February as months 13 and 14 of previous year
        // (This is part of the algorithm for easier mental math)
        int adjustedYear = year;
        int adjustedMonth = month;

        if (month <= 2) {
            adjustedMonth += 12;
            adjustedYear--;
        }

        int doomsday = calculateDoomsday(adjustedYear);
        int doomsdayDate = getDoomsdayDate(month, year);

        // Calculate difference between target date and nearest doomsday
        int diff = day - doomsdayDate;

        // Adjust for negative differences
        int dayOfWeek = (doomsday + diff) % 7;
        if (dayOfWeek < 0) dayOfWeek += 7;

        return dayOfWeek;
    }

    /**
     * Alternative: Zeller's Congruence (for verification)
     */
    public static int zellersCongruence(int day, int month, int year) {
        if (month < 3) {
            month += 12;
            year--;
        }
        int q = day;
        int m = month;
        int k = year % 100;
        int j = year / 100;

        int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
        // Zeller returns 0=Saturday, 1=Sunday... convert to 0=Sunday
        return (h + 6) % 7;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("╔════════════════════════════════════════════╗");
        System.out.println("║     CONWAY'S DOOMSDAY ALGORITHM            ║");
        System.out.println("║     (Day of Week Calculator)               ║");
        System.out.println("╚════════════════════════════════════════════╝");
        System.out.println();

        // Demo with known dates
        System.out.println("📅 TESTING WITH KNOWN DATES:");
        System.out.println("─────────────────────────────────────");

        testDate(15, 8, 2026); // Today
        testDate(11, 9, 2001); // 9/11
        testDate(20, 7, 1969); // Moon landing
        testDate(6, 6, 1944); // D-Day
        testDate(14, 2, 2026); // Valentine's Day
        testDate(25, 12, 2026); // Christmas

        System.out.println();

        // Interactive mode
        System.out.println("🎯 INTERACTIVE MODE:");
        System.out.println("─────────────────────────────────────");

        while (true) {
            System.out.print("\nEnter date (DD MM YYYY) or 'quit': ");
            String input = scanner.nextLine().trim();

            if (input.equalsIgnoreCase("quit")) {
                System.out.println("Goodbye! 👋");
                break;
            }

            try {
                String[] parts = input.split("\\s+");
                if (parts.length != 3) {
                    System.out.println("❌ Please enter in format: DD MM YYYY");
                    continue;
                }

                int day = Integer.parseInt(parts[0]);
                int month = Integer.parseInt(parts[1]);
                int year = Integer.parseInt(parts[2]);

                if (!isValidDate(day, month, year)) {
                    System.out.println("❌ Invalid date!");
                    continue;
                }

                testDate(day, month, year);
            } catch (NumberFormatException e) {
                System.out.println("❌ Invalid input. Use numbers only.");
            }
        }

        scanner.close();
    }

    private static void testDate(int day, int month, int year) {
        int doomsdayResult = getDayOfWeek(day, month, year);
        int zellerResult = zellersCongruence(day, month, year);

        System.out.printf(
            "%02d/%02d/%d → %s",
            day,
            month,
            year,
            DAYS[doomsdayResult]
        );

        if (doomsdayResult == zellerResult) {
            System.out.println(" ✅ (verified)");
        } else {
            System.out.println(" ❌ MISMATCH with Zeller's!");
        }
    }

    private static boolean isValidDate(int day, int month, int year) {
        if (year < 1 || month < 1 || month > 12 || day < 1) return false;

        int[] daysInMonth = {
            0,
            31,
            28,
            31,
            30,
            31,
            30,
            31,
            31,
            30,
            31,
            30,
            31,
        };
        if (isLeapYear(year)) daysInMonth[2] = 29;

        return day <= daysInMonth[month];
    }
}
