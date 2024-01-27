#ifndef TYPES_H
#define TYPES_H

typedef struct personStruct{
	char *vorname, *nachname;
	int alter;
} Person;

typedef struct elementStruct Element;

struct elementStruct{
	Person *value;
	Element *next;
};

typedef struct listStruct{
	Element *anfang;
	int size;
} List;

#endif