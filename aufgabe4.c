#include <stdlib.h>
#include <stdio.h>

#define GERMANY 0
#define SPAIN 1
#define USA 2
#define FRANCE 3
#define CHINA 4

/// @brief Sagt, ob das Jahr ein Schaltjahr ist.
/// @param year 
/// @return 
int isLeapYear(int year)
{
    int isMulitpleOf400 = year % 400 == 0;
    int isMultipleOf4 = year % 4 == 0;
    int isSecularYear = year % 100 == 0;

    // Jedes 400. Jahr ist ein Schaltjahr sowie alle Jahre,
    // die sich durch 4 teilen lassen (außer jedes 100. Jahr).
    return isMulitpleOf400 || (isMultipleOf4 && !isSecularYear);
}

/// @brief Sagt, ob das angegebene Datum gültig ist (zu Aufgabe 1 b).
/// @param day 
/// @param month 
/// @param year 
/// @return 
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

/// @brief Druckt das Datum in einem bestimmten Länderformat aus (Aufgabe 2).
/// @param day Der Tag
/// @param month Der Monat
/// @param year Das Jahr
/// @param countryCode Der Ländercode
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
            printf("%02d-%02d-%04d", month, day, year);
        break;

        case FRANCE:
            printf("%02d/%02d/%04d", day, month, year);
        break;

        case CHINA:
            printf("%04d-%02d-%02d", year, month, day);
        break;

        default:

        printDate(USA, day, month, year);
    }

    puts("");
}

/// @brief Rundet den Kommawert auf 0 ab (Nachkommastelle).
/// @param toFloor 
/// @return Abgerundeter Wert.
double floor(double toFloor)
{
    return (double) ((int) toFloor);
}

/// @brief Berechnet den Wochentag nach dem Zeller-Algorithmus.
///        Quelle für Spezialregelung: https://en.wikipedia.org/wiki/Zeller's_congruence#Common_simplification
/// @param day Tag des Datums
/// @param month Monat des Datums
/// @param year Jahr des Datums
/// @return Wochentag, wobei 1 = Montag und 7 = Sonntag usw. (zyklisch wiederholend).
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

void testZellerAlgorithm()
{
    puts("");
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(1, 1, 2000), 1, 1, 2000);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(28, 2, 2022), 28, 2, 2022);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(28, 2, 2021), 28, 2, 2021);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", zellerAlgorithm(28, 2, 2020), 28, 2, 2020);
    puts("");
}

void printWeekday(int day, int month, int year)
{
    int weekday = zellerAlgorithm(day, month, year);

    switch(weekday)
    {
        case 1:
            puts("Montag");
        break;

        case 2:
            puts("Dienstag");
        break;

        case 3:
            puts("Mittwoch");
        break;

        case 4:
            puts("Donnerstag");
        break;

        case 5:
            puts("Freitag");
        break;

        case 6:
            puts("Samstag");
        break;

        case 7:
            puts("Sonntag");
        break;

        default:
            puts("Unbekannter Fehler (Wert ungueltig)");
    }
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

/// @brief Gibt den maximalen Tag eines Monats zurück.
/// @param month Monat in einem bestimmten Jahr
/// @param year Jahr
/// @return Anzahl der Tage eines Monats in einem bestimmten Jahr.
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

/// @brief Aufpassen, dass man den Speicher danach wieder freigibt!
/// @return Raster für einen Monat nach Wochentagen geordnet.
int** saveMonthByWeekday(int month, int year)
{
    int **grid = calloc(6, sizeof(int*));

    for(int rows = 0; rows < 6; rows++)
        grid[rows] = calloc(7, sizeof(int));

    // int firstWeekdayInMonth = ;

    for(int day = 1; day <= maxDaysOfMonth(month, year); day++)
    {
        
    }

    return grid;
}

/// @brief Druckt einen Monat aus von einem Jahr,
///        formatiert nach den Wochentagen.
/// @param month Monat
/// @param year Jahr
void printMonthGrid(int month, int year)
{
    if(!(month > 0 && month < 13 && year > 1969 && year < 2101))
    {
        return; // Print nothing if the given month and year is not supported or invalid.
    }

    // int **month = saveMonthByWeekday(month, year);
}

/// @brief Die Hauptfunktion
/// @param argc Anzahl der Parameter auf der Konsole, inkl. Programmname selber.
/// @param argv Zeichenketten, die eingegeben wurden.
/// @return 1, wenn Programm erfolgreich beendet, sonst 0.
int main(int argc, char **argv)
{
    int day = 0, month = 0, year = 0;

    int countryCode = USA;

    testZellerAlgorithm();
    testPrintWeekday();

    do
    {
        if(argc == 4)
        {
            char *dayString, *monthString, *yearString;

            argv++; // Programmname überspringen.

            dayString = *argv; // Tag-Zeichenkette auslesen.

            argv++;

            monthString = *argv; // Monat-Zeichenkette auslesen.

            argv++;

            yearString = *argv; // Jahr-Zeichenkette auslesen.

            day = atoi(dayString);
            month = atoi(monthString);
            year = atoi(yearString);

            argc = 0; // Bugfix, damit do-while den "if(argc == 4)" Teil nur einmal ausführt.
        }
        else
        {
            puts("Geben Sie ein gültiges Datum ein:");

            puts("1. Tag: ");
            scanf("%d", &day);

            puts("2. Monat: ");
            scanf("%d", &month);

            puts("3. Jahr: ");
            scanf("%d", &year);
        }
    }
    while(!isDateValid(day, month, year));

    puts("Geben Sie einen Ländercode ein (0 bis 4):");
    scanf("%d", &countryCode);

    printDate(day, month, year, countryCode);
    puts("Wochentag:");
    printWeekday(day, month, year);

    puts("Programm beendet.");

    return EXIT_SUCCESS;
}