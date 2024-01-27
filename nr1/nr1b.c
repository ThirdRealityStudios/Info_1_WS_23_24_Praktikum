#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	char ziel[20];
	
	strcpy(ziel, "Sexy unsicher in ein Array schreiben"
				 " und noch mehr Schabernak-Text hier bis "
				 "das Programm hoffentlich irgendwann abstuerzt oder "
				 "mein Anti-Viren-Programm mein C-Programm in Quarantaene steckt "
				 "und beendet. s daf dfs f a f dfsa f dsa f dsaf sad f saf sadf  saf sa f ds af sa fsdaf sa f dsa f sa fdsa ");
	
	fputs("Geilomat\n", stdout);
	fprintf(stdout, "%s", ziel);
	return EXIT_SUCCESS;
}
	