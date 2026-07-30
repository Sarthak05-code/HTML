import java.util.Scanner;

public class Main {

    /*
     * Day indexes:
     * 0 = Sunday
     * 1 = Monday
     * 2 = Tuesday
     * 3 = Wednesday
     * 4 = Thursday
     * 5 = Friday
     * 6 = Saturday
     */

    private static final String[] DAYS = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
    };

    /*
     * Century anchors for Gregorian calendar.
     *
     * century % 4:
     * 0 -> Tuesday
     * 1 -> Sunday
     * 2 -> Friday
     * 3 -> Wednesday
     *
     * Numeric representation:
     * Tuesday    = 2
     * Sunday     = 0
     * Friday     = 5
     * Wednesday  = 3
     */
    private static final int[] CENTURY_ANCHORS = { 2, 0, 5, 3 };

    /**
     * Check whether a year is a leap year.
     */
    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

    /**
     * Calculate the Doomsday for a given year.
     *
     * Conway's formula:
     *
     * century anchor
     * + (year / 12)
     * + (year % 12)
     * + ((year % 12) / 4)
     * --------------------------------
     *                 % 7
     *
     * Returns:
     * 0 = Sunday
     * 1 = Monday
     * 2 = Tuesday
     * 3 = Wednesday
     * 4 = Thursday
     * 5 = Friday
     * 6 = Saturday
     */
    public static int calculateDoomsday(int year) {
        int century = year / 100;
        int yearInCentury = year % 100;

        // Find the century anchor.
        int centuryAnchor = CENTURY_ANCHORS[century % 4];

        // Conway's calculation.
        int a = yearInCentury / 12;
        int b = yearInCentury % 12;
        int c = b / 4;

        return (centuryAnchor + a + b + c) % 7;
    }

    /**
     * Get the month's Doomsday date.
     *
     * These are the dates that fall on the year's Doomsday.
     *
     * Normal year:
     * Jan 3, Feb 28, Mar 14, Apr 4, May 9, Jun 6,
     * Jul 11, Aug 8, Sep 5, Oct 10, Nov 7, Dec 12
     *
     * Leap year:
     * Jan 4, Feb 29, Mar 14, Apr 4, May 9, Jun 6,
     * Jul 11, Aug 8, Sep 5, Oct 10, Nov 7, Dec 12
     */
    public static int getDoomsdayDate(int month, int year) {
        boolean leap = isLeapYear(year);

        switch (month) {
            case 1:
                return leap ? 4 : 3;
            case 2:
                return leap ? 29 : 28;
            case 3:
                return 14;
            case 4:
                return 4;
            case 5:
                return 9;
            case 6:
                return 6;
            case 7:
                return 11;
            case 8:
                return 8;
            case 9:
                return 5;
            case 10:
                return 10;
            case 11:
                return 7;
            case 12:
                return 12;
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }

    /**
     * Calculate the day of the week for a given date
     * using Conway's Doomsday Algorithm.
     *
     * Returns:
     * 0 = Sunday
     * 1 = Monday
     * 2 = Tuesday
     * 3 = Wednesday
     * 4 = Thursday
     * 5 = Friday
     * 6 = Saturday
     */
    public static int getDayOfWeek(int day, int month, int year) {
        // Find the Doomsday for the year.
        int doomsday = calculateDoomsday(year);

        // Find the date in this month that falls on Doomsday.
        int doomsdayDate = getDoomsdayDate(month, year);

        // Difference between our date and the month's Doomsday.
        int difference = day - doomsdayDate;

        /*
         * Math.floorMod() is used instead of % so that
         * negative values are handled correctly.
         */
        return Math.floorMod(doomsday + difference, 7);
    }

    /**
     * Zeller's Congruence.
     *
     * This is an independent algorithm that we use
     * to verify the result of Conway's algorithm.
     *
     * Returns:
     * 0 = Sunday
     * 1 = Monday
     * 2 = Tuesday
     * 3 = Wednesday
     * 4 = Thursday
     * 5 = Friday
     * 6 = Saturday
     */
    public static int zellersCongruence(int day, int month, int year) {
        // January and February are treated as months 13 and 14
        // of the previous year in Zeller's formula.
        if (month < 3) {
            month += 12;
            year--;
        }

        int q = day;
        int m = month;

        int k = year % 100;
        int j = year / 100;

        int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;

        /*
         * Zeller's result:
         *
         * 0 = Saturday
         * 1 = Sunday
         * 2 = Monday
         * ...
         *
         * Convert it to our system:
         *
         * 0 = Sunday
         * 1 = Monday
         * ...
         */
        return (h + 6) % 7;
    }

    /**
     * Validate a date.
     */
    public static boolean isValidDate(int day, int month, int year) {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false;
        }

        int[] daysInMonth = {
            0,
            31, // January
            28, // February
            31, // March
            30, // April
            31, // May
            30, // June
            31, // July
            31, // August
            30, // September
            31, // October
            30, // November
            31, // December
        };

        // February has 29 days in a leap year.
        if (isLeapYear(year)) {
            daysInMonth[2] = 29;
        }

        return day <= daysInMonth[month];
    }

    /**
     * Test a date using both algorithms.
     */
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

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("╔════════════════════════════════════════════╗");
        System.out.println("║       CONWAY'S DOOMSDAY ALGORITHM          ║");
        System.out.println("║        DAY OF WEEK CALCULATOR              ║");
        System.out.println("╚════════════════════════════════════════════╝");
        System.out.println();

        // --------------------------------------------------
        // TESTING
        // --------------------------------------------------

        System.out.println("📅 TESTING WITH KNOWN DATES:");
        System.out.println("─────────────────────────────────────");

        testDate(15, 8, 2026); // Example date
        testDate(11, 9, 2001); // 9/11
        testDate(20, 7, 1969); // Moon landing
        testDate(6, 6, 1944); // D-Day
        testDate(14, 2, 2026); // Valentine's Day
        testDate(25, 12, 2026); // Christmas

        // Additional tests specifically for January and February.
        System.out.println();
        System.out.println("📅 JANUARY / FEBRUARY TESTS:");
        System.out.println("─────────────────────────────────────");

        testDate(1, 1, 2026);
        testDate(3, 1, 2026);
        testDate(28, 2, 2026);
        testDate(29, 2, 2024);
        testDate(4, 1, 2024);
        testDate(29, 2, 2000);

        // --------------------------------------------------
        // INTERACTIVE MODE
        // --------------------------------------------------

        System.out.println();
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
}
