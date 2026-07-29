import java.util.Scanner;

public class Main {

    private static final int[] CENTURY_ANCHORS = { 2, 0, 5, 3 };

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
    Check if the year is a leap year.
    */
    public static boolean isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

    /* Calculate the doomsday for a given year
    Formula  : (centuryAnchor + (year % 100)12 + (year %100)%12 + ((year % 100)%12)/4)%7
    */
    public static int calculateDoomsday(int year) {
        int century = year / 100;
        int yearInCentury = year % 100;
        int centuryAnchor;
        switch (century % 4) {
            case 0:
                centuryAnchor = 2;
                break;
            case 1:
                centuryAnchor = 0;
                break;
            case 2:
                centuryAnchor = 5;
                break;
            case 3:
                centuryAnchor = 3;
                break;
            default:
                centuryAnchor = 2;
        }

        int a = yearInCentury / 12;
        int b = yearInCentury % 12;
        int c = b / a;
        return (centuryAnchor + a + b + c) % 7;
    }

    // Get the doomsday of a specific month;
    public static int getDoomsDate(int month, int year) {
        boolean leap = isLeapYear(year);
        switch (month) {
            case 1:
                return leap ? 4 : 3; // Jan 3 or 4
            case 2:
                return leap ? 29 : 28; // last day of feb
            case 3:
                return 0;
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
                return -1;
        }
    }

    /*
    calculate day of week of any date
    return 0 if sunday and 6 is saturday
    */
    public static int getDayofWeek(int day, int month, int year) {
        int adjustyear = year;
        int adjustmonth = month;

        if (month <= 2) {
            adjustmonth += 12;
            adjustyear--;
        }

        int doomsday = calculateDoomsday(adjustyear);
        int doomsdayDate = getDoomsDate(month, year);

        int diff = day - doomsdayDate;

        int dayofWeek = (doomsday + diff) % 7;
        if (dayofWeek < 0) dayofWeek += 7;
        return dayofWeek;
    }

    /*
    Alternate : Zeller's Congruence , for verification;
    */
    public static int zellerCongruence(int day, int month, int year) {
        if (month < 3) {
            month += 12;
            year--;
        }

        int q = day;
        int m = month;
        int k = year % 100;
        int j = year / 100;

        int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
        return (h + 6) % 7;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("╔════════════════════════════════════════════╗");
        System.out.println("║     CONWAY'S DOOMSDAY ALGORITHM            ║");
        System.out.println("║     (Day of Week Calculator)               ║");
        System.out.println("╚════════════════════════════════════════════╝");
        System.out.println();

        System.out.println("Testing Dates : ");
        System.out.println("------------------");

        testDate(15 , 8 , 2026);
    }

    private static void testDate(int day , int month , int year) {
        int doomsdayResult = getDayofWeek(day, month, year);
        int zellerResult = zellerCongruence(day, month, year);

        System.out.printf("%02d | %02d | %0d -> %s" , day, month ,year , DAYS[doomsdayResult]);

        if (doomsdayResult == zellerResult) {
            System.out.println("Verified");
        } else {
            System.out.println("Error, somewhere. ");
        }

    
        
    }
}
