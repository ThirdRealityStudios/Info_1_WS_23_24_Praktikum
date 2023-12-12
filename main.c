#include "calendar.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// @brief Die Hauptfunktion
/// @return 1, wenn Programm erfolgreich beendet, sonst 0.
int main(void)
{
    while(1)
	{
		int userInputMainMenu = getUserInputMainMenu();
		
		switch(userInputMainMenu)
		{
			case 1:{
				// neue Terminserie anlegen
			}
			break;
			
			case 2: {
				// Terminserie anzeigen
			}
			break;
			
			case 9:
				return EXIT_SUCCESS;
				
			default:
				puts("Ungueltige Eingabe!");
		}
	}

    return EXIT_SUCCESS;
}