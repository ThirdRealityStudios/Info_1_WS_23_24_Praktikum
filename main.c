#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "list.h"

// gcc ./main.c ./list.c -o ./test.exe
int main(int argc, char **argv){
	List *list = createList();
	Person *p = malloc(sizeof(Person));
	p -> vorname = "Fritz";
	p-> nachname = "Mueller";
	p-> alter = 20;
	
	Person *p2 = malloc(sizeof(Person));
	p2 -> vorname = "Max";
	p2-> nachname = "Mustermann";
	p2-> alter = 18;
	
	Person *p3 = malloc(sizeof(Person));
	p3 -> vorname = "Albert";
	p3-> nachname = "Einstein";
	p3-> alter = 55;
	puts("Init done");
	
	addElement(list, 0, p); // kann man machen, da ja Funktion noch aufm Stack.
	puts("Added");
	
	Person *getP = getElement(list, 0) -> value;
	puts("Get called");
	
	printList(list);
	
	removeElement(list, getP);
	puts("Remove called");
	
	addElement(list, 0, p2);
	puts("Added");
	
	addElement(list, 0, p3);
	puts("Added");
	
	printList(list);
	
	free(list);
	free(p);
	free(p2);
	free(p3);
	
	return EXIT_SUCCESS;
}
	