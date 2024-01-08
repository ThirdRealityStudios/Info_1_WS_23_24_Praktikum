#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
// Alter, fehlerhafter Code mit Absturz
int main(void)
{
	time_t *currentTime = time(NULL);
	
	char dateString[100];
	
	strftime(dateString, sizeof(dateString), "%d.%m.%Y %H:%M", currentTime);
	
	printf("%s\n", dateString);
	
	return EXIT_SUCCESS;
}
*/

// Korrigerter Code
int main(void)
{
	time_t currentTime = time(NULL); // Hier jetzt kein Pointer mehr (Rückgabe von time() ist eine Ganzzahl)
	
	char dateString[100];
	
	strftime(dateString, sizeof(dateString), "%d.%m.%Y %H:%M", localtime(&currentTime)); // localtime() macht time_t zu struct tm.
	
	printf("%s\n", dateString);
	
	return EXIT_SUCCESS;
}

