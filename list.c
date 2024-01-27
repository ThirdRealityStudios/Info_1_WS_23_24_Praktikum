#include <stdio.h>
#include <stdlib.h>
#include "types.h"

List* createList(){
	return calloc(sizeof(List), 1);
}

Element* createElement(){
	return calloc(sizeof(Element), 1);
}

void removeElement(List *list, Person *p){
	if(list == NULL || p == NULL || list -> anfang == NULL)
		return;
	
	if(list -> anfang -> next == NULL) // only 1 element
	{
		if(list -> anfang -> value == p)
		{
			free(list -> anfang -> value);
			free(list -> anfang);
			list -> anfang = NULL;
			
			list -> size--;
		}
		return;
	}
	
	Element* current = list -> anfang;
	
	if(current -> value == p) // remove first element case
	{
		Element *next = current -> next;
		
		list -> anfang = next;
		
		free(current -> value);
		free(current);
		
		list -> size--;
	}
	
	while(current -> next != NULL && current -> next -> value != p)
		current = current -> next; // find element before the one to delete.
	
	if(current -> next == NULL) // element not found
	{
		return;
	}
	
	Element *next = current -> next; // to delete
	
	current -> next = current -> next -> next; // bind element before to remove element with el after that.
	
	free(next -> value);
	free(next);
	
	list -> size--;
}

Element* getElement(List *list, int index){
	if(list == NULL || list -> anfang == NULL)
		return NULL; // empty or invalid list => element not existing.
	
	Element *current = list -> anfang;
	
	for(int i = 0; i <= index; i++)
	{
		if(i == index)
			return current;
		
		current = current -> next;
	}
	
	return NULL; // element not found (Person)
}

void addElement(List *list, int index, Person *person){
	if(list == NULL || person == NULL)
		return; // list or person argument invalid.
	
	Element *neu = createElement();
	neu -> value = person;
	
	list -> size++;
	
	if(list -> anfang == NULL)
	{
		list -> anfang = neu;
		
		return;
	}
	
	if(index == 0)
	{
		neu -> next = list -> anfang;
		
		list -> anfang = neu;
		
		return;
	}
	
	Element *before = getElement(list, index - 1);
	
	neu -> next = before -> next;
	before -> next = neu;
}

int size(List *list){
	if(list == NULL)
		return -1;
	
	return list -> size;
}

void printList(List *list){
	
	if(list == NULL)
		return;
	
	for(int i = 0; i < size(list); i++){
		Person *current = getElement(list, i) -> value;
		printf("%s, %s, %d Jahre alt\n", current -> vorname, current -> nachname, current -> alter);
	}
}