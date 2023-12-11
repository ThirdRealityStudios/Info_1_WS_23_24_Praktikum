#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEIGHT 6 // Einfach immer 6 Zeilen, um das Monatsraster zu repräsentieren pauschal.
#define WIDTH 7 // 7 Wochentage

#define GERMANY 0
#define SPAIN 1
#define USA 2
#define FRANCE 3
#define CHINA 4

#define ONEDAY 86400
#define ONEHOUR 3600
#define ONEMINUTE 60
#define ONESECOND 1

int isLeapYear(int year)
{
    int isMulitpleOf400 = year % 400 == 0;
    int isMultipleOf4 = year % 4 == 0;
    int isSecularYear = year % 100 == 0;

    // Jedes 400. Jahr ist ein Schaltjahr sowie alle Jahre,
    // die sich durch 4 teilen lassen (außer jedes 100. Jahr).
    return isMulitpleOf400 || (isMultipleOf4 && !isSecularYear);
}

int isDateValid(int day, int month, int year)
{
    int isBasicallyCorrect = year > 0 && month > 0 && month < 13 && day > 0 && day < 32;

    if(!isBasicallyCorrect)
    {
        return 0;
    }

    if(month <= 7 && month % 2 == 0)
    {
        return month == 2 ? (isLeapYear(year) ? day < 30 : day < 29) : day < 31;
    }
    else if(month <= 7 && month % 2 != 0)
    {
        return day < 32;
    }

    if(month > 7 && month % 2 == 0)
    {
        return day < 32;
    }
    else if(month > 7 && month % 2 != 0)
    {
        return day < 31;
    }

    return 0;
}

void printDate(int day, int month, int year, int countryCode)
{
    switch(countryCode)
    {
        case GERMANY:
            printf("%02d.%02d.%04d", day, month, year);
            break;

        case SPAIN:
            printf("%02d/%02d/%04d", day, month, year);
            break;

        case USA:
            printf("%02d/%02d/%04d", month, day, year);
            break;

        case FRANCE:
            printf("%02d/%02d/%04d", day, month, year);
            break;

        case CHINA:
            printf("%04d-%02d-%02d", year, month, day);
            break;

        default:

            printDate(day, month, year, USA);
    }

    puts("");
}

double floor(double toFloor)
{
    return (double) ((int) toFloor);
}

int zellerAlgorithm(int day, int month, int year)
{
    // Für Januar und Februar nur lt. Wikipedia.
    year = (month == 1 || month == 2) ? year - 1 : year;
    month = (month == 1 || month == 2) ? month + 12 : month;

    double h = 0,
            q = (double) day,
            m = (double) month,
            K = (double) (year % 100),
            J = (double) year / 100.0;

    double operand1 = q,
            operand2 = floor((13 * (m + 1)) / 5.0),
            operand3 = K,
            operand4 = floor(K / 4.0),
            operand5 = floor(J / 4.0),
            operand6 = 2 * J;

    h = operand1 + operand2 + operand3 + operand4 + operand5 - operand6;

    return ((int) h + 1) % 7;
}

char* getWeekdayString(int weekday)
{
    switch(weekday)
    {
        case 1:
            return "Montag";
            break;

        case 2:
            return "Dienstag";
            break;

        case 3:
            return "Mittwoch";
            break;

        case 4:
            return "Donnerstag";
            break;

        case 5:
            return "Freitag";
            break;

        case 6:
            return "Samstag";
            break;

        case 7:
            return "Sonntag";
            break;

        default:
            return "Unbekannter Fehler (Wert ungueltig)";
    }
}

int getWeekday(int day, int month, int year)
{
    // Für Januar und Februar nur lt. Wikipedia.
    year = (month == 1 || month == 2) ? year - 1 : year;
    month = (month == 1 || month == 2) ? month + 12 : month;

    double h = 0,
            q = (double) day,
            m = (double) month,
            K = (double) (year % 100),
            J = (double) year / 100.0;

    double operand1 = q,
            operand2 = floor((13 * (m + 1)) / 5.0),
            operand3 = K,
            operand4 = floor(K / 4.0),
            operand5 = floor(J / 4.0),
            operand6 = 2 * J;

    h = operand1 + operand2 + operand3 + operand4 + operand5 - operand6;

    h = ((int) h + 1) % 7;

    // s. Variable "d" bei:
    // https://en.wikipedia.org/wiki/Zeller's_congruence#Formula
    // Hiermit werden die Wochentage verschoben,
    // sodass 0 nicht mehr Samstag ist und 6 ist Freitag.
    // Stattdessen ist 1 jetzt Montag und 7 ist jetzt Sonntag.
    // Somit sind die zurückgegebenen Werte jetzt für Normalos
    // besser verständlich.
    int d = (((int) h + 5) % 7) + 1;

    // Jetzt wird der entsprechende Tag zurückgegeben.
    return d;
}

int** createArray()
{
    int **arr = calloc(HEIGHT, sizeof(int));

    for(int i = 0; i < HEIGHT; i++)
    {
        arr[i] = calloc(WIDTH, sizeof(int));
    }

    return arr;
}

void insertDay(int **grid, int weekday, int day, int firstDayX)
{
    /**
     * Bugfix:
     *
     * Hier muss zusätzlich "firstDayX" hinzuaddiert werden.
     * Grund ist,
     * dass jeder Monat einen unterschiedlichen ersten Wochentag hat
     * im Bezug auf den 01.mm.yyyy jeden Monats.
     * Beispielsweise ist der 01.11.2023 ein Mittwoch,
     * während der 01.05.2023 wiederum ein Montag gewesen ist.
     * Folglich kann man nicht einfach den Monatstag durch 7 teilen,
     * um die Zeile zu ermitteln,
     * wo dieser eingefügt werden soll.
     * Nur deswegen muss ich also "firstDayX" noch zusätzlich hinzuaddieren,
     * um das wieder auszugleichen.
     * Dann erscheint der jeweilige Tag auch in der richtigen Zeile.
     * Ohne "+ firstDayX" würden der Montag und der Dienstag immer
     * eine Zeile später erscheinen als eigentlich erwartet (das war der Bug).
     * Die Wertzuweisung vor dem Bugfix lautete also schlicht:
     * int y = (day - 1) / WIDTH;
     * Das war aber falsch..
     */
    int y = (day + firstDayX - 1) / WIDTH;

    int x = weekday - 1;

    grid[y][x] = day;
}

int maxDaysOfMonth(int month, int year)
{
    if(month % 2 == 0)
    {
        if(month == 2)
        {
            return isLeapYear(year) ? 29 : 28;
        }

        return month <= 7 ? 30 : 31;
    }
    else
    {
        return month <= 7 ? 31 : 30;
    }
}

int** getMonthArray(int month, int year)
{
    int **grid = createArray();

    // Ermittelt die x-Position des ersten Tages in einem Monat "month"
    // (für die erste Zeile),
    // um später dann der Funktion insertDay(..) unten übergeben zu werden.
    int firstDayX = getWeekday(1, month, year) - 1;

    for(int day = 1; day <= maxDaysOfMonth(month, year); day++)
    {
        insertDay(grid, getWeekday(day, month, year), day, firstDayX);
    }

    return grid;
}

char* getMonthString(int month)
{
    switch(month)
    {
        case 1:
            return "Januar";
            break;

        case 2:
            return "Februar";
            break;

        case 3:
            return "Maerz";
            break;

        case 4:
            return "April";
            break;

        case 5:
            return "Mai";
            break;

        case 6:
            return "Juni";
            break;

        case 7:
            return "Juli";
            break;

        case 8:
            return "August";
            break;

        case 9:
            return "September";
            break;

        case 10:
            return "Oktober";
            break;

        case 11:
            return "November";
            break;

        case 12:
            return "Dezember";
            break;

        default:
            return "Fehlermonat";
            break;
    }
}

void printMonthGrid(int month, int year)
{
    if(!(month > 0 && month < 13 && year > 1969 && year < 2101))
    {
        return; // Print nothing if the given month and year is not supported or invalid.
    }

    // Den Monat und Jahr ausgeben oberhalb des Kalendermonats.
    printf("%s %04d\n", getMonthString(month), year);

    int **monthArray = getMonthArray(month, year);

    int monthDayWidth = 4;

    for(int weekday = 1; weekday <= 7; weekday++)
    {
        char *weekdayString = getWeekdayString(weekday);

        // Nur die ersten beiden Zeichen merken vom Wochentag zur Ausgabe,
        // aber wichtig hier: in sind ALLE Strings immer NULL-terminiert,
        // daher brauche ich das Zeichen '\0' noch am Ende (=> insgesamt 3 Zeichen benötigt zum Speichern).
        char weekdayShortenedString[3] = {weekdayString[0], weekdayString[1], '\0'};

        printf("%*s", monthDayWidth, weekdayShortenedString);
    }

    puts("");

    for(int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            int day = monthArray[y][x];

            if(day > 0)
            {
                printf("%*d", monthDayWidth, day);
            }
            else
            {
                printf("%*s", monthDayWidth, "");
            }
        }

        puts("");
    }
}

int isEarlierThan(int dateEarlier[], int dateLater[])
{
    // Compare year if older than the other one.
    if(dateEarlier[2] < dateLater[2])
    {
        return 1;
    }
    else if(dateEarlier[2] > dateLater[2])
    {
        return 0;
    }
    else // both years equal to each other:
    {
        // Compare both months
        if(dateEarlier[1] < dateLater[1])
        {
            return 1;
        }
        else if(dateEarlier[1] > dateLater[1])
        {
            return 0;
        }
        else // both months equal to each other:
        {
            // Compare both days
            if(dateEarlier[0] < dateLater[0])
            {
                return 1;
            }
            else if(dateEarlier[0] > dateLater[0])
            {
                return 0;
            }
            else // both days equal to each other:
            {
                // Compare both hours
                if(dateEarlier[3] < dateLater[3])
                {
                    return 1;
                }
                else if(dateEarlier[3] > dateLater[3])
                {
                    return 0;
                }
                else // both hours equal to each other:
                {
                    // Compare both minutes
                    if(dateEarlier[4] < dateLater[4])
                    {
                        return 1;
                    }
                    else if(dateEarlier[4] > dateLater[4])
                    {
                        return 0;
                    }
                    else // both minutes equal to each other:
                    {
                        // Compare both seconds
                        if(dateEarlier[5] < dateLater[5])
                        {
                            return 1;
                        }
                        else if(dateEarlier[5] > dateLater[5])
                        {
                            return 0;
                        }
                        else // both seconds equal to each other
                        {
                            return 0; // both date objects are identical!
                        }
                    }
                }
            }
        }
    }
}

void incDateSecond(int date[])
{
    int second = date[5],
        minute = date[4],
        hour   = date[3],

        year   = date[2],
        month  = date[1],
        day    = date[0];

    second++; // Increment the second.

    if(second > 59)
    {
        minute++; // Increment the minute.
        second = 0; // Reset the seconds.
    }

    if(minute > 59)
    {
        hour++; // Increment the hour.
        minute = 0; // Reset the minutes.
    }

    if(hour > 23)
    {
        day++; // Increment the days.
        hour = 0; // Reset the hours.
    }

    if(day > maxDaysOfMonth(date[1], date[2]))
    {
        month++; // Increment the month.
        day = 1; // Reset the days (first of next month).
    }

    if(month > 12)
    {
        month = 1; // Reset month to the first of next year.
        year++; // Increment the year.
    }

    date[0] = day;
    date[1] = month;
    date[2] = year;
    date[3] = hour;
    date[4] = minute;
    date[5] = second;
}

long long toUnixtime(int date[])
{
    int startDate[] = {1,1,1970,0,0,0};

    int daysCurrentMonth = 0;

    long long seconds = 0;

    while(isEarlierThan(startDate, date))
    {
        seconds++;
        incDateSecond(startDate);
    }

    return seconds;
}

void printWeekday(int day, int month, int year)
{
    printf("%s\n", getWeekdayString(getWeekday(day, month, year)));
}

void testIsEarlierThan()
{
    int dateEarlier[] = {1, 1, 1970, 0, 0, 0};
    int dateLater[] = {1, 1, 1970, 0, 0, 1};

    puts("testIsEarlierThan()");
    puts("");
    printf("1/1/1970 0:00:00 is earlier than 1/1/1970 0:00:01 => %s\n", (isEarlierThan(dateEarlier, dateLater) ? "yes" : "no"));
    puts("");

    int dateEarlier1[] = {1, 1, 1970, 0, 0, 0};
    int dateLater1[] = {1, 1, 1970, 0, 0, 0};
    printf("1/1/1970 0:00:00 is earlier than 1/1/1970 0:00:00 => %s\n", (isEarlierThan(dateEarlier1, dateLater1) ? "yes" : "no"));
    puts("");

    int dateEarlier2[] = {1, 1, 1971, 0, 0, 0};
    int dateLater2[] = {1, 1, 1970, 0, 0, 0};
    printf("1/1/1971 0:00:00 is earlier than 1/1/1970 0:00:00 => %s\n", (isEarlierThan(dateEarlier2, dateLater2) ? "yes" : "no"));
    puts("");

    int dateEarlier3[] = {1, 1, 1970, 0, 0, 0};
    int dateLater3[] = {1, 1, 1970, 12, 0, 0};
    printf("1/1/1970 0:00:00 is earlier than 1/1/1970 12:00:00 => %s\n", (isEarlierThan(dateEarlier3, dateLater3) ? "yes" : "no"));
    puts("");

    int dateEarlier4[] = {23, 2, 1981, 0, 0, 0};
    int dateLater4[] = {1, 1, 1991, 0, 0, 19};
    printf("2/23/1981 0:00:00 is earlier than 1/1/1991 0:00:19 => %s\n", (isEarlierThan(dateEarlier4, dateLater4) ? "yes" : "no"));
    puts("");

    int dateEarlier5[] = {1, 3, 1970, 0, 0, 0};
    int dateLater5[] = {28, 2, 1970, 23, 59, 59};
    printf("1/3/1970 0:00:00 is earlier than 28/2/1970 0:00:19 => %s\n", (isEarlierThan(dateEarlier5, dateLater5) ? "yes" : "no"));
    puts("");
}

void testIncDateSecond(int date[])
{
    puts("testIncDateSecond()");
    puts("");
    printf("Incrementing %02d:%02d:%02d ", date[3], date[4], date[5]);
    printDate(date[0], date[1], date[2], USA);
    printf("=> ");
    incDateSecond(date);
    printf("%02d:%02d:%02d ", date[3], date[4], date[5]);
    printDate(date[0], date[1], date[2], USA);
    puts("");
}

void testDateIncrementations()
{
    int date0[] = {1,1,1970,0,0,0};
    testIncDateSecond(date0);

    int date1[] = {1,1,1970,0,0,59};
    testIncDateSecond(date1);

    int date2[] = {1,1,1970,0,59,59};
    testIncDateSecond(date2);

    int date3[] = {1,1,1970,23,59,59};
    testIncDateSecond(date3);

    int date4[] = {31,1,1970,23,59,59};
    testIncDateSecond(date4);

    int date5[] = {28,2,1970,23,59,59};
    testIncDateSecond(date5);
}

void testToUnixTime(int date[])
{
    puts("\ntestToUnixTime()");
    puts("");
    printf("Unix-Time calculated for %02d:%02d:%02d ", date[3], date[4], date[5]);
    printDate(date[0], date[1], date[2], USA);
    printf("=> %lld", toUnixtime(date));
    puts("");
}

void testToUnixTimes()
{
    int date0[] = {1,1,1970,0,0,0};
    testToUnixTime(date0);

    int date1[] = {1,1,1970,0,0,59};
    testToUnixTime(date1);

    int date2[] = {1,1,1970,0,59,59};
    testToUnixTime(date2);

    int date3[] = {1,1,1970,23,59,59};
    testToUnixTime(date3);

    int date4[] = {31,1,1970,23,59,59};
    testToUnixTime(date4);

    int date5[] = {28,2,1970,23,59,59};
    testToUnixTime(date5);

    int date6[] = {11,12,2023,13,22,29};
    testToUnixTime(date6);
}

void testGetWeekday()
{
    puts("testGetWeekday()");
    puts("");
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(1, 1, 2000), 1, 1, 2000);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(28, 2, 2022), 28, 2, 2022);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(28, 2, 2021), 28, 2, 2021);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(28, 2, 2020), 28, 2, 2020);
    puts("");
}

void testPrintWeekday()
{
    int day = 10;

    puts("");

    puts("testPrintWeekday()");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 10., ein Freitag, s. Windows-Kalender.
    printWeekday(day++, 11, 2023);
    puts("Expected: Freitag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 11., ein Samstag
    printWeekday(day++, 11, 2023);
    puts("Expected: Samstag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 12., ein Sonntag
    printWeekday(day++, 11, 2023);
    puts("Expected: Sonntag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 13., ein Montag
    printWeekday(day++, 11, 2023);
    puts("Expected: Montag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 14., ein Dienstag
    printWeekday(day++, 11, 2023);
    puts("Expected: Dienstag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 15., ein Mittwoch
    printWeekday(day++, 11, 2023);
    puts("Expected: Mittwoch");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 16., ein Donnerstag
    printWeekday(day++, 11, 2023);
    puts("Expected: Donnerstag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 17., ein Freitag (wie gerade auch)
    printWeekday(day++, 11, 2023);
    puts("Expected: Freitag");

    puts("");

    printDate(day, 11, 2023, GERMANY); // der 18., ein Samstag (wie zu Anfang auch)
    printWeekday(day++, 11, 2023);
    puts("Expected: Samstag");

    puts("");

    puts("changing years, keeping day and month:");

    printDate(28, 2, 2023, GERMANY); // der 28.2.23, ein Dienstag lt. Windows-Kalender.
    printWeekday(28, 2, 2023);
    puts("Expected: Dienstag");

    puts("");

    printDate(28, 2, 2022, GERMANY); // der 28.2.22, ein Montag lt. Windows-Kalender.
    printWeekday(28, 2, 2022);
    puts("Expected: Montag");

    puts("");

    printDate(28, 2, 2021, GERMANY); // der 28.2.21, ein Sonntag lt. Windows-Kalender.
    printWeekday(28, 2, 2021);
    puts("Expected: Sonntag");

    puts("");

    printDate(28, 2, 2020, GERMANY); // der 28.2.20, ein Freitag lt. Windows-Kalender.
    printWeekday(28, 2, 2020);
    puts("Expected: Freitag");

    puts("");

    printDate(28, 2, 2019, GERMANY); // der 28.2.19, ein Donnerstag lt. Windows-Kalender.
    printWeekday(28, 2, 2019);
    puts("Expected: Donnerstag");

    puts("");

    printDate(28, 2, 2018, GERMANY); // der 28.2.18, ein Mittwoch lt. Windows-Kalender.
    printWeekday(28, 2, 2018);
    puts("Expected: Mittwoch");

    puts("");
}

void testPrintMonthGrid()
{
    puts("testPrintMonthGrid()");
    puts("");
    printMonthGrid(11, 2023);
    puts("");
    printMonthGrid(10, 2023);
    puts("");
    printMonthGrid(9, 2023);
    puts("");
    printMonthGrid(2, 2023);
    puts("");
    printMonthGrid(11, 2022);
    puts("");
    printMonthGrid(10, 2022);
    puts("");
    printMonthGrid(9, 2022);
    puts("");
    printMonthGrid(2, 2022);
    puts("");
    printMonthGrid(11, 2021);
    puts("");
    printMonthGrid(10, 2021);
    puts("");
    printMonthGrid(9, 2021);
    puts("");
    printMonthGrid(2, 2021);
    puts("");
    printMonthGrid(11, 2020);
    puts("");
    printMonthGrid(10, 2020);
    puts("");
    printMonthGrid(9, 2020);
    puts("");
    printMonthGrid(2, 2020);
    puts("");
    printMonthGrid(11, 2019);
    puts("");
    printMonthGrid(10, 2019);
    puts("");
    printMonthGrid(9, 2019);
    puts("");
    printMonthGrid(2, 2019);
    puts("");
}

void testZellerAlgorithm()
{
    puts("testZellerAlgorithm()");
    puts("");
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(1, 1, 2000), 1, 1, 2000);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(28, 2, 2022), 28, 2, 2022);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(28, 2, 2021), 28, 2, 2021);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(28, 2, 2020), 28, 2, 2020);
    puts("");
}

void test()
{
    testPrintWeekday();
    testGetWeekday();
    testPrintWeekday();
    testZellerAlgorithm();
    testPrintMonthGrid();
    testIsEarlierThan();
    testDateIncrementations();
    testToUnixTimes();
}