#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define DEBUG // Uncomment if DEBUG output wanted.

/// \return Returns 1 if 'first' > 'second',
///  		-1 if 'first' \< 'second',
///         0 if 'first' equals 'second'.
int compare(struct tm first, struct tm second)
{
	int diff = difftime(mktime(&first), mktime(&second));
	
	return diff > 0 ? 1 : diff < 0 ? -1 : 0;
}

void doSomething(struct tm start, struct tm end)
{
	struct tm *current = &start;
	
	while(1)
	{
		if(compare(*current, end) > 0)
			break;
		else {
			// do something
			current -> tm_mday += 7;
			time_t currentTimeStamp = mktime(current);
			current = localtime(&currentTimeStamp);
		}
	}
	
	#ifdef DEBUG
	char dateString[100];
	
	strftime(dateString, sizeof(dateString), "%d.%m.%Y %H:%M", current);
	printf("%s\n", dateString); // Ausgabe: "01.07.2023 17:32"
	#endif
}

int main(void)
{
	struct tm *start, *end;
	
	time_t startT, endT;
	
	time ( &startT );
    start = localtime ( &startT );
	
	time ( &endT );
    end = localtime ( &endT );
	// end = gmtime ( &endT ); // Alternative: international time GMT+0
	
	end -> tm_mday += 7;
	
	doSomething(*start, *end);
	
	return EXIT_SUCCESS;
}