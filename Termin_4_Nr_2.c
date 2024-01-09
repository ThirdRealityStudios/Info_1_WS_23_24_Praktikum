#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct termin
{
	char *titel; // Max 20 symbols incl \0
	time_t start; // max. 2037
	long dauer; // max. 8
} Termin;

typedef struct terminserie
{
	Termin *termine; // beliebig viele Termine pro Serie
	int termineLength;
} Terminserie;

Termin* readTermin()
{
	char *titel;
	long tag, monat, jahr, stunde, minute;
	long dauer;
	
	fputs("Wie soll der Termin heissen?: ", stdout);
		
	titel = calloc(sizeof(char), 20);
		
	while(fgets(titel, 20, stdin) == NULL)
	{
		fflush(stdin);
	}
		
	for(int i = 0; i < 20; i++)
	{
		if(titel[i] == '\n')
			titel[i] = '\0';
	}
	
	fflush(stdin);
	
	fputs("\nJetzt bitte Datum und Uhrzeit (tt.mm.jjjj hh:mm): ", stdout);
	
	while(fscanf(stdin, "%d.%d.%d %d:%d", &tag, &monat, &jahr, &stunde, &minute) == 0
		  || jahr < 1970 || jahr > 2037)
	{
		fputs("\nIhre Termineingabe enthaelt einen Fehler!\n"
			  "Ihre Eingabe: ", stderr);
		
		fflush(stdin);
	}
	
	fflush(stdin);
	
	fputs("Jetzt bitte Termindauer in Stunden: ", stdout);
	
	while(fscanf(stdin, "%d", &dauer) != 1 || dauer < 1 || dauer > 8)
	{
		fputs("\nDie Eingabe der Termindauer war fehlerhaft!\n"
			  "Ihre Eingabe: ", stderr);
		fflush(stdin);
	}
	
	fflush(stdin);
	
	struct tm *tmTermin = calloc(sizeof(struct tm), 1);
	
	tmTermin -> tm_mday = tag;
	tmTermin -> tm_mon = monat - 1;
	tmTermin -> tm_year = jahr - 1900;
	tmTermin -> tm_hour = stunde;
	tmTermin -> tm_min = minute;
	tmTermin -> tm_isdst = 0;
	
	Termin *t = calloc(sizeof(Termin), 1);

	t -> start = mktime(tmTermin); // saves "tmTermin" as UNIX time
								   // and converts to GMT+0, so it thinks you pass some local time.

	free(tmTermin);
	
	t -> titel = titel;
	
	t -> dauer = dauer;
	
	return t;
}

void printTerminZeile(Termin *t)
{
	time_t time = t -> start;

	struct tm *stamp = localtime(&time);

	char formatTime[100];
	
	strftime(formatTime, sizeof(formatTime), "%d.%m.%Y %H:%M", stamp);
	
	fprintf(stdout, "Titel: %22s | ", t -> titel);
	fprintf(stdout, "Beginn: %18s | ", formatTime);
	fprintf(stdout, "Dauer: %3d\n", t -> dauer);
}

int main(int argc, char *argv)
{
	int serienLength = 0;
	int termineLength = 0;

	Terminserie *serien = NULL;
	Termin *termine = NULL;

	int indexSerien = 0;
	int indexTermine = 0;

	static int choice = EOF;

	int exit = 0;

	do
	{
		fputs("\n1 = Termin anlegen\n"
			  "2 = Terminserie anlegen\n"
			  "3 = Einzeltermin loeschen\n"
			  "4 = alle Termine und Serien anzeigen\n"
			  "5 = Naechsten Termin anzeigen\n"
			  "6 = Kalenderausgabe\n"
			  "9 = Beenden\n", stdout);
		fputs("Bitte treffen Sie eine Auswahl: ", stdout);
		fscanf(stdin, "%d", &choice);
		fflush(stdin);
		fputs("\n", stdout);

		switch(choice)
		{
			Termin *t = NULL;
			
			int relativeHaeufigkeit = 0;
			int absoluteHaeufigkeit = 0;
			
			int auswahl = 0;
			
			int scanfSuccess = 0;
			
			case 1: // Termin anlegen
				t = readTermin();
				
				if(t == NULL) // invalid input
					continue;
				
				if(termineLength == 0)
				{
					termine = calloc(sizeof(Termin), 1);
					
					termine[0] = *t;
					
					termineLength++;
				}
				else // termineLength > 0
				{
					Termin *newMemoryLocation = realloc(termine, ++termineLength * sizeof(Termin));
					
					if(newMemoryLocation == NULL)
					{
						fputs("Zu wenig Programmspeicher. Termin konnte nicht erstellt werden!\n", stderr);
						
						free(t);
						t = NULL;
						
						termineLength--; // Änderung rückgängig machen.
						
						break;
					}
					
					if(newMemoryLocation != termine)
					{
						free(termine); // alte Referenz freen
						termine = NULL;
						
						termine = newMemoryLocation; // Bugfix: before was access to dangling pointer below.
					}
					// else: Adresse ist die selbe geblieben.
					
					newMemoryLocation = NULL; // Referenz nicht mehr gebraucht.
					
					// Neues Element setzen / kopieren.
					termine[termineLength - 1] = *t;
				}
				
				// TODO Warum Crash, wenn free aktiv hier?
				// free(t);
				// t = NULL;
				
				printTerminZeile(&termine[termineLength - 1]);
				fprintf(stdout, "Es sind jetzt %d Termine registriert\n", termineLength);
			break;
			
			case 2: // Terminserie anlegen
				do{
					fputs("Soll Ihr Termin taeglich (1), woechentlich (2) oder 2-woechentlich (3) sein? > ", stdout);
					
					scanfSuccess = fscanf(stdin, "%d", &relativeHaeufigkeit);
					fflush(stdin);
					fputs("\n", stdout);
				}
				while(relativeHaeufigkeit < 1 || relativeHaeufigkeit > 3 || scanfSuccess != 1);
				
				do{
					fputs("Wie oft brauchen Sie den Termin? > ", stdout);
					
					scanfSuccess = fscanf(stdin, "%d", &absoluteHaeufigkeit);
					fflush(stdin);
					fputs("\n", stdout);
				}
				while(absoluteHaeufigkeit < 1 || scanfSuccess != 1);
				
				fputs("Geben Sie jetzt bitte die Termininfos ein!\n", stdout);
				
				t = readTermin();
				
				if(t == NULL) // Fehler beim Abfragen der Termininformationen
				{
					fputs("Anlegen der Serie fehlgeschlagen (Eingabe inkorrekt?)\n", stderr);
					
					break;
				}
				
				Terminserie *s = calloc(sizeof(Terminserie), 1);
				
				s -> termine = calloc(sizeof(Termin), absoluteHaeufigkeit);
				s -> termineLength = absoluteHaeufigkeit;
				
				// Entweder 1 Tag in secs, 1 Woche in secs oder 2 Wochen eben.
				int relativeHaeufigkeitSekunden = 
				(relativeHaeufigkeit == 1) ? 86400 : (relativeHaeufigkeit == 2)
				? 86400 * 7 : 86400 * 14;
				
				for(int i = 0; i < absoluteHaeufigkeit; i++)
				{
					s -> termine[i] = *t; // copy struct
					
					// Now set the start timestamp for daily, weekly whatever..
					(s -> termine[i]).start += i * relativeHaeufigkeitSekunden + (i > 0 ? 1 : 0);
				}
				
				if(serien == NULL)
				{
					serien = calloc(sizeof(Terminserie), ++serienLength);
					
					serien[0] = *s;
				}
				else // serienLength > 0 || serien != NULL
				{
					Terminserie *newMemoryLocation = realloc(serien, ++serienLength * sizeof(Terminserie));
					
					if(newMemoryLocation == NULL)
					{
						fputs("Zu wenig Programmspeicher. Terminserie konnte nicht erstellt werden!\n", stderr);
	
						free(s);
						s = NULL;
						
						serienLength--; // Änderung rückgängig machen.
						
						break;
					}
					
					if(newMemoryLocation != serien)
					{
						free(serien); // alte Referenz freen.
						serien = NULL;
						
						serien = newMemoryLocation; // Bugfix: before was access to dangling pointer before.
					}
					
					newMemoryLocation = NULL; // Referenz nicht mehr gebraucht.
					
					serien[serienLength - 1] = *s; // Neues Element setzen / kopieren.
				}

				free(t);
				t = NULL;
				
				free(s);
				s = NULL;
				
				fputs("Terminserie erstellt!\n", stdout);
			break;
			
			case 3: // Termin löschen
				fputs("Folgende Termine stehen zur Auswahl zum Loeschen (merke Nummer):\n\n", stdout);
				
				if(termineLength < 1)
				{
					fputs("Es stehen keine Termine zum Loeschen zur Auswahl\n", stdout);
					
					break;
				}
				
				for(int i = 0; i < termineLength; i++)
				{
					fprintf(stdout, "(Nr. %d) ", i);
					printTerminZeile(&termine[i]);
				}
				
				do{
					fputs("Nr zum Loeschen: ", stdout);
					fscanf(stdin, "%d", &auswahl);
					fflush(stdin);
				}
				while(auswahl < 0 || auswahl >= termineLength);
				
				free(&termine[auswahl]);
				
				if(termineLength == 1)
				{
					termine = NULL;
					
					termineLength--;
					
					break; // Code hierunter funktioniert nur für termineLength > 1
				}
				
				int toIgnoreIndex = auswahl;
				
				Termin *neuesArray = calloc(sizeof(Termin), termineLength - 1);
				
				int j = 0; // New array index
				
				for(int i = 0; i < termineLength; i++)
				{
					if(i != toIgnoreIndex) // the struct to "delete"
					{
						neuesArray[j] = termine[i]; // Termine kopieren außer den zu "löschenden".
						
						j++;
					}
				}
				
				--termineLength;
				
				free(termine);
				termine = neuesArray;
				
				fputs("Termin geloescht!\n", stdout);
			break;
			
			case 4: // Alle Termine anzeigen
				fputs("Ihre Einzeltermine:\n", stdout);
			
				for(int i = 0; i < termineLength; i++)
					printTerminZeile(&termine[i]);
				
				if(termineLength == 0)
					fputs("Keine Termine vorhanden\n", stdout);
				
				fputs("Ihre Terminserien:\n", stdout);
				
				for(int i = 0; i < serienLength; i++)
				{
					fprintf(stdout, "Terminserie Nr. %d\n", i + 1);
					
					// TODO Bug absturz hier loesen ab 2 Serien
					for(int j = 0; j < serien[i].termineLength; j++)
					{
						printTerminZeile(&serien[i].termine[j]);
					}
					
					fputs("\n", stdout);
				}
				
				if(serienLength == 0)
				{
					fputs("Es gibt keine Terminserien derzeit!\n", stdout);
					
					break;
				}
			break;
			
			case 5: // Naechsten Termin anzeigen
			{
				Termin *neachster = NULL;
				
				time_t systemzeit = time(NULL);
				
				// Nächsten Termin suchen (nicht aus Serien).
				for(int iT = 0; iT < termineLength; iT++)
				{
					// Termine aus Vergangenheit überspringen.
					if(termine[iT].start <= systemzeit)
						continue;
					// Schauen, ob der gefundene Termin noch früher ist.
					else if(neachster != NULL && termine[iT].start < neachster -> start)
						neachster = &termine[iT];
					else if(neachster == NULL) // es gibt noch keinen Vergleichstermin.
						neachster = &termine[iT];
				}
				
				Terminserie *aktuelleSerie = NULL;
				
				for(int iS = 0; iS < serienLength; iS++)
				{
					aktuelleSerie = &serien[iS];
					
					// Nächsten Termin suchen (anhand der aktuellen Terminserie).
					for(int iST = 0; iST < aktuelleSerie -> termineLength; iST++)
					{
						// Termine aus Vergangenheit überspringen.
						if(aktuelleSerie -> termine[iST].start <= systemzeit)
						{
							continue;
						}
						// Schauen, ob der gefundene Termin noch früher ist.
						else if(neachster != NULL && aktuelleSerie -> termine[iST].start < neachster -> start)
						{
							neachster = &aktuelleSerie -> termine[iST];
						}
						else if(neachster == NULL) // es gibt noch keinen Vergleichstermin.
						{
							neachster = &aktuelleSerie -> termine[iST];
						}
					}
				}

				if(neachster != NULL) // es gibt einen nächsten Termin
				{
					printTerminZeile(neachster);
				}
				else // es gibt keinen
					fputs("Sie haben keinen naechsten Termin!\n", stdout);
			break;
			}
			case 6: // Kalenderausgabe
				
			break;
			
			case 9: // Programm beenden
				exit = 1;
			break;
			
			default:
				fputs("Diese Eingabe war falsch\n", stdout);
				continue;
		}
	}
	while(!exit);

	free(serien);
	free(termine);

	return EXIT_SUCCESS;
}