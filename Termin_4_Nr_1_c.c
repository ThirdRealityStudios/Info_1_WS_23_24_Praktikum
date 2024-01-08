#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	fputs("Bitte geben Sie zwei Datumswerte inkl. Uhrzeit "
		  "ein nach dem folgenden Format:\n"
		  "tt.mm.jjjj hh:mm\n\n", stdout);
	int day, month, year, hour, minute;
	
	int amountValuesRead = 0;
	
	do
	{
		fputs("Das 1. Datum mit Uhrzeit bitte:\n", stdout);
		
		amountValuesRead = fscanf(stdin, "%02d.%02d.%04d %02d:%02d", &day, &month, &year, &hour, &minute);
		fflush(stdin);
	}
	while(amountValuesRead != 5);
	
	int day2, month2, year2, hour2, minute2;
	do
	{
		fputs("Bitte das 2. Datum mit Uhrzeit eingeben:\n", stdout);
		amountValuesRead = fscanf(stdin, "%02d.%02d.%04d %02d:%02d", &day2, &month2, &year2, &hour2, &minute2);
		fflush(stdin);
	}
	while(amountValuesRead != 5);
	
	fputs("Danke blyat\n", stdout);
	
	// calloc() verwenden, da sonst restliche nicht gesetzte Felder später zufällige Werte haben..
	struct tm *tm1 = calloc(sizeof(struct tm), 1), *tm2 = calloc(sizeof(struct tm), 1);
	
	tm1 -> tm_mday = day;
	tm1 -> tm_mon = month - 1;
	tm1 -> tm_year = year - 1900;
	tm1 -> tm_hour = hour;
	tm1 -> tm_min = minute;
	
	tm2 -> tm_mday = day2;
	tm2 -> tm_mon = month2 - 1;
	tm2 -> tm_year = year2 - 1900;
	tm2 -> tm_hour = hour2;
	tm2 -> tm_min = minute2;
	
	char dateString0[100], dateString1[100];
	
	strftime(dateString0, sizeof(dateString0), "%d.%m.%Y %H:%M", tm1);
	
	fprintf(stdout, "1. Datum mit Uhrzeit war: %s\n", dateString0);
	
	strftime(dateString1, sizeof(dateString1), "%d.%m.%Y %H:%M", tm2);
	
	fprintf(stdout, "Das 2. Datum mit Uhrzeit ist: %s\n", dateString1);
	
	long long time1 = mktime(tm1);
	long long time2 = mktime(tm2);
	
	long long diffTime = time1 > time2 ? (time1 - time2) : (time2 - time1);
	
	fprintf(stdout, "Zeitdiff.: %d", diffTime / 60); // Zeit ausgeben in Minuten.
	
	return EXIT_SUCCESS;
}

