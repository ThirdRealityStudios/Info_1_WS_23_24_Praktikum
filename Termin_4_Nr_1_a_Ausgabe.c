#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct tm date = {0, 32, 17, 4, 6, 123};
char dateString[100];

int main(void)
{
	strftime(dateString, sizeof(dateString), "%d.%m.%Y %H:%M", &date);
	printf("%s", dateString); // Ausgabe: "01.07.2023 17:32"
	
	return EXIT_SUCCESS;
}