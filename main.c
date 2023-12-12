#include "calendar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_TERMINSERIEN 3

long long** createEmptyTerminserien()
{
	long long **terminserien = NULL;
	
	terminserien = calloc(sizeof(long long*), MAX_TERMINSERIEN);
	
	for(int i = 0; i < MAX_TERMINSERIEN; i++)
	{
		terminserien[i] = calloc(MAX_TERMINE, sizeof(long long));
	}
	
	return terminserien;
}

void freeTerminserien(long long** terminserien)
{
	for(int i = 0; i < MAX_TERMINSERIEN; i++)
	{
		free(terminserien[i]);
	}
	
	free(terminserien);
}

/// @brief Die Hauptfunktion
/// @return 1, wenn Programm erfolgreich beendet, sonst 0.
int main(void)
{
	long long **terminserien = createEmptyTerminserien();

	int position = 0;

    while(1)
	{
		int userInputMainMenu = getUserInputMainMenu();

		switch(userInputMainMenu)
		{
			case 1:{
				// neue Terminserie anlegen
				
				if(position == MAX_TERMINSERIEN)
				{
					puts("Maximale Anzahl an Terminserien bereits erreicht!");
					continue;
				}
				
				int rythm = 0;
				
				puts("Welchen Rythmus soll Ihr Termin haben?\n"
				     "\n"
					 "1 fuer taeglich\n"
					 "2 fuer woechentlich\n"
					 "3 fuer 2-woechentlich\n");
				
				scanf("%d", &rythm);
				
				#if defined(WIN32) || defined(WIN64)
					fflush(stdin);
				#else
					getchar();
				#endif
				
				if(rythm > 3 && rythm < 1)
				{
					puts("Ihre Eingabe war falsch!");
					continue;
				}
				
				puts("Dankeschoen fuer Ihre Eingabe!\n"
					 "Geben Sie bitte den Ersttermin ein\n"
					 "(Format tt.mm.yyyy hh:MM):");

				int date[6] = {0,0,0,0,0,0};

				scanf("%02d.%02d.%04d %02d:%02d", &date, &date[1], &date[2], &date[3], &date[4]);

				#if defined(WIN32) || defined(WIN64)
					fflush(stdin);
				#else
					getchar();
				#endif

				puts("OK");

				// Die Unix-Zeit ermitteln.
				long long unixTime = toUnixtime(date);

				// MAX_TERMINE Termine anlegen für eine Serie.
				for(int i = 0; i < MAX_TERMINE; i++)
				{
					terminserien[position][i] = unixTime;

					switch(rythm)
					{
						case 1:
							terminserien[position][i] += ONEDAY * i;
						break;
						
						case 2:
							terminserien[position][i] += 7 * ONEDAY * i;
						break;
						
						case 3:
							terminserien[position][i] += 14 * ONEDAY * i;
						break;
						
						default:
							puts("Unbekannter, interner Fehler!");
					}
					
					printf("%d. Termin: %s\n", i+1, unixtimeToString(terminserien[position][i]));
				}
				
				puts("");

				position++;
				
				// Terminserie hier anlegen.
			}
			break;
			
			case 2: {
				// Terminserie anzeigen
				
				if(position == 0)
				{
					puts("Hier gibt es nichts zum Anzeigen.\n");
				}
				else
					for(int y = 0; y < position; y++)
					{
						printf("Terminserie %d:\n\n", y+1);
						
						for(int x = 0; x < MAX_TERMINE; x++)
						{
							printf("Termin %d: %s\n", x+1, unixtimeToString(terminserien[y][x]));
						}
						
						puts("");
					}
			}
			break;
			
			case 9:
				return EXIT_SUCCESS;

			default:
				puts("Ungueltige Eingabe!");
		}
	}

	freeTerminserien(terminserien);

    return EXIT_SUCCESS;
}