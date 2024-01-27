#ifndef LIST_H
#define LIST_H

#include "types.h"

/// @brief Creates a new empty list.
/// @return Reference to the new empty list.
List* createList();

/// @brief Creates a new empty Element.
/// @return Empty element created.
Element* createElement();

/// @brief Deletes an element from the list
/// @param list List to delete from
/// @param el Person to delete
void removeElement(List *list, Person *p);

/// @brief Adds an Element at given index.
/// @param list The list to add the Element to.
/// @param index The index where to add the Element.
/// @param person The Person to add to the list.
void addElement(List *list, int index, Person *person);

/// @brief Gets an Element from the list.
/// @param list List to get the Person from.
/// @param index Index of the Person.
/// @return Element that holds a Person instance.
Element* getElement(List *list, int index);

/// @brief Returns the size of the list.
/// @param list List to print.
/// @return Size of the list.
int size(List *list);

/// @brief Prints a list
/// @param list The list to print
void printList(List *list);

#endif