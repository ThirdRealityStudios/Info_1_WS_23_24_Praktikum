#include <stdlib.h>
#include <stdio.h>

#define GERMANY 0
#define SPAIN 1
#define USA 2
#define FRANCE 3
#define CHINA 4

#define HEIGHT 6 // Einfach immer 6 Zeilen, um das Monatsraster zu repräsentieren pauschal.
#define WIDTH 7 // 7 Wochentage

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

void testGetWeekday()
{
    puts("");
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(1, 1, 2000), 1, 1, 2000);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(28, 2, 2022), 28, 2, 2022);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(28, 2, 2021), 28, 2, 2021);
    printf("Weekday calculated is %d for %02d.%02d.%04d\n", getWeekday(28, 2, 2020), 28, 2, 2020);
    puts("");
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

void printWeekday(int day, int month, int year)
{
    printf("%s\n", getWeekdayString(getWeekday(day, month, year)));
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

/// @brief Fügt einen Tag in die richtige Stelle im 2D-Array ein,
///        abhängig davon,
///        welcher Wochentag (1 = Montag bis 7 = Sonntag) dieser ist.
///        Das bearbeitete 2D-Array (das per Parameter "grid" übergeben wurde) ergibt dann den
///        jeweiligen Monat,
///        den man auf der Konsole ausgeben möchte.
/// @param grid Referenz auf Ihr 2D-Array, das Sie einfach übergeben.
/// @param weekday Der Wochentag, z.B. "Montag", der für den übergebenen Tag gelten soll.
/// @param day Der Tag aus dem jeweiligen Monat.
/// @param firstDayX Die Position auf x-Achse gesehen vom ersten Tag im Monat.
///                  Wenn z.B. der 01.11.23 an der x-Position "2" steht in der ersten Zeile des Monats,
///                  dann muss entsprechend eine 2 übergeben werden.
///                  Bei dem 01.05.23 ist dies wiederum eine "0",
///                  da dieser direkt an erster Stelle steht und ein ein Montag war.
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

/// @brief Erstellt ein mit Nullen alloziiertes 2D-Array anhand von WIDTH und HEIGHT.
/// @return Alloziiertes 2D-Array.
int** createArray()
{
    int **arr = calloc(HEIGHT, sizeof(int));

    for(int i = 0; i < HEIGHT; i++)
    {
        arr[i] = calloc(WIDTH, sizeof(int));
    }

    return arr;
}

/// @brief Aufpassen, dass man den Speicher danach wieder freigibt!
/// @return Raster für einen Monat nach Wochentagen geordnet.
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

/// @brief Gibt den Monat in geschriebener, natürlich-sprachiger Form zurück.
/// @param month Monat im numerischen Format (1 bis 12).
/// @return Monat als Zeichenkette, lesbar für alle Menschen.
///         Falls ungültiger Monat angegeben, dann "Fehlermonat" als Rückgabe.
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

void testPrintMonthGrid()
{
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

/// @brief Gibt einen alloziierten, NULL-terminierten String wieder frei.
///        Achtung! Der String MUSS NULL-terminiert sein.
///        Ansonsten läuft freeString(..) in eine Endlosschleife..
/// @param string String, der wieder freigegeben werden soll.
void freeString(char *string)
{
    while(*string != '\0')
    {
        free(string++);
    }

    // NULL-Byte auch freigeben.
    free(string);
}

/// @brief Bestimmt die Länge eines NULL-terminierten Strings.
///        Das NULL-Byte wird hier NICHT mitgezählt für die Länge des Strings.
///        Obacht! Wenn der übergebene String nicht NULL-terminiert ist,
///        dann wird diese Funktion in eine Endlosschleife laufen!
/// @param string NULL-terminierter String
/// @return Länge dieses Strings.
int stringLength(char *string)
{
    int length = 0;

    // while(*string) ist das Gleiche wie while(*string != '\0').
    while(*string)
    {
        length++;

        string++; // Bugfix: vergessen zu inkrementieren (= Endlosschleife).
    }

    return length;
}

/// @brief Spiegelt einen String.
///        Achtung! Der zurückgebene String muss später auch wieder freigegeben werden mit freeString(..).
///        Außerdem ist der zurückgegebene String NULL-terminiert.
/// @param string Der String, der gespielgelt werden soll.
/// @return Ein komplett neuer String, aber gespiegelt (übergebener Parameter bleibt unverändert).
char* mirrorString(char *string)
{
    int stringLengthValue = stringLength(string);

    int newStringAllocationLength = stringLengthValue + 1;

    // stringLength(string) + 1 wegen NULL-Byte am Ende.
    // Das NULL-Byte muss aber wegen der Funktionsweise von calloc(..) nicht explizit gesetzt werden.
    char *mirroredString = calloc((size_t) newStringAllocationLength, sizeof(char));

    for(int i = 0; i < stringLengthValue; i++)
    {
        mirroredString[i] = string[stringLengthValue - i - 1]; // "- 1" wegen dem NULL-Byte, das ich nicht möchte an die erste Stelle.
    }

    return mirroredString;
}

/// @brief Wandelt eine Zahl in ihre String-Repräsentation um,
///        wobei diese Zahl aufgefüllt werden kann mit Nullen (per width).
///        Verwendet das Division-Modulo-Verfahren zur Basis 10 zur Umwandlung und Bestimmung der einzelnen Ziffern.
///        Achtung! Der zurückgegebene String muss später wieder per freeString(..) freigegeben werden,
///        falls er nicht mehr gebraucht wird.
/// @param num Zahl zum Konvertieren in einen String.
/// @return String-Repräsentation der Zahl.
char* toString(int num)
{
    char *digitString = NULL, *digitStringPos = NULL;

    int remainder = 0,
        quotient = 0;

    int stringLength = 0;

    do
    {
        // Für jede berechnete Ziffer soll die Anzahl
        // der Zeichenketten-Symbole um 1 (s. ++stringLength) wachsen.
        digitString = realloc(digitString, (size_t) (++stringLength));

        // Division-Modulo-Verfahren zur Bestimmung der 10er-Basis-Ziffer.
        remainder = num % 10;
        quotient = num / 10;

        // Die Schreibposition immer auf das letzte Zeichen setzen
        // in der Zeichenkette,
        // um die neue ermittelte Ziffer dort zu speichern.
        digitStringPos = digitString + stringLength - 1;

        *digitStringPos = (char) ('0' + remainder); // Die errechnete Ziffer in der Zeichenkette speichern (führend links).

        num = quotient;
    }
    while(quotient != 0);

    // Noch eine letzte Erweiterung des Strings,
    // um das NULL-Byte zu speichern.
    digitString = realloc(digitString, (size_t) (++stringLength));

    // Die Schreibposition wieder auf das letzte Zeichen setzen.
    digitStringPos = digitString + stringLength - sizeof(char);

    // NULL-Byte speichern.
    *digitStringPos = '\0';

    // Jetzt den String noch spiegeln,
    // da man auf dem Blatt Papier die ermittelte Zahl
    // auch von unten nach oben aufschreiben muss.
    // Dies ist hier also analog einfach das Spiegeln des Strings,
    // damit er später richtig angezeigt wird als Zahl.
    char *mirroredString = mirrorString(digitString);

    freeString(digitString);

    return mirroredString;
}

/// @brief Sagt, ob ein Datum ein Palindrom ist (1, wenn wahr, ansonsten 0)
/// @param day Tag
/// @param month Monat
/// @param year Jahr
/// @return 1, wenn das Datum ein Palindrom ist, ansonsten 0.
int isPalindrom(int day, int month, int year)
{
    return 0;
}

void testIsPalindrom()
{
    int day = 1, month = 1, year = 2023, result = 0;

    result = isPalindrom(day, month, year);
    printf("Ist %d.%d.%d ein Palindrom? %d\n", day, month, year, result);

    day = 22, month = 02, year = 2022;

    result = isPalindrom(day, month, year);
    printf("Ist %d.%d.%d ein Palindrom? %d\n", day, month, year, result);

    result = isPalindrom(day, month, year);
    printf("Ist %d.%d.%d ein Palindrom? %d\n", day, month, year, result);

    result = isPalindrom(day, month, year);
    printf("Ist %d.%d.%d ein Palindrom? %d\n", day, month, year, result);

    result = isPalindrom(day, month, year);
    printf("Ist %d.%d.%d ein Palindrom? %d\n", day, month, year, result);

    result = isPalindrom(day, month, year);
    printf("Ist %d.%d.%d ein Palindrom? %d\n", day, month, year, result);
}

void testToString()
{
    int num = 0;
    char *numString = NULL;

    puts("testToString()");

    puts("");

    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 1;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 2;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 3;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 9;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 10;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 11;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 12;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 98;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 99;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 100;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 101;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);

    num = 102;
    numString = toString(num);
    printf("Integer: %d, String-Zahl: %s\n", num, numString);
    freeString(numString);
}

/// @brief Die Hauptfunktion
/// @param argc Anzahl der Parameter auf der Konsole, inkl. Programmname selber.
/// @param argv Zeichenketten, die eingegeben wurden.
/// @return 1, wenn Programm erfolgreich beendet, sonst 0.
int main(int argc, char **argv)
{
    int day = 0, month = 0, year = 0;

    int countryCode = USA;

    testToString(); // Nicht gefordert vom Praktikum, aber ich mache zur Sicherheit, da es eine wichtige Hilfsfunktion ist.
    testPrintMonthGrid();
    testGetWeekday();
    testPrintWeekday();

    testIsPalindrom();

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