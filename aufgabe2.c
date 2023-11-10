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
    if(countryCode == GERMANY)
        printf("%02d.%02d.%04d", day, month, year);
    else if(countryCode == SPAIN)
        printf("%02d/%02d/%04d", day, month, year);
    else if(countryCode == USA)
        printf("%02d-%02d-%04d", month, day, year);
    else if(countryCode == FRANCE)
        printf("%02d/%02d/%04d", day, month, year);
    else if(countryCode == CHINA)
        printf("%04d-%02d-%02d", year, month, day);
    else
        printDate(USA, day, month, year);

    puts("");
}

/// @brief Die Hauptfunktion
/// @param argc Anzahl der Parameter auf der Konsole, inkl. Programmname selber.
/// @param argv Zeichenketten, die eingegeben wurden.
/// @return 1, wenn Programm erfolgreich beendet, sonst 0.
int main(int argc, char **argv)
{
    int day = 0, month = 0, year = 0;

    int countryCode = USA;

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

    puts("Programm beendet.");

    return EXIT_SUCCESS;
}