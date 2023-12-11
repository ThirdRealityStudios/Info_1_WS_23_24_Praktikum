#ifndef CALENDAR_H

#define CALENDAR_H

#define GERMANY 0
#define SPAIN 1
#define USA 2
#define FRANCE 3
#define CHINA 4

/// @brief Sagt, ob das Jahr ein Schaltjahr ist.
/// @param year
/// @return 1 wenn Schaltjahr, ansonsten 0.
int isLeapYear(int year);

/// @brief Sagt, ob das angegebene Datum gültig ist (zu Aufgabe 1 b).
/// @param day
/// @param month
/// @param year
/// @return 1, wenn das Datum korrekt ist. Ansonsten 0.
int isDateValid(int day, int month, int year);

/// @brief Druckt das Datum in einem bestimmten Länderformat aus (Aufgabe 2).
/// @param day Der Tag
/// @param month Der Monat
/// @param year Das Jahr
/// @param countryCode Der Ländercode
void printDate(int day, int month, int year, int countryCode);

/// @brief Rundet den Kommawert auf 0 ab (Nachkommastelle).
/// @param toFloor
/// @return Abgerundeter Wert.
double floor(double toFloor);

/// @brief Berechnet den Wochentag nach dem Zeller-Algorithmus.
///        Quelle für Spezialregelung: https://en.wikipedia.org/wiki/Zeller's_congruence#Common_simplification
/// @param day Tag des Datums
/// @param month Monat des Datums
/// @param year Jahr des Datums
/// @return Wochentag, wobei 0 = Samstag und 6 = Freitag usw. (zyklisch wiederholend).
int zellerAlgorithm(int day, int month, int year);

/// @brief Gibt den Wochentag komplett ausgeschrieben aus
///        auf der Konsole für ein bestimmtes Datum.
void printWeekday(int day, int month, int year);

/// @brief Berechnet den Wochentag nach dem Zeller-Algorithmus.
///        Quelle für Spezialregelung: https://en.wikipedia.org/wiki/Zeller's_congruence#Common_simplification
/// @param day Tag des Datums
/// @param month Monat des Datums
/// @param year Jahr des Datums
/// @return Wochentag, wobei 1 = Montag und 7 = Sonntag usw. (zyklisch wiederholend).
int getWeekday(int day, int month, int year);

/// @brief Gibt den Wochentag ausgeschrieben als Zeichenkette zurück
///        für einen bestimmten Ganzzahl-Wert,
///        nämlich von 1 (Montag) bis 7 (Sonntag).
/// @return Wochentag als Zeichenkette.
char* getWeekdayString(int weekday);

/// @brief Gibt den Wochentag voll ausgeschrieben
///        auf der Konsole aus für ein bestimmtes Datum.
void printWeekday(int day, int month, int year);

/// @brief Gibt den maximalen Tag eines Monats zurück.
/// @param month Monat in einem bestimmten Jahr
/// @param year Jahr
/// @return Anzahl der Tage eines Monats in einem bestimmten Jahr.
int maxDaysOfMonth(int month, int year);

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
void insertDay(int **grid, int weekday, int day, int firstDayX);

/// @brief Erstellt ein mit Nullen alloziiertes 2D-Array anhand von WIDTH und HEIGHT.
/// @return Alloziiertes 2D-Array.
int** createArray();

/// @brief Aufpassen, dass man den Speicher danach wieder freigibt!
/// @return Raster für einen Monat nach Wochentagen geordnet.
int** getMonthArray(int month, int year);

/// @brief Gibt den Monat in geschriebener, natürlich-sprachiger Form zurück.
/// @param month Monat im numerischen Format (1 bis 12).
/// @return Monat als Zeichenkette, lesbar für alle Menschen.
///         Falls ungültiger Monat angegeben, dann "Fehlermonat" als Rückgabe.
char* getMonthString(int month);

/// @brief Druckt einen Monat aus von einem Jahr,
///        formatiert nach den Wochentagen.
/// @param month Monat
/// @param year Jahr
void printMonthGrid(int month, int year);

/// @brief Sagt dir,
///        ob ein Datum älter ist als das andere.
/// @param dateEarlier Älteres Datum als Array der Form {Tag, Monat, Jahr, Stunde, Minute, Sekunde}.
/// @param dateLater Neueres Datum als Array der Form {Tag, Monat, Jahr, Stunde, Minute, Sekunde}.
/// @return -1, wenn dateEarlier kleiner als dateLater. Ansonsten 0, wenn beide gleich. Andernfalls 1, wenn dateEarlier größer ist als dateLater.
int isEarlierThan(int dateEarlier[], int dateLater[]);

/// @brief Inkrementiert ein Datumsobjekt um eine Sekunde.
/// @param date Datumsarray der Form {Tag, Monat, Jahr, Stunde, Minute, Sekunde}.
void incDateSecond(int date[]);

/// @brief Berechnet für ein gegebenes Datum (in Form eines Arrays)
///        die Unix-Zeit,
///        also die verstrichenen Sekunde seit dem 1.1.1970.
/// @param date Array muss Form {Tag, Monat, Jahr, Stunde, Minute, Sekunde}.
/// @return Anzahl der Sekunde seit 1.1.1970.
long long toUnixtime(int date[]);

/// @brief Gibt den jeweiligen Zeitstempel als String zurück,
///        formatiert als deutsches Datum.
/// @return Zeichenkette des jeweligen Datums.
const char* unixtimeToString(long long timeStamp);

/// @brief Vergleicht zwei Daten "first" und "second".
/// @param first Erstes Datum
/// @param second Zweites Datum
/// @return Gibt 1 zurück, wenn "first" > "second", ansonsten -1.
int compare(int first[], int second[]);

/// @brief Sagt dir,
///        ob ein Datum zwischen zwei anderen liegt.
/// @param before Anfangsdatum
/// @param between Datum, das dazwischen liegen soll.
/// @param after Enddatum
/// @return 1, wenn das Datum zwischen diesen liegt, ansonsten 0.
int between(int before[], int between[], int after[]);

/// @brief Testet die Funktion between().
void testBetween();

/// @brief Testet die Funktion printWeekday().
void testPrintWeekday();

/// @brief Testet die Funktion getWeekday().
void testGetWeekday();

/// @brief Testet die Funktion printWeekday().
void testPrintWeekday();

/// @brief Testet die Funktion zellerAlgorithm().
void testZellerAlgorithm();

/// @brief Testet die Funktion printMonthGrid().
void testPrintMonthGrid();

/// @brief Blyat zum Testen von int compare(..).
void testCompare();

/// @brief Testet alle Funktionalitäten,
///        indem alle untergeordneten Test-Funktionen aufgerufen werden nacheinander.
void test();

#endif
